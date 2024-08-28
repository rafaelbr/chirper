//
// Created by Rafael Brasileiro de Araujo on 28/08/24.
//

#include <unity.h>
#include <Arduino.h>
#include "modules/BoardController.h"
#include "modules/SDCardController.h"

BoardController boardController;
SDCardController sdCardController;

void setUp(void) {
    boardController.begin(false);
    sdCardController.begin();
}

void tearDown(void) {
    // clean stuff up here
}

void test_write_read() {
    String filename = "/test.txt";
    String data = "Hello World!";
    sdCardController.writeData(filename, data);
    Serial.println("Data written");
    String readData = sdCardController.readData(filename);
    Serial.println("Data read");
    delay(2000);
    TEST_ASSERT_EQUAL_STRING(data.c_str(), readData.c_str());
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_write_read);
    UNITY_END();
}

void loop() {
}