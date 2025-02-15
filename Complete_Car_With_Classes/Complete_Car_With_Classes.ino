#include "Motors_Controller.h"
#include "Bluetooth_Comm.h"
#include "Ultrasonic.h"
// #include "IR_Controller.h"

MotorsController myMotorsController(0.065,0.128,600,90,0.9,0.3);
BluetoothComm myBLTComm(&myMotorsController);
Ultrasonic frontUltrasonic(&myMotorsController);
// IRController myIR(12, &myMotorsController);


void setup() {
  Serial.begin(9600);
  myMotorsController.init();
  frontUltrasonic().init();
  // myIR.init();

}

void loop() {
  // moveCar();
  // myIR.readInput();
  // while(Serial.available() == 0){}

  // 1) Actualizar el estado del motor (control no bloqueante)
  myMotorsController.update();
  

  if(Serial.available() > 0){
    myBLTComm.readStream();
  }


}

