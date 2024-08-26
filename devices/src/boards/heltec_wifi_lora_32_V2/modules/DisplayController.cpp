//
// Created by Rafael Brasileiro de Araujo on 16/08/24.
//

#include "DisplayController.h"


DisplayController::DisplayController() {
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
    Heltec.display->displayOff();
}

void DisplayController::begin() {
    Heltec.begin(true, false);
}

void DisplayController::println(String text) {
    //check if display reach end of screen
    if (linePos > HELTEC_DISPLAY_MAXLINES) {
        Heltec.display->clear();
        linePos = 0;
    }
    Heltec.display->drawString(0, linePos, text);
    Heltec.display->display();
    linePos += 10;
}

void DisplayController::clearCurrentChar() {
    if (inputBufferIndex < 0) {
        return;
    }

    //get current char width
    int charWidth = Heltec.display->getStringWidth(String(inputBuffer[inputBufferIndex]));

    Heltec.display->setColor(BLACK);
    Heltec.display->fillRect(charPos, linePos, charWidth, HELTEC_DISPLAY_LINEHEIGHT + 3);
    Heltec.display->display();
    Heltec.display->setColor(WHITE);
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
            charPos = Heltec.display->getStringWidth(currentBuffer.substring(0, inputBufferIndex+1));
        }
        charPos -= Heltec.display->getStringWidth(String(currentChar));
        if (charPos < inputStartCol) {
            charPos = inputStartCol;
        }

        clearCurrentChar();
        printInputCursor();
        return;
    }

    //get width of char on current font
    int charWidth = Heltec.display->getStringWidth(String(c));

    //prevent to add more characters outside input area
    if (charPos + charWidth >= inputEndCol && linePos + HELTEC_DISPLAY_LINEHEIGHT >= inputEndLine) {
        return;
    }
    //Serial.println("Before print - Char width: " + String(charWidth) + " CharPos: " + String(charPos) + " LinePos: " + String(linePos) + " InputEndCol: " + String(inputEndCol) + " InputEndLine: " + String(inputEndLine));

    //print character on display
    Heltec.display->setColor(WHITE);
    Heltec.display->drawString(charPos, linePos, String(c));
    Heltec.display->display();

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
    Heltec.display->drawString(charPos, linePos, "_");
    Heltec.display->display();
    //Serial.println("Checkin inputs - inputStartLine: " + String(inputStartLine) + " inputStartCol: " + String(inputStartCol) + " inputEndLine: " + String(inputEndLine) + " inputEndCol: " + String(inputEndCol) + " InputBufferIndex: " + String(inputBufferIndex));
    addCharToBuffer('_');
    //Serial.println("Checkin Input Cursor - inputStartLine: " + String(inputStartLine) + " inputStartCol: " + String(inputStartCol) + " inputEndLine: " + String(inputEndLine) + " inputEndCol: " + String(inputEndCol) + " InputBufferIndex: " + String(inputBufferIndex));
}

void DisplayController::clearInputKb(int startLine, int startCol, int endLine, int endCol, bool clearBuffer) {
    Heltec.display->setColor(BLACK);
    Heltec.display->fillRect(startCol, startLine, endCol, endLine - HELTEC_DISPLAY_LINEHEIGHT);
    Heltec.display->display();
    Heltec.display->setColor(WHITE);


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
    Heltec.display->clear();
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
