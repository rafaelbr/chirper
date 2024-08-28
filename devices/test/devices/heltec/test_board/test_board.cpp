//
// Created by Rafael Brasileiro de Araujo on 28/08/24.
//

#include "unity.h"
#include <Arduino.h>
#include "modules/BoardController.h"

#define TEST_TIME 5000

BoardController boardController;

void setUp(void) {
    boardController.begin(false);
}

void tearDown(void) {
    // clean stuff up here
}

void test_read_button_low() {
    Serial.println("Testing read button low");
    bool button1 = boardController.readButton(COMMAND_BTN1);
    bool button2 = boardController.readButton(COMMAND_BTN2);
    bool button3 = boardController.readButton(COMMAND_BTN3);
    delay(2000);
    TEST_ASSERT_EQUAL(false, button1);
    TEST_ASSERT_EQUAL(false, button2);
    TEST_ASSERT_EQUAL(false, button3);
}

void test_read_button1_high() {
    int time = 0;
    Serial.println("Testing read button1 high... please press PRG button on board...");
    bool state = false;
    while (time < TEST_TIME && !state) {
        state = boardController.readButton(COMMAND_BTN1);
        delay(100);
        time += 100;
    }
    time = 0;
    TEST_ASSERT_EQUAL(true, state);
}

void test_read_button2_high() {
    int time = 0;
    Serial.println("Testing read button2 high... please press YELLOW button on board...");
    bool state = false;
    while (time < TEST_TIME && !state) {
        state = boardController.readButton(COMMAND_BTN2);
        delay(100);
        time += 100;
    }
    time = 0;
    TEST_ASSERT_EQUAL(true, state);
}

void test_read_button3_high() {
    int time = 0;
    Serial.println("Testing read button3 high... please press BLUE button on board...");
    bool state = false;
    while (time < TEST_TIME && !state) {
        state = boardController.readButton(COMMAND_BTN3);
        delay(100);
        time += 100;
    }
    time = 0;
    TEST_ASSERT_EQUAL(true, state);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_read_button_low);
    RUN_TEST(test_read_button1_high);
    RUN_TEST(test_read_button2_high);
    RUN_TEST(test_read_button3_high);
    UNITY_END();
}

void loop() {
}