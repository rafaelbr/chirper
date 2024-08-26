//
// Created by Rafael Brasileiro de Araujo on 25/08/24.
//

#include "BoardController.h"


BoardController::BoardController() {
}

BoardController::~BoardController() {
}

void BoardController::begin() {
    // Initialize the Heltec board - Display and Serial only
    Heltec.begin(true, false);

    // Set the button pins as input
    //pinMode(BUTTON_A, INPUT);
    //pinMode(BUTTON_B, INPUT);
}