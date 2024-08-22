/*************
* LoRaWanController.h
* Created by Rafael Brasileiro de Araujo on 16/08/24.
*
* Handles initialization and configuration of LoRa Module and LoRaWAN stack (Init, Join, Send, Receive)
* Because of implementation of Heltec ESP32 Library, we will stick to LoRaWAN MAC 1.0.3, I need fo figure
* out how to implement 1.1 stack using this library (manage nonces and session persistence)
*
* The Heltec LoRa library implements Class A, B and C. Because Class A goes to deep sleep after the second RX window,
* we are using Class C to keep the device awake and listening for messages.
*
* This class is only compatible with Heltec ESP32 LoRa boards.
*************/

//

//

#ifndef LORAWANCONTROLLER_H
#define LORAWANCONTROLLER_H

#include "LoRaWan_APP.h"

class LoRaWanController {
    public:
        LoRaWanController(uint8_t DevEUI[], uint8_t JoinEUI[], uint8_t AppKey[]);
        ~LoRaWanController();


        /*
         * Heltec LoRaWAN stack is implemented as a state machine
         * variable deviceState is updated every frame loop, so we need to control this here
         */
        eDeviceState_LoraWan loRaWANStateMachine();

        void begin();
        void sendDummyMessage();
        void prepareSendData(String message, int size);

     private:
        uint8_t* (*txFunction)(void);

};



#endif //LORAWANCONTROLLER_H
