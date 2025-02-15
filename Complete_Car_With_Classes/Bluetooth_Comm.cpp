#include "Bluetooth_Comm.h"

BluetoothComm::BluetoothComm(MotorsController* motors){
  this->motorsController = motors;
}

void BluetoothComm::readStream(){
  if(Serial.available()){
    cmd = Serial.readStringUntil('\n');
    cmd.trim();

    float distance = 0.3;
    int speed = 1;
    char direction = '\0';

    // Serial.println(cmd);
    if(cmd.length() == 1 || cmd.startsWith("MODE")){
      if(sscanf(cmd.c_str(), "MODE%d", &isManualDrive) == 1){
          // Serial.println("Manual Drive");
      }else if(sscanf(cmd.c_str(), "%c", &direction) == 1){
        // Serial.println(isManualDrive);
        if(isManualDrive){
          // Serial.println("ControlCar");
          controlCar(direction);
        }else{
          moveCar(direction);
        }
        return;
      } 
      
    }else {
      int firstSpaceIndex = cmd.indexOf(' ');
      int secondSpaceIndex = cmd.indexOf(' ', firstSpaceIndex + 1);
      if (firstSpaceIndex != -1 && secondSpaceIndex != -1) {
        String strDistance = cmd.substring(0, firstSpaceIndex);
        String strSpeed = cmd.substring(firstSpaceIndex + 1, secondSpaceIndex);
        String strAngle = cmd.substring(secondSpaceIndex + 1);
        
        float distance = strDistance.toFloat();
        int speed = strSpeed.toInt();
        int angle = strAngle.toInt();

        if (strDistance.length() > 0 && strSpeed.length() > 0 && strAngle.length() > 0) {
          motorsController->setWantedVelocity((1.1/8. * speed - 1.1/8.) + 0.9);
          motorsController->setWantedDistance(distance);
          motorsController->setWantedTurnAngle(angle);
          return;
        }
      }
      Serial.println("Invalid Format");
    }
    

  }
}

void BluetoothComm::moveCar(char direction){
  if(direction == 'f'){
    motorsController->goForward();
    // Serial.println("Going forward");
  }

  if(direction == 'b'){
    motorsController->goBackward();
    // Serial.println("Going backward");
  }

  if(direction == 'r'){
    motorsController->turnRight();
    // Serial.println("Turning right");
  }

  if(direction == 'l'){
    motorsController->turnLeft();
    // Serial.println("Turning left");
  }
}

void BluetoothComm::controlCar(char direction){
    if(direction == 'w'){
    motorsController->manualForward();
  }

  if(direction == 's'){
    motorsController->manualBackward();
  }

  if(direction == 'd'){
    motorsController->manualRight();
  }

  if(direction == 'a'){
    motorsController->manualLeft();
  }

  if(direction == 'p'){
    motorsController->stopCar();
  }
}