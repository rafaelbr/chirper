/*************
* KeyboardController.h
* Created by Rafael Brasileiro de Araujo on 21/08/24.
*
* Handles keyboard initialization and reading mechanics. For Heltec boards
* we don't have a native keyboard, so by design we are using a M5Stack CardKB
*
* Here we use I2C communication to read the keyboard, using the CardKB specification
* for action key codes like UP, DOWN, LEFT, RIGHT and FN+Key
*
*************/

#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

class KeyboardController {

public:
  KeyboardController();
  ~KeyboardController();

  void begin();
  void setFunctions(void (*up)(), void (*down)(), void (*left)(), void (*right)(), void (*enter)());
  char readKey();

private:

  bool executeAction(char actionCode);

  void (*upFunction)();
  void (*downFunction)();
  void (*leftFunction)();
  void (*rightFunction)();
  void (*enterFunction)();
};



#endif //KEYBOARDCONTROLLER_H
