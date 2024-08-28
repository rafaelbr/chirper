//
// Created by Rafael Brasileiro de Araujo on 12/08/24.
//

#ifndef MAIN_H
#define MAIN_H

#include <modules/BoardController.h>

#include "modules/LoRaWanController.h"
#include "modules/DisplayController.h"
#include "modules/KeyboardController.h"
#include "devices.h"

static void prepareTxFrame( uint8_t port );
void displayPrintLn(String text);
void generateMessageScreen();


/******* LoRaWAN Parameters *******/
/* OTAA parameters */

uint8_t devEUI[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_DEVEUI };
uint8_t appEUI[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_JOINEUI };
uint8_t appKEY[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_APPKEY };


BoardController boardController;
LoRaWanController loraWanController(devEUI, appEUI, appKEY);
DisplayController displayController;
KeyboardController keyboardController;

int currentInput = 0;
int currentInputStartLine[] = {13, 40};
int currentInputEndLine[] = {25, 64};

bool isLoRaJoined = false;

String deviceIdInput = "";
String messageInput = "";

#endif //MAIN_H
