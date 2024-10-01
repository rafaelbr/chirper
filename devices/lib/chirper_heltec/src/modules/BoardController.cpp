//
// Created by Rafael Brasileiro de Araujo on 28/08/24.
//

#include "BoardController.h"

BoardController::BoardController() {
}

BoardController::~BoardController() {
}

void BoardController::begin(bool displayEnable) {
    Wire.begin(BOARD_SDA, BOARD_SCL);
    Serial.begin(SERIAL_BAUD);
    //initialize buttons
    pinMode(COMMAND_BTN1, INPUT);
    pinMode(COMMAND_BTN2, INPUT_PULLDOWN);
    pinMode(COMMAND_BTN3, INPUT_PULLDOWN);

}

bool BoardController::readButton(int button) {
    //PRG button is inverted on board
    bool state = digitalRead(button);
    if (button == COMMAND_BTN1) {
        return state == LOW;
    }
    //Serial.println("Reading " + String(button) + ": " + digitalRead(button));
    return state;
}

int BoardController::getBatteryLevel() {
    float dividerRatio = 3.2; 	// Used measured values to determine the ratio
    Serial.println("Inside Battery::Measure");

    // 3.3 Volts is the theoretical value. The actual value depends on the
    // board's voltage regulator.
    float FS = 3.3 / 4095;		// Calculate the bit weight from Full Scale
    uint16_t MULT = 1000; 		// Convert to milliVolts
    delay(10);					// Allow things to stabilize

    // Make a measurement without the divider.
    uint16_t c  =  analogRead(BAT_MEASURE_PIN)*FS*MULT;
    Serial.println("Batt V (undivided): " + String( c ));
    digitalWrite(BAT_DIVIDER_PIN, LOW);
    delay(10);

    // Make a measurement with the divider.
    c  =  analogRead(BAT_MEASURE_PIN)*FS*MULT;
    Serial.println("Batt V (divided): " + String( c ));

    // Multiply the measured voltage by the divider ratio
    Serial.println("Batt V (calibrated): " + String( c * dividerRatio ));
    digitalWrite(BAT_DIVIDER_PIN, HIGH); // open divider
    return c * dividerRatio;
}
