
#include "modules/BoardController.h"
#include "modules/LoRaWanController.h"
#include "modules/DisplayController.h"
#include "devices.h"
#include "main.h"

uint64_t devEUI =  DEVICE_TDECK_915M_0001_DEVEUI ;
uint64_t joinEUI = DEVICE_TDECK_915M_0001_JOINEUI;
uint8_t appKEY[] = { DEVICE_TDECK_915M_0001_APPKEY };
uint8_t NwkKEY[] = { DEVICE_TDECK_915M_0001_NWKKEY };

BoardController boardController;
LoRaWanController loRaWanController;
DisplayController displayController;

void setup()
{
    boardController.begin();
    displayController.begin();
    loRaWanController.begin(devEUI, joinEUI, appKEY, NwkKEY);

    Serial.println(F("Ready!\n"));

}


void loop()
{
    loRaWanController.sendTestMessage();
    displayController.println("Sending uplink");
    displayController.println("Uplink complete");
    delay(1000);
}