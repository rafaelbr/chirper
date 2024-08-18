#include <Arduino.h>
#include "modules/LoRaWanController.h"
#include "modules/DisplayController.h"
#include "devices.h"
#include "main.h"

/******* LoRaWAN Parameters *******/
/* OTAA parameters */

uint8_t devEUI[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_DEVEUI };
uint8_t appEUI[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_JOINEUI };
uint8_t appKEY[] = { DEVICE_HELTEC_WIFI_LORA_32_V2_0001_APPKEY };


LoRaWanController loraWanController(devEUI, appEUI, appKEY);
DisplayController displayController;

//downlink data handle
//heltec lorawan stack has an extern linkage for downlink handle... so it needs to stay on sketch
//figuring out how to manage this...
void downLinkDataHandle(McpsIndication_t *mcpsIndication)
{
    Serial.printf("+REV DATA:%s,RXSIZE %d,PORT %d\r\n",mcpsIndication->RxSlot?"RXWIN2":"RXWIN1",mcpsIndication->BufferSize,mcpsIndication->Port);
    Serial.print("+REV DATA:");
    for(uint8_t i=0;i<mcpsIndication->BufferSize;i++)
    {
        Serial.printf("%02X",mcpsIndication->Buffer[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);

    displayController.begin();
    loraWanController.begin();

    displayController.clear();

    displayController.println("Init OK");


}

void loop() {
    auto state = loraWanController.loRaWANStateMachine();
}