//
// Created by Rafael Brasileiro de Araujo on 25/08/24.
//

#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <Arduino.h>
#include "heltec.h"

#define BUTTON_A 12
#define BUTTON_B 13

class BoardController {

public:
    BoardController();
    ~BoardController();

    void begin();
 

};



#endif //BOARDCONTROLLER_H
