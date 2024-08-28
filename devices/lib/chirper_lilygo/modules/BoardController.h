/*************
* BoardController.h
* Created by Rafael Brasileiro de Araujo on 16/08/24.
*
* Handles the initialization of the board
*
* LilyGo T-DECK board has some specific controls and pins to handle modules initialization
* Needed to be used at the begining of setup on main sketch
*************/

#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <Arduino.h>
#include "../utils/utilities.h"

class BoardController {

public:
    BoardController();
    ~BoardController();

    void begin();
    void printWakeUpReason();
    void gotoSleep(uint32_t seconds);

private:
    int bootCount = 0;

};



#endif //BOARDCONTROLLER_H
