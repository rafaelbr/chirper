//
// Created by Rafael Brasileiro de Araujo on 17/08/24.
//

#include "DisplayController.h"


DisplayController::DisplayController() {
    tft = new TFT_eSPI();
}

DisplayController::~DisplayController() {
    //deallocate memory from pointers
    //needs to be checked if it is necessary... C++ (and Arduino Wiring/Processing hybrid does not have
    //a garbage collector system, so we need to take care of pointers somehow... but because this class stands
    //instantiated the whole device life, maybe it is not necessary to deallocate memory.
    delete tft;
    tft = nullptr;
}

void DisplayController::begin() {
    Serial.println("Init display");

    tft->init();
    // Adjust backlight
    pinMode(BOARD_BL_PIN, OUTPUT);
    setBrightness(16);

    tft->setRotation( 1 );
    tft->fillScreen(TFT_BLUE);
    tft->setTextColor(TFT_WHITE, TFT_BLUE);
    tft->setTextFont(1);
    println("Init TFT OK");
}

// LilyGo  T-Deck  control backlight chip has 16 levels of adjustment range
// The adjustable range is 0~15, 0 is the minimum brightness, 15 is the maximum brightness
void DisplayController::setBrightness(uint8_t brightness) {
    static uint8_t level = 0;
    static uint8_t steps = 16;
    if (brightness == 0) {
        digitalWrite(BOARD_BL_PIN, 0);
        delay(3);
        level = 0;
        return;
    }
    if (level == 0) {
        digitalWrite(BOARD_BL_PIN, 1);
        level = steps;
        delayMicroseconds(30);
    }
    int from = steps - level;
    int to = steps - brightness;
    int num = (steps + to - from) % steps;
    for (int i = 0; i < num; i++) {
        digitalWrite(BOARD_BL_PIN, 0);
        digitalWrite(BOARD_BL_PIN, 1);
    }
    level = brightness;
}

void DisplayController::println(String text) {
    int maxLinePos = DISPLAY_MAX_LINES;
    maxLinePos *= 10;
    //check if display reach end of screen
    if (linePos > maxLinePos) {
        tft->fillScreen(TFT_BLUE);
        linePos = 0;
    }
    tft->drawString(" " + text, 10, linePos);
    linePos += 10;
}
