//
// Created by Rafael Brasileiro de Araujo on 28/08/24.
//

#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <Arduino.h>
#include <heltec.h>

#define BOARD_SDA 4
#define BOARD_SCL 15
#define COMMAND_BTN1 0
#define COMMAND_BTN2 36
#define COMMAND_BTN3 37

class BoardController {
public:
    BoardController();
    ~BoardController();

    void begin(bool displayEnable = true);

    bool readButton(int button);
};



#endif //BOARDCONTROLLER_H
