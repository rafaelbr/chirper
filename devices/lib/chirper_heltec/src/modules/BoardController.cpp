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

}
