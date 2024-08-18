/*************
* LoRaWanController.h
* Created by Rafael Brasileiro de Araujo on 16/08/24.
*
* Handles initialization and configuration of LoRa Module and LoRaWAN stack (Init, Join, Send, Receive)
* Implements all routines to initialize LoRa Module on Lilygo T-Deck (pins configurations) and
* configure RadioLib to initialize LoRaWan stack
*
* This device implements Class A LoRaWAN because RadioLib does not support Class B and Class C
*
* This module implements LoRaWAN MAC 1.1 with session and nonces persistence via ESP32 RTC memory
* using preferences API. Session persistence only works during device deep sleep and not for reboots.
* If a reboot occurs a new OTAA join will be required. (needs to be reviewed)
*************/

#ifndef LORAWANCONTROLLER_H
#define LORAWANCONTROLLER_H

#include <RadioLib.h>
#include <Preferences.h>

class LoRaWanController {

public:
    LoRaWanController();
    ~LoRaWanController();

    void begin(uint64_t DevEUI, uint64_t JoinEUI, uint8_t AppKey[], uint8_t NwkKey[]);;

    void sendTestMessage();

private:
    //Region and subBand configuration - Set to US915 - Brazil configuration
    //Must match gateway module
    const LoRaWANBand_t Region = US915;
    const uint8_t subBand = 1;

    //
    SX1262 *radio;
    Preferences store;
    LoRaWANNode *node;

    //decode result codes from RadioLib
    String stateDecode(const int16_t result);

    //helper to print debug strings
    void debug(bool failed, const __FlashStringHelper* message, int state, bool halt);

    //helper to dump array on serial
    void arrayDump(uint8_t *buffer, uint16_t len);
};



#endif //LORAWANCONTROLLER_H
