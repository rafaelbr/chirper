//
// Created by Rafael Brasileiro de Araujo on 28/08/24.2
//

#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <Arduino.h>
#include <heltec.h>

#define SERIAL_BAUD 115200

#define BOARD_SDA 4
#define BOARD_SCL 15
#define COMMAND_BTN1 0
#define COMMAND_BTN2 12
#define COMMAND_BTN3 13

#define BAT_MEASURE_PIN 37
#define BAT_DIVIDER_PIN 21


class BoardController {
public:
    BoardController();
    ~BoardController();

    void begin(bool displayEnable = true);

    bool readButton(int button);

    int getBatteryLevel();
};



#endif //BOARDCONTROLLER_H
