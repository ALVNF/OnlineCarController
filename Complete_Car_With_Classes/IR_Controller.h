#ifndef IR_CONTROLLER_H
#define IR_CONTROLLER_H

#include <Arduino.h>
#include "Motors_Controller.h"

class IRController {
  private:
    byte pin;
    MotorsController* motorsController;
    bool updateSpeed = false;
    bool updateDistance = false;
    String newValue = "";
  public :
    IRController(){} // Do not use
    IRController(byte pin, MotorsController* motors);
    void init();
    void readInput();
    void moveCar(unsigned long irValue);
    void establishSpeed(unsigned long irValue);
    void establishDistance(unsigned long irValue);
};


#endif