/*************
* LoRaWanController.cpp
* Created by Rafael Brasileiro de Araujo on 16/08/24.
*
* Handles initialization and configuration of LoRa Module and LoRaWAN stack (Init, Join, Send, Receive)
* Because of implementation of Heltec ESP32 Library, we will stick to LoRaWAN MAC 1.0.3, I need fo figure
* out how to implement 1.1 stack using this library (manage nonces and session persistence)
*
* The Heltec LoRa library implements Class A,B and C, but we will stick to Class A for now to be
* retrocompatible with other boards and libraries.
* Because of this, we will manage a single TX every time window (maybe 30s) to open a RX window and update
* available devices and messages for the current device.
*
* This class is only compatible with Heltec ESP32 LoRa boards.
*
* Notice the Heltec stack for LoRaWAN are made in a state machine architecture controlled during loop phase
* on sketch. So, is obligatory to call loRaWANStateMachine() on loop phase to update the state machine. Also, we cannot
* use any delays on loop phase here and send data are made on a fixed time window (appTxDutyCycle).
*************/

#include "LoRaWanController.h"

/******** Heltec LoRaWAN parameters **********
 * Heltec LoRa stack need to explicit declare LoRaWAN needed variables (they have an extern on the class my lord!!!! WHY?????)
 * Why they can't put this on a constructor or a function??? WHYYYYYY????????
 *
 */

//LoRaWAN MAC 1.0.x parameters
//Should be configured in ChirpStack Server for each device
//AppEUI is the JoinEUI
uint8_t devEui[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appEui[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appKey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// Bogus code to avoid compilation errors...
// They are used in ABP mode, but we are using OTAA
// Note we will need nwkSKey on LoRaWAN MAC 1.1 later (to be implemented)
uint8_t nwkSKey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appSKey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint32_t devAddr = 0x0000000;

//LoRaWan channelsmask, default channels 0-7
//Should be compatible with Gateway configuration (considering an 8-channel module)
uint16_t userChannelsMask[6]={ 0x00FF,0x0000,0x0000,0x0000,0x0000,0x0000 }; //US915 Band 1

//LoRaWan Region
//Should be configured based on LoRa network specification, must be unique between devices in same gateway
//US915 is default used on Brazil (ANATEL regulation)
LoRaMacRegion_t loraWanRegion = LORAMAC_REGION_US915;

// Device class, choose A here for compatibility reasons
// Remember... Class A only opens a RX window after a TX window!!!
DeviceClass_t  loraWanClass = CLASS_C;

//the application data transmission duty cycle.  value in [ms].
//this is needed for the current LoRa stack from Heltec... they made things to run on a fixed state machine with
//duty cycles... another bad design decision!!!!
uint32_t appTxDutyCycle = 2000;

//Is OTAA ou ABP??? Stick to OTAA is recommended
bool overTheAirActivation = true;

//Should enable ADR?
//Adaptive Data Rate is a LoRaWAN feature that allows the network to optimize the data rate and transmit power for each device
//Enabled by default
bool loraWanAdr = true;

// Indicates if the node is sending confirmed or unconfirmed messages
// Default is true (need to figure out if this is need or not)
bool isTxConfirmed = true;

// Application port
// Still figuring out if its needed or not
uint8_t appPort = 2;


/*!
* Number of trials to transmit the frame, if the LoRaMAC layer did not
* receive an acknowledgment. The MAC performs a datarate adaptation,
* according to the LoRaWAN Specification V1.0.2, chapter 18.4, according
* to the following table:
*
* Transmission nb | Data Rate
* ----------------|-----------
* 1 (first)       | DR
* 2               | DR
* 3               | max(DR-1,0)
* 4               | max(DR-1,0)
* 5               | max(DR-2,0)
* 6               | max(DR-2,0)
* 7               | max(DR-3,0)
* 8               | max(DR-3,0)
*
* Note, that if NbTrials is set to 1 or 2, the MAC will not decrease
* the datarate, in case the LoRaMAC layer did not receive an acknowledgment
*/
uint8_t confirmedNbTrials = 4;

LoRaWanController::LoRaWanController(uint8_t DevEUI[], uint8_t JoinEUI[], uint8_t AppKey[]) {
    //copying parameters to class variables
    memcpy(devEui, DevEUI, 8);
    memcpy(appEui, JoinEUI, 8);
    memcpy(appKey, AppKey, 16);
}

LoRaWanController::~LoRaWanController() {

}

void LoRaWanController::begin() {
    //turn on LoRa module
    Mcu.begin(HELTEC_BOARD,SLOW_CLK_TPYE);
}


void LoRaWanController::prepareSendData(String message, int size) {
    appDataSize = size;
    for (int i = 0; i < size; i++) {
        appData[i] = message[i];
    }
}

eDeviceState_LoraWan LoRaWanController::loRaWANStateMachine() {
    switch( deviceState ) {
        case DEVICE_STATE_INIT:
        {
            LoRaWAN.init(loraWanClass,loraWanRegion);
            //both set join DR and DR when ADR off
            LoRaWAN.setDefaultDR(3);
            Serial.println("LoRA INIT");
            break;
        }
        case DEVICE_STATE_JOIN:
        {
            LoRaWAN.join();
            Serial.println("LoRAWan Joining...");
            break;
        }
        case DEVICE_STATE_SEND:
        {
            //Dummy TX packet
            /*appDataSize = 4;
            appData[0] = 0x00;
            appData[1] = 0x01;
            appData[2] = 0x02;
            appData[3] = 0x03;*/

            //send appData message
            if (appDataSize > 0) {
                LoRaWAN.send();
                Serial.println("Sending TX...");
            }

            appDataSize = 0;
            deviceState = DEVICE_STATE_CYCLE;
            break;
        }
        case DEVICE_STATE_CYCLE:
        {
            // Schedule next packet transmission
            txDutyCycleTime = appTxDutyCycle + randr( -APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND );
            LoRaWAN.cycle(txDutyCycleTime);
            deviceState = DEVICE_STATE_SLEEP;
            break;
        }
        case DEVICE_STATE_SLEEP:
        {
            LoRaWAN.sleep(loraWanClass);
            break;
        }
        default:
        {
            deviceState = DEVICE_STATE_INIT;
            break;
        }
    }
    return deviceState;
}
