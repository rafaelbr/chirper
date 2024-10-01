/*************
* DisplayController.h
* Created by Rafael Brasileiro de Araujo on 16/08/24.
*
* Handles display initialization and printing mechanics
*
* Uses default Heltec initialization mechanism only for display
*************/
#include <HT_SSD1306Wire.h>
#include "HT_DisplayUi.h"
#include "modules/KeyboardController.h"


#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#define HELTEC_DISPLAY_MAXLINES 50
#define HELTEC_DISPLAY_MAXCHARS 120

#define HELTEC_DISPLAY_LINEHEIGHT 12

const uint8_t activeSymbol[] PROGMEM = {
    0B00000000,
    0B00000000,
    0B00011000,
    0B00100100,
    0B01000010,
    0B01000010,
    0B00100100,
    0B00011000
};

const uint8_t inactiveSymbol[] PROGMEM = {
    0B00000000,
    0B00000000,
    0B00000000,
    0B00000000,
    0B00011000,
    0B00011000,
    0B00000000,
    0B00000000
};

struct InputConfig {
    String label;
    int startLinePos;
    int maxLines;
    const uint8_t *fontData;
    bool shouldClearBuffer;
    bool isActive;
    String buffer;
};


class DisplayController {

public:

    DisplayController();
    ~DisplayController();

    /* Initialize display */
    void begin();

    /**** Display Functions ****/

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

    /* Draw image on display */
    void drawImage(int x, int y, int w, int h, const uint8_t *data);

    /****** UI Functions ******/

    /* Configure UI parameters for screen flow*/
    void configureUI();

    /* Gets the display object */
    ScreenDisplay* getDisplay();

    /* Sets frame functions to be displayed */
    void setFrames(FrameCallback* frames, int frameCount);

    /* Sets overlay functions to be displayed */
    void setOverlays(OverlayCallback* overlays, int overlayCount);

    void showFrame(int frameIndex);

    int getCurrentFrame() const {
        return currentFrame;
    }

    bool getFrameInitialization() {
        return frameInitialized;
    }

    void setFrameInitilized();

    int addInputConfig(String label, int startLinePos, int maxLines, const uint8_t *fontData, bool shouldClearBuffer);

    InputConfig getInputConfig(int index);

    void updateInput(int inputConfigIndex, KeyboardController* kbController);

    void setInputActive(int inputConfigIndex);

    int16_t updateUI();

private:

    String inputBuffer;
    int inputBufferIndex = 0;
    int currentFrame;

    /**** non UI control parameters ****/
    int linePos = 0;
    int charPos = 0;

    int inputStartLine = 0;
    int inputStartCol = 0;

    int inputEndLine = 0;
    int inputEndCol = 0;

    InputConfig inputConfigs[255];
    int inputConfigsCount = 0;

    SSD1306Wire*  display;
    DisplayUi* ui;

    bool frameInitialized = false;

    void printInputCursor();
    void clearCurrentChar();
    void addCharToBuffer(char c);
    void removeLastCharFromBuffer();

    void getFontHeight(uint8_t fontData);

};



#endif //DISPLAYCONTROLLER_H
