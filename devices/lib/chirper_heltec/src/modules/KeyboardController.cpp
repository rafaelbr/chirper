//
// Created by Rafael Brasileiro de Araujo on 21/08/24.
//

#include "KeyboardController.h"
#include <Wire.h>

#define CARDKB_ADDR 0x5F

KeyboardController::KeyboardController() {
}

KeyboardController::~KeyboardController() {
}

void KeyboardController::begin() {
  //make a initial read on I2C to clear the buffer
  Wire.requestFrom(CARDKB_ADDR, 1);

}

void KeyboardController::setFunctions(void (*up)(), void (*down)(), void (*left)(), void (*right)(), void (*enter)()) {
  upFunction = up;
  downFunction = down;
  leftFunction = left;
  rightFunction = right;
  enterFunction = enter;
}

char KeyboardController::readKey() {
  Wire.requestFrom(CARDKB_ADDR, 1);
  char c = 0;
  while (Wire.available()) {
    c = Wire.read();
    if (executeAction(c)) {
      return 0;
    }
  }
  return c;
}

bool KeyboardController::executeAction(char actionCode) {
  switch (actionCode) {
    case 0xB4:
      //left
      leftFunction();
      return true;
    case 0xB7:
      //right
      rightFunction();
      return true;
    case 0xB5:
      //up
      upFunction();
      return true;
    case 0xB6:
      //down
      downFunction();
      return true;
    case 0xA3:
      //enter
      enterFunction();
      return true;
    default:
      return false;
  }
}
