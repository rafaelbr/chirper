/*************
* SDCardController.h
* Created by Rafael Brasileiro de Araujo on 28/08/24.
*
* Handles initialization and operations with SD Card
*
* Uses default library SD.h and SPI.h
*
*************/
#ifndef SDCARDCONTROLLER_H
#define SDCARDCONTROLLER_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SDCARD_CS 2
#define SDCARD_MOSI 23
#define SDCARD_MISO 22
#define SDCARD_SCK 17


class SDCardController {

public:
    SDCardController();
    ~SDCardController();

    /* Initialize SD Card */
    void begin();

    /* Write data to file */
    void writeData(String filepath, String data);

    /* Read data from file */
    String readData(String filepath);

private:
    SPIClass spi1;


};



#endif //SDCARDCONTROLLER_H
