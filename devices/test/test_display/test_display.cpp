//
// Created by Rafael Brasileiro de Araujo on 26/08/24.
//

#include "unity.h"
#include "../../src/boards/heltec_wifi_lora_32_V2/modules/BoardController.h"
#include "../../src/boards/heltec_wifi_lora_32_V2/modules/DisplayController.h"

BoardController boardController;
DisplayController displayController;

void setUp(void) {
    boardController.begin();
}

void tearDown(void) {
}

void test_printOnScreen(void) {
    displayController.println("Testing display...");
    delay(2000);
    displayController.clear();
    delay(2000);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_printOnScreen);
    UNITY_END();
}

void loop() {
}



