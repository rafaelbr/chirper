/*************
* DisplayController.h
* Created by Rafael Brasileiro de Araujo on 16/08/24.
*
* Control the TFT Display for T-Deck and take care of its initialization
*
* Uses TFT_eSPI library
*************/

//
// Created by Rafael Brasileiro de Araujo on 17/08/24.
//

#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "../utils/utilities.h"

#define DISPLAY_MAX_LINES 20;

class DisplayController {

public:
    DisplayController();
    ~DisplayController();

    void begin();

    void setBrightness(uint8_t brightness);

    void println(String text);

private:
    int linePos = 0;

    TFT_eSPI* tft;

};



#endif //DISPLAYCONTROLLER_H
