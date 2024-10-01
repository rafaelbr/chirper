#include <Arduino.h>
#include "main.h"


/****** TASKS ******/

//Initialization task
void initializeTask(void *pvParameters)
{
    xSemaphoreTake(loraSemaphore, portMAX_DELAY);
    displayController.showFrame(INIT_LOGO);
    delay(2000);

    displayController.showFrame(INIT_SCREEN);
    //delay(1000);
    addInitMessage("Starting up system...");

    // this is needed to wait for I2C to be ready again after display initialization
    delay(100);

    // initialize and configure keyboard actions
    keyboardController.begin();
    keyboardController.setFunctions(upFunction, downFunction, leftFunction, rightFunction, enterFunction);

    delay(1000);

    xSemaphoreGive(loraSemaphore);
    vTaskDelete(NULL);
}

//LoRaWAN State Machine Task
void loraStateTask(void *pvParameters) {
    loraWanController.begin();
    xSemaphoreTake(loraSemaphore, portMAX_DELAY);
    while(1) {

        auto state = loraWanController.loRaWANStateMachine();

        if (state == DEVICE_STATE_JOIN) {
            addInitMessage("LoRAWan Joining...");
            continue;
        }

        if (state == DEVICE_STATE_SEND) {
            if (!isLoRaJoined) {
                addInitMessage("Joined network!!!");
                addInitMessage("Initializing UI...");
                isLoRaJoined = true;
                delay(1000);
                displayController.showFrame(MESSAGE_SCREEN);
                continue;
            }
        }
        vTaskDelay(1);
    }
    xSemaphoreGive(loraSemaphore);
}

void keyboardReadTask(void *pvParameters) {
    while(1) {
        keyboardController.readCharAndWriteToBuffer();
        delay(100);
    }
}

void setup() {
    boardController.begin();
    //initialize peripherals
    setupFrames(&displayController, &keyboardController, &loraWanController);
    displayController.begin();

    loraSemaphore = xSemaphoreCreateBinary();

    //initialize tasks
    xTaskCreate(
        initializeTask,
        "initializeTask",
        2048,
        NULL,
        1,
        setupTaskHandle);

    xTaskCreate(
        loraStateTask,
        "loraStateTask",
        2048,
        NULL,
        1,
        loraTaskHandle);

    xTaskCreate(
        keyboardReadTask,
        "keyboardReadTask",
        2048,
        NULL,
        1,
        keyboardTaskHandle);

    xSemaphoreGive(loraSemaphore);


}

void loop() {

    //UI Update -- don't change this
    int remainingTimeBudget = displayController.updateUI();

    if (remainingTimeBudget > 0) {
        // You can do some work here
        // Don't do stuff if you are below your
        // time budget.
        delay(remainingTimeBudget);
    }

}