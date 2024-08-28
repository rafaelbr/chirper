//
// Created by Rafael Brasileiro de Araujo on 28/08/24.
//

#include <unity.h>
#include <Arduino.h>
#include "modules/BoardController.h"
#include "modules/KeyboardController.h"

#define TEST_TIME 5000

BoardController boardController;
KeyboardController keyboardController;

void dummy() {
}


void setUp(void) {
	boardController.begin(false);
    delay(2000);
    keyboardController.begin();
    keyboardController.setFunctions(dummy, dummy, dummy, dummy, dummy);
}

void tearDown(void) {
    // clean stuff up here
}

void test_readKey() {
    // Test readKey - A key is pressed
    Serial.println("Press A key in two seconds...");
    char key = 0;
    int time = 0;
    while (key == 0 && time < TEST_TIME) {
        key = keyboardController.readKey();
        delay(100);
        time+=100;
    }
    TEST_ASSERT_EQUAL(0x61, key);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_readKey);
    UNITY_END();
}

void loop() {
    // do nothing
}
