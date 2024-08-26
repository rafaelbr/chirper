#include <Arduino.h>
#include "main.h"

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

/********** Keyboard Action Functions **************/

void upFunction() {
    currentInput--;
    if (currentInput < 0) {
        currentInput = 0;
    }
    else {
        displayController.clearInputKb(currentInputStartLine[currentInput], 0, currentInputEndLine[currentInput], HELTEC_DISPLAY_MAXCHARS);
    }
    displayController.setupInputKb(currentInputStartLine[currentInput], 0, currentInputEndLine[currentInput], HELTEC_DISPLAY_MAXCHARS);
}

void downFunction() {
    currentInput++;
    if (currentInput > 1) {
        currentInput = 1;
    }
    else {
        displayController.clearInputKb(currentInputStartLine[currentInput], 0, currentInputEndLine[currentInput], HELTEC_DISPLAY_MAXCHARS);
    }
    displayController.setupInputKb(currentInputStartLine[currentInput], 0, currentInputEndLine[currentInput], HELTEC_DISPLAY_MAXCHARS);
}

void leftFunction() {

}

void rightFunction() {

}

void enterFunction() {
    String input = displayController.getInputBuffer();
    loraWanController.prepareSendData(input, input.length());
    displayController.clear();
    displayController.setTextCursor(0, 0);
    displayController.println("Sending...");
    delay(5000);
    generateMessageScreen();

}

/********** Screen Creation **************/
// We decided to make a textual UI for this device because the size of screen
// So we are controlling all just with a label and input field
// DisplayController has some methods to handle this
void generateMessageScreen() {
    displayController.clear();
    displayController.setTextCursor(0, 0);
    displayController.println("To Device: ");
    displayController.setTextCursor(27, 0);
    displayController.println("Message: ");
    displayController.setupInputKb(currentInputStartLine[currentInput], 0, currentInputEndLine[currentInput], HELTEC_DISPLAY_MAXCHARS);
}

/********** Tasks **************/
// We are using FreeRTOS to manage tasks
void loraWanTask(void *pvParameters) {
    while (true) {
        auto state = loraWanController.loRaWANStateMachine();


        if (state == DEVICE_STATE_JOIN) {
            displayController.println("LoRAWan Joining...");
            continue;
        }

        if (state == DEVICE_STATE_SEND && !isLoRaJoined) {
            displayController.println("Joined network!!!");
            displayController.println("Initializing UI...");
            isLoRaJoined = true;
            continue;
        }
        vTaskDelay( pdMS_TO_TICKS( 10u ) );
    }
}

void setup() {

    //initialize peripherals
    //boardController.begin(); //need to be first - initializes board
    displayController.begin();
    loraWanController.begin();
    //sdCardController.begin();
    // this is needed to wait for I2C to be ready again after display initialization
    delay(100);

    // initialize and configure keyboard actions
    keyboardController.begin();
    keyboardController.setFunctions(upFunction, downFunction, leftFunction, rightFunction, enterFunction);

    //Starting up system....
    displayController.clear();
    displayController.println("Device ready!");
    displayController.println("Starting up system...");

    xTaskCreate(
        loraWanTask,
        "LoRaWAN StateMachine",
        4096,
        NULL,
        1,
        NULL
        );


}

void loop() {
    /*auto state = loraWanController.loRaWANStateMachine();

    */

    char c = keyboardController.readKey();
    if (c != 0) {
        displayController.printCharSequence(c);
    }
}