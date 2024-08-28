//
// Created by Rafael Brasileiro de Araujo on 28/08/24.
//

#include "SDCardController.h"

SDCardController::SDCardController() {
}

SDCardController::~SDCardController() {

}

void SDCardController::begin() {
    spi1.begin(SDCARD_SCK, SDCARD_MISO, SDCARD_MOSI, SDCARD_CS);
    if (!SD.begin(2, spi1)) {
        Serial.println("SD Card Mount Failed");
        return;
    }
    Serial.println("SD Card Mounted");
}

void SDCardController::writeData(String filepath, String data) {
    File file = SD.open(filepath, FILE_WRITE);
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }
    if (file.print(data)) {
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

String SDCardController::readData(String filepath) {
    File file = SD.open(filepath);
    if (!file) {
        Serial.println("Failed to open file for reading");
        return "";
    }
    String data = "";
    while (file.available()) {
        data += (char)file.read();
    }
    file.close();
    return data;
}