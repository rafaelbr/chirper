//
// Created by Rafael Brasileiro de Araujo on 16/08/24.
//

#include "DisplayController.h"



DisplayController::DisplayController() {
    display = new SSD1306Wire(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);
    ui = new DisplayUi(display);

    //put some additional creation and instantiation code here
    linePos = 0;
    charPos = 0;

    inputStartLine = 0;
    inputStartCol = 0;

    inputEndLine = 0;
    inputEndCol = 0;

    for (char & i : inputBuffer) {
        i = 0;
    }
    inputBufferIndex = -1;
}

DisplayController::~DisplayController() {
    display->displayOff();
    delete ui;
    delete display;
}

void DisplayController::begin() {
    configureUI();
}

void DisplayController::println(String text) {
    //check if display reach end of screen
    if (linePos > HELTEC_DISPLAY_MAXLINES) {
        display->clear();
        linePos = 0;
    }

    display->drawString(charPos, linePos, text);
    display->display();
    linePos += 10;
}

void DisplayController::clearCurrentChar() {
    if (inputBufferIndex < 0) {
        return;
    }

    //get current char width
    int charWidth = display->getStringWidth(String(inputBuffer[inputBufferIndex]));

    display->setColor(BLACK);
    display->fillRect(charPos, linePos, charWidth, HELTEC_DISPLAY_LINEHEIGHT + 3);
    display->display();
    display->setColor(WHITE);
    //Serial.println("Checkin clear char - LinePos: " + String(linePos) + " CharPos: " + String(charPos) + " InputBufferIndex: " + String(inputBufferIndex) + " CharWidth: " + String(charWidth));

    //clear current char from buffer
    removeLastCharFromBuffer();
}

void DisplayController::printCharSequence(char c) {
    //Serial.println("InputEndCol: " + String(inputEndCol) + " InputEndLine: " + String(inputEndLine) + " InputBufferIndex: " + String(inputBufferIndex) + " CharPos: " + String(charPos) + " LinePos: " + String(linePos));
    //clear current char
    clearCurrentChar();

    //return if no char
    if (c == 0) {
        return;
    }

    //ENTER
    if (c == 0x0D) {
        charPos = 0;
        linePos += 10;
        if (linePos > inputEndLine) {
            linePos = inputStartLine;
        }
        printInputCursor();
        return;
    }

    //BACKSPACE
    if (c == 0x08) {
        if (inputBufferIndex < 0) {
            printInputCursor();
            return;
        }
        char currentChar = inputBuffer[inputBufferIndex];
        if (charPos <= inputStartCol) {
            linePos -= HELTEC_DISPLAY_LINEHEIGHT;
            if (linePos < inputStartLine) {
                linePos = inputStartLine;
            }
            //calculate current buffer width
            String currentBuffer = String(inputBuffer);
            charPos = display->getStringWidth(currentBuffer.substring(0, inputBufferIndex+1));
        }
        charPos -= display->getStringWidth(String(currentChar));
        if (charPos < inputStartCol) {
            charPos = inputStartCol;
        }

        clearCurrentChar();
        printInputCursor();
        return;
    }

    //get width of char on current font
    int charWidth = display->getStringWidth(String(c));

    //prevent to add more characters outside input area
    if (charPos + charWidth >= inputEndCol && linePos + HELTEC_DISPLAY_LINEHEIGHT >= inputEndLine) {
        return;
    }
    //Serial.println("Before print - Char width: " + String(charWidth) + " CharPos: " + String(charPos) + " LinePos: " + String(linePos) + " InputEndCol: " + String(inputEndCol) + " InputEndLine: " + String(inputEndLine));

    //print character on display
    display->setColor(WHITE);
    display->drawString(charPos, linePos, String(c));
    display->display();

    //update cursor position
    charPos += charWidth;
    if (charPos >= inputEndCol) {
        charPos = inputStartCol;
        linePos += HELTEC_DISPLAY_LINEHEIGHT;
    }
    //store char in buffer
    addCharToBuffer(c);
    //Serial.println("After print - Char width: " + String(charWidth) + " CharPos: " + String(charPos) + " LinePos: " + String(linePos) + " InputEndCol: " + String(inputEndCol) + " InputEndLine: " + String(inputEndLine));
    printInputCursor();

}

void DisplayController::printInputCursor() {
    //Serial.println("Checkin inputs - inputStartLine: " + String(inputStartLine) + " inputStartCol: " + String(inputStartCol) + " inputEndLine: " + String(inputEndLine) + " inputEndCol: " + String(inputEndCol) + " InputBufferIndex: " + String(inputBufferIndex));
    display->drawString(charPos, linePos, "_");
    display->display();
    //Serial.println("Checkin inputs - inputStartLine: " + String(inputStartLine) + " inputStartCol: " + String(inputStartCol) + " inputEndLine: " + String(inputEndLine) + " inputEndCol: " + String(inputEndCol) + " InputBufferIndex: " + String(inputBufferIndex));
    addCharToBuffer('_');
    //Serial.println("Checkin Input Cursor - inputStartLine: " + String(inputStartLine) + " inputStartCol: " + String(inputStartCol) + " inputEndLine: " + String(inputEndLine) + " inputEndCol: " + String(inputEndCol) + " InputBufferIndex: " + String(inputBufferIndex));
}

void DisplayController::clearInputKb(int startLine, int startCol, int endLine, int endCol, bool clearBuffer) {
    display->setColor(BLACK);
    display->fillRect(startCol, startLine, endCol, endLine - HELTEC_DISPLAY_LINEHEIGHT);
    display->display();
    display->setColor(WHITE);


    if (clearBuffer) {
        inputBufferIndex = -1;
        for (char & i : inputBuffer) {
            i = 0;
        }
    }

}

void DisplayController::setTextCursor(int line, int col) {
    clearCurrentChar();
    linePos = line;
    charPos = col;
}


void DisplayController::setupInputKb(int startLine, int startCol, int endLine, int endCol) {
    //clear input cursor from current position
    clearCurrentChar();

    inputStartLine = startLine;
    inputStartCol = startCol;
    inputEndLine = endLine;
    inputEndCol = endCol;
    setTextCursor(inputStartLine, inputStartCol);
    //Serial.println("Checkin Setup Input - inputStartLine: " + String(inputStartLine) + " inputStartCol: " + String(inputStartCol) + " inputEndLine: " + String(inputEndLine) + " inputEndCol: " + String(inputEndCol));

    inputBufferIndex = -1;
    for (char & i : inputBuffer) {
        i = 0;
    }

    printInputCursor();
}

void DisplayController::clear() {
    display->clear();
    linePos = 0;
}

String DisplayController::getInputBuffer() {
    String data;
    for (int i = 0; i < inputBufferIndex; i++) {
        data += inputBuffer[i];
    }

    return data;
}

void DisplayController::addCharToBuffer(char c) {
    inputBufferIndex++;
    inputBuffer[inputBufferIndex] = c;
    //Serial.println("Current buffer: " + String(inputBuffer));
}

void DisplayController::removeLastCharFromBuffer() {
    inputBuffer[inputBufferIndex] = 0;
    inputBufferIndex--;
    //Serial.println("Current buffer: " + String(inputBuffer));
}

void DisplayController::drawImage(int x, int y, int w, int h, const uint8_t *data) {
    display->drawXbm(x, y, w, h, data);
    display->display();
}

void DisplayController::configureUI() {
    ui->setTargetFPS(60);

    ui->disableAllIndicators();

    ui->setActiveSymbol(activeSymbol);
    ui->setInactiveSymbol(inactiveSymbol);
    ui->setIndicatorPosition(RIGHT);
    ui->setIndicatorDirection(LEFT_RIGHT);
    ui->setFrameAnimation(SLIDE_UP);
    ui->disableAutoTransition();
    ui->init();
}

int16_t DisplayController::updateUI() {
    return ui->update();
}

ScreenDisplay* DisplayController::getDisplay() {
    return display;
}

void DisplayController::setFrames(FrameCallback* frames, int frameCount) {
    ui->setFrames(frames, frameCount);
}

void DisplayController::setOverlays(OverlayCallback* overlays, int overlayCount) {
    ui->setOverlays(overlays, overlayCount);
}

void DisplayController::showFrame(int frameIndex) {
    currentFrame = frameIndex;
    ui->switchToFrame(frameIndex);
    frameInitialized = false;
}

void DisplayController::setFrameInitilized() {
    frameInitialized = true;
}

int DisplayController::addInputConfig(String label, int startLinePos, int maxLines, const uint8_t *fontData, bool shouldClearBuffer) {
    InputConfig config;
    config.label = label;
    config.startLinePos = startLinePos;
    config.maxLines = maxLines;
    config.fontData = fontData;
    config.shouldClearBuffer = shouldClearBuffer;
    inputConfigs[inputConfigsCount] = config;
    inputConfigsCount++;
    return inputConfigsCount - 1;
}

InputConfig DisplayController::getInputConfig(int index) {
    return inputConfigs[index];
}

void DisplayController::updateInput(int inputConfigIndex, KeyboardController* kbController) {
    InputConfig config = inputConfigs[inputConfigIndex];


    String label = config.label;
    int maxLines = config.maxLines;
    const uint8_t *fontData = config.fontData;
    bool shouldClearBuffer = config.shouldClearBuffer;

    int firstLineMaxSize = DISPLAY_WIDTH - display->getStringWidth(label);
    int linesMaxSize = DISPLAY_WIDTH;
    int maxSize = firstLineMaxSize + linesMaxSize * (maxLines - 1);

    String inputBuffer;
    if (config.isActive) {
        inputBuffer = kbController->getInputBuffer() + "_";
    }
    else {
        inputBuffer = config.buffer;
    }

    if (display->getStringWidth(inputBuffer) >= maxSize && config.isActive) {
        inputBuffer.remove(inputBuffer.length() - 2, 2);

        kbController->adjustBuffer(inputBuffer);
    }

    config.buffer = inputBuffer;
    inputConfigs[inputConfigIndex] = config;


    String firstLineBuffer;
    int lineStop = -1;
    for (int i = 0; i < inputBuffer.length(); i++) {
        if (display->getStringWidth(firstLineBuffer + String(inputBuffer[i])) < firstLineMaxSize) {
            firstLineBuffer += inputBuffer[i];
            lineStop = i;
        } else {
            break;
        }
    }

    display->setFont(fontData);

    display->drawString(0, config.startLinePos, label + firstLineBuffer);



    inputBuffer = inputBuffer.substring(lineStop+1, inputBuffer.length());
    int bufferLines = (display->getStringWidth(inputBuffer) / DISPLAY_WIDTH) + 1;
    String linesBuffer[bufferLines];
    for (int i = 0; i < bufferLines; i++) {
        int lineStop = -1;
        String lineBuffer;
        for (int j = 0; j < inputBuffer.length(); j++) {
            if (display->getStringWidth(lineBuffer + String(inputBuffer[j])) < linesMaxSize) {
                lineBuffer += inputBuffer[j];
            } else {
                lineStop = j;
                break;
            }
        }
        linesBuffer[i] = lineBuffer;
        inputBuffer = inputBuffer.substring(lineStop, inputBuffer.length());
    }

    if (bufferLines <= 0) {
        return;
    }

    for (int i = 0; i < bufferLines; i++) {
        String lineBuffer = linesBuffer[i];
        display->drawString(0, config.startLinePos + (13 * (i+1)), lineBuffer);
    }
}

void DisplayController::setInputActive(int inputConfigIndex) {
    //disable all inputs
    for (int i = 0; i < inputConfigsCount; i++) {
        InputConfig config = inputConfigs[i];
        config.isActive = false;
        config.buffer.remove(config.buffer.length() - 1, 1);
        inputConfigs[i] = config;
    }
    //enable current active input
    InputConfig config = inputConfigs[inputConfigIndex];
    config.isActive = true;
    //remove cursor
    inputConfigs[inputConfigIndex] = config;
}