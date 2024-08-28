//
// Created by Rafael Brasileiro de Araujo on 28/08/24.
//

#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <Arduino.h>
#include <heltec.h>

#define BOARD_SDA 4
#define BOARD_SCL 15

class BoardController {
public:
    BoardController();
    ~BoardController();

    void begin(bool displayEnable = true);
};



#endif //BOARDCONTROLLER_H
