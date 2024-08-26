//
// Created by Rafael Brasileiro de Araujo on 25/08/24.
//

#include "SDCardController.h"

SDCardController::SDCardController() {

}

SDCardController::~SDCardController() {
}

void SDCardController::begin() {
				// Initialize the SD card
				spi1.begin(SDCARD_SCK, SDCARD_MISO, SDCARD_MOSI, SDCARD_CS);
				if (!SD.begin(SDCARD_CS, spi1)) {
								Serial.println("SD Card initialization failed!");
								return;
				}
				Serial.println("SD Card initialized.");
}
