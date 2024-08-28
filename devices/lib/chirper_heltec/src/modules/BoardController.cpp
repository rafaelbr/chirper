//
// Created by Rafael Brasileiro de Araujo on 28/08/24.
//

#include "BoardController.h"

BoardController::BoardController() {
}

BoardController::~BoardController() {
}

void BoardController::begin(bool displayEnable) {
    if (!displayEnable) {
        //we need to initialize I2C bus
        Wire.begin(BOARD_SDA, BOARD_SCL);
    }

    Heltec.begin(displayEnable, false, true);

    //initialize buttons
    pinMode(COMMAND_BTN1, INPUT);
    pinMode(COMMAND_BTN2, INPUT);
    pinMode(COMMAND_BTN3, INPUT);

}

bool BoardController::readButton(int button) {
    //PRG button is inverted on board
    if (button == COMMAND_BTN1) {
        return digitalRead(button) == LOW;
    }
    return digitalRead(button);
}
