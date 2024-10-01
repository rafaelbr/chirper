//
// Created by Rafael Brasileiro de Araujo on 06/09/24.
//
#include "app_frames.h"
#include "images.h"

int framesCount = 3;

FrameCallback frames[] = {
    initLogoFrame,
    initFrame,
    sendMessageFrame
};

int overlaysCount = 0;
OverlayCallback overlays[] = {};

/********** Keyboard Action Functions **************/

void upFunction() {
    int* inputs = framesInput[display_controller->getCurrentFrame()];

    currentInput--;
    if (currentInput < 0) {
        currentInput = inputCounts[display_controller->getCurrentFrame()] - 1;
    }

    display_controller->setInputActive(inputs[currentInput]);
    keyboard_controller->clearBuffer();

}

void downFunction() {
    int* inputs = framesInput[display_controller->getCurrentFrame()];

    currentInput++;
    if (currentInput >= inputCounts[display_controller->getCurrentFrame()]) {
        currentInput = 0;
    }

    display_controller->setInputActive(inputs[currentInput]);
    keyboard_controller->clearBuffer();
}

void leftFunction() {

}

void rightFunction() {

}

void enterFunction() {
    switch (display_controller->getCurrentFrame()) {
        case INIT_SCREEN:
        case INIT_LOGO:
            break;
        case MESSAGE_SCREEN:
            Serial.println("Sending...");
            lora_controller->prepareSendData(display_controller->getInputConfig(MAIN_SCREEN_INPUT_MESSAGE).buffer);
            break;
    }

}

void setupFrames(DisplayController* displayC, KeyboardController* keyboardC, LoRaWanController* loraC) {
    display_controller = displayC;
    keyboard_controller = keyboardC;
    lora_controller = loraC;
    displayC->setFrames(frames, framesCount);
    displayC->setOverlays(overlays, overlaysCount);

    //register all screens inputs
    displayC->addInputConfig("Device ID: ", 0, 1, ArialMT_Plain_10, true);
    displayC->addInputConfig("Enter Message: ", 13,2, ArialMT_Plain_10, true);
}

void initLogoFrame(ScreenDisplay *display, DisplayUiState* state, int16_t x, int16_t y) {
    display->drawXbm(32, 0, logo_width, logo_height, logo_bits);
    display->drawString(5, 50, "Message Network Device");
}

void initFrame(ScreenDisplay *display, DisplayUiState* state, int16_t x, int16_t y) {
    display->drawString(0, 0, initScreenBuffer);
}

void sendMessageFrame(ScreenDisplay *display, DisplayUiState* state, int16_t x, int16_t y) {

    display_controller->updateInput(MAIN_SCREEN_INPUT_MESSAGE, keyboard_controller);
    display_controller->updateInput(MAIN_SCREEN_INPUT_DEVICE, keyboard_controller);

    //setup initial input
    if (!display_controller->getFrameInitialization()) {
        display_controller->setFrameInitilized();
        currentInput = 0;
        display_controller->setInputActive(MAIN_SCREEN_INPUT_DEVICE);
    }

}

void screenFlow() {
    delay(2000);
    display_controller->showFrame(INIT_SCREEN);
}

void addInitMessage(String message) {
    initScreenBuffer += message + "\n";
}

