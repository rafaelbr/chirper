//
// Created by Rafael Brasileiro de Araujo on 26/08/24.
//

#include <unity.h>
#include <Arduino.h>
#include "images.h"
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

void test_drawImage() {
    displayController.drawImage(32, 0, logo_width, logo_height, logo_bits);
    //displayController.drawImage(0, 0, logo_alt_width, logo_alt_height, logo_alt_bits);
    displayController.setTextCursor(50, 5);
    displayController.println("Message Network Device");
    delay(2000);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_println);
    RUN_TEST(test_drawImage);
    UNITY_END();
}

void loop() {
    // do nothing
}