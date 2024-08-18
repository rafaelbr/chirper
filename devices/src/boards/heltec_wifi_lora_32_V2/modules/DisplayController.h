/*************
* DisplayController.h
* Created by Rafael Brasileiro de Araujo on 16/08/24.
*
* Handles display initialization and printing mechanics
*
* Uses default Heltec initialization mechanism only for display
*************/

#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#define HELTEC_DISPLAY_MAXLINES 50


#include "heltec.h"


class DisplayController {

public:

    DisplayController();
    ~DisplayController();

    void begin();
    void println(String text);
    void clear();
    void update();

private:
    int linePos = HELTEC_DISPLAY_MAXLINES;

};



#endif //DISPLAYCONTROLLER_H
