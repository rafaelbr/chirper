//
// Created by Rafael Brasileiro de Araujo on 16/08/24.
//

#include "DisplayController.h"


DisplayController::DisplayController() {
    //put some additional creation and instantiation code here
}

DisplayController::~DisplayController() {
    Heltec.display->displayOff();
}

void DisplayController::begin() {
    //enable heltec stack but only display
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
    Heltec.display->setColor(BLACK);
    Heltec.display->fillRect(charPos, linePos, 6, 13);
    Heltec.display->display();
    Heltec.display->setColor(WHITE);
}

void DisplayController::printCharSequence(char c) {
    clearCurrentChar();
    if (c == 0) {
        return;
    }
    if (c == 0x0D) {
        charPos = 0;
        linePos += 10;
        if (linePos > inputEndLine) {
            linePos = inputStartLine;
        }
        printInputCursor();
        return;
    }
    if (c == 0x08) {
        charPos -= 6;
        if (charPos < inputStartCol) {
            linePos -= 10;
            if (linePos < inputStartLine) {
                linePos = inputStartLine;
            }
            charPos = inputStartCol;
        }
        clearCurrentChar();
        printInputCursor();
        return;
    }
    Heltec.display->setColor(WHITE);
    Heltec.display->drawString(charPos, linePos, String(c));
    Heltec.display->display();
    charPos += 6;
    if (charPos > inputEndCol) {
        charPos = inputStartCol;
        linePos += 10;
        if (linePos > inputEndLine) {
            linePos = inputStartLine;
        }
    }
    printInputCursor();

}

void DisplayController::printInputCursor() {
    Heltec.display->drawString(charPos, linePos, "_");
    Heltec.display->display();
}

void DisplayController::clearInputKb(int startLine, int startCol, int endLine, int endCol) {
    Heltec.display->setColor(BLACK);
    Heltec.display->fillRect(startCol, startLine, endCol, endLine);
    Heltec.display->display();
    Heltec.display->setColor(WHITE);
}

void DisplayController::setTextCursor(int line, int col) {
    clearCurrentChar();
    linePos = line;
    charPos = col;
}


void DisplayController::setupInputKb(int startLine, int startCol, int endLine, int endCol) {
    inputStartLine = startLine;
    inputStartCol = startCol;
    inputEndLine = endLine;
    inputEndCol = endCol;
    setTextCursor(inputStartLine, inputStartCol);
    printInputCursor();
}

void DisplayController::clear() {
    Heltec.display->clear();
    linePos = 0;
}