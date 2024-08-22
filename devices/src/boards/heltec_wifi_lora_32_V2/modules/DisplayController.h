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
#define HELTEC_DISPLAY_MAXCHARS 100

#include "heltec.h"


class DisplayController {

public:

    DisplayController();
    ~DisplayController();

    void begin();
    void println(String text);
    void printCharSequence(char c);
    void setupInputKb(int startLine, int startCol, int endLine, int endCol);
    void clearInputKb(int startLine, int startCol, int endLine, int endCol);
    void setTextCursor(int line, int col);
    void clear();
    void update();

private:
    int linePos = 0;
    int charPos = 0;

    int inputStartLine = 0;
    int inputStartCol = 0;

    int inputEndLine = 0;
    int inputEndCol = 0;

    void printInputCursor();
    void clearCurrentChar();

};



#endif //DISPLAYCONTROLLER_H
