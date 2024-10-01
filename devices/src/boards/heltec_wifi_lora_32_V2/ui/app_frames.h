//
// Created by Rafael Brasileiro de Araujo on 06/09/24.
//

#ifndef APP_FRAMES_H
#define APP_FRAMES_H

#include <modules/DisplayController.h>
#include <modules/KeyboardController.h>
#include <modules/LoRaWanController.h>

#define INIT_LOGO 0
#define INIT_SCREEN 1
#define MESSAGE_SCREEN 2

//input defines
#define MAIN_SCREEN_INPUT_DEVICE 0
#define MAIN_SCREEN_INPUT_MESSAGE 1


static DisplayController* display_controller;
static KeyboardController* keyboard_controller;
static LoRaWanController* lora_controller;

static int framesInput[][5] = {
    {},
    {},
    {MAIN_SCREEN_INPUT_DEVICE, MAIN_SCREEN_INPUT_MESSAGE}
};

static int inputCounts[] = {0, 0, 2};

static int currentInput;

static String initScreenBuffer = "Initializing...\n";



void setupFrames(DisplayController* displayController, KeyboardController* keyboardController, LoRaWanController* loraController);

void initLogoFrame(ScreenDisplay *display, DisplayUiState* state, int16_t x, int16_t y);
void initFrame(ScreenDisplay *display, DisplayUiState* state, int16_t x, int16_t y);
void sendMessageFrame(ScreenDisplay *display, DisplayUiState* state, int16_t x, int16_t y);

void addInitMessage(String message);

//action functions
void upFunction();
void downFunction();
void leftFunction();
void rightFunction();
void enterFunction();

#endif //APP_FRAMES_H
