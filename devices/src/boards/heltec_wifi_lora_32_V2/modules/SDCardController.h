//
// Created by Rafael Brasileiro de Araujo on 25/08/24.
//

#ifndef SDCARDCONTROLLER_H
#define SDCARDCONTROLLER_H

#include <Arduino.h>
#include <SD.h>

#define SDCARD_CS 2
#define SDCARD_MOSI 22
#define SDCARD_MISO 23
#define SDCARD_SCK 17



class SDCardController {
public:
    SDCardController();
    ~SDCardController();

    void begin();

private:
    SPIClass	spi1;

};



#endif //SDCARDCONTROLLER_H
