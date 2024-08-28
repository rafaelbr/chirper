//
// Created by Rafael Brasileiro de Araujo on 28/08/24.
//

#include <unity.h>
#include <Arduino.h>
#include "modules/BoardController.h"
#include "modules/LoRaWanController.h"
#include "devices.h"

/******* LoRaWAN Parameters *******/
/* OTAA parameters */

uint8_t devEUI[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_DEVEUI };
uint8_t appEUI[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_JOINEUI };
uint8_t appKEY[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_APPKEY };


LoRaWanController loraWanController(devEUI, appEUI, appKEY);

BoardController boardController;

void setUp(void) {
    boardController.begin(false);
}

void tearDown(void) {
    // clean stuff up here
}

void test_join() {
    // Test join
    loraWanController.begin();
    bool isLoRaJoined = false;
    while(!isLoRaJoined) {
        auto state = loraWanController.loRaWANStateMachine();
        if (state == DEVICE_STATE_JOIN) {
            Serial.println("LoRAWan Joining...");
        }

        if (state == DEVICE_STATE_SEND && !isLoRaJoined) {
            isLoRaJoined = true;
            Serial.println("LoRAWan Joined!");
            delay(1000);
            return;
        }
        delay(10);
    }


}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_join);
    UNITY_END();
}

void loop() {
    // do nothing
}

