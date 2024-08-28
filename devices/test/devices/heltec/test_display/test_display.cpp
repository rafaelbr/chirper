//
// Created by Rafael Brasileiro de Araujo on 26/08/24.
//

#include <unity.h>
#include <Arduino.h>
#include "modules/BoardController.h"
#include "modules/DisplayController.h"

BoardController boardController;
DisplayController displayController;

void setUp(void) {
    boardController.begin();
    displayController.begin();
    displayController.clear();
}

void tearDown(void) {
    // clean stuff up here
}

void test_println() {
    displayController.println("Testing Display Controller...");
    delay(2000);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_println);
    UNITY_END();
}

void loop() {
    // do nothing
}