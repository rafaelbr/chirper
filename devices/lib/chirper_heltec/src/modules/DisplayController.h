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
#define HELTEC_DISPLAY_MAXCHARS 120

#define HELTEC_DISPLAY_LINEHEIGHT 12

#include "heltec.h"

class DisplayController {

public:

    DisplayController();
    ~DisplayController();

    /* Initialize display */
    void begin();

    /* Print text line to display */
    void println(String text);

    /* Print a char on display and add to input buffer */
    void printCharSequence(char c);

    /* Initialize new input keyboard area */
    void setupInputKb(int startLine, int startCol, int endLine, int endCol);

    /* Clear input keyboard area */
    void clearInputKb(int startLine, int startCol, int endLine, int endCol, bool clearBuffer = false);

    /* Set text cursor position */
    void setTextCursor(int line, int col);

    /* Get current input buffer */
    String getInputBuffer();

    /* Clear display */
    void clear();

private:
    int linePos = 0;
    int charPos = 0;

    int inputStartLine = 0;
    int inputStartCol = 0;

    int inputEndLine = 0;
    int inputEndCol = 0;

    //current input buffer
    char inputBuffer[255] = {0};
    //current input buffer index - points to the last char in the buffer
    int inputBufferIndex;

    void printInputCursor();
    void clearCurrentChar();
    void addCharToBuffer(char c);
    void removeLastCharFromBuffer();


};



#endif //DISPLAYCONTROLLER_H
