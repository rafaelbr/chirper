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
    if (linePos > 50) {
        Heltec.display->clear();
        linePos = 0;
    }
    Heltec.display->drawString(0, linePos, text);
    Heltec.display->display();
    linePos += 10;
}

void DisplayController::clear() {
    Heltec.display->clear();
    linePos = 0;
}