#ifndef BLUETOOTH_COMM_H
#define BLUETOOTH_COMM_H
#include <Arduino.h>
#include "Motors_Controller.h"

class BluetoothComm {
  private:
    String cmd;
    MotorsController* motorsController;
    int isManualDrive = 0;
    void moveCar(char direction);
    void controlCar(char direction);

  public:
    BluetoothComm(MotorsController* motors);
    void readStream();
};

#endif