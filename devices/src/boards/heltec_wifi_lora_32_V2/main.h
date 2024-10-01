//
// Created by Rafael Brasileiro de Araujo on 12/08/24.
//

#ifndef MAIN_H
#define MAIN_H

#include <modules/BoardController.h>
#include <modules/LoRaWanController.h>
#include <modules/KeyboardController.h>
#include <modules/DisplayController.h>
#include "ui/images.h"
#include "ui/app_frames.h"
#include "devices.h"

static void prepareTxFrame( uint8_t port );
void displayPrintLn(String text);
void generateMessageScreen();


/******* LoRaWAN Parameters *******/
/* OTAA parameters */

static uint8_t devEUI[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_DEVEUI };
static uint8_t appEUI[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_JOINEUI };
static uint8_t appKEY[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_APPKEY };


static BoardController boardController;
static DisplayController displayController;
static LoRaWanController loraWanController(devEUI, appEUI, appKEY);
static KeyboardController keyboardController;


static bool isLoRaJoined = false;

static String deviceIdInput = "";
static String messageInput = "";

static TaskHandle_t* setupTaskHandle;
static TaskHandle_t* loraTaskHandle;
static TaskHandle_t* keyboardTaskHandle;

static SemaphoreHandle_t loraSemaphore;



#endif //MAIN_H
