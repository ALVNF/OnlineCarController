#include "IR_Controller.h"
#include <IRremote.h>


IRController::IRController(byte pin, MotorsController* motors){
  this->pin = pin;
  this->motorsController = motors;
}

void IRController::init(){
  IrReceiver.begin(pin, ENABLE_LED_FEEDBACK);
}

void IRController::readInput(){
  while(IrReceiver.decode() == 0){};
  unsigned long irValue =IrReceiver.decodedIRData.decodedRawData; // Print "old" raw data
  // Serial.println(irValue,HEX);
  // IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
  // IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
  delay(500);

  if(updateDistance){
    establishDistance(irValue);
  }
  if(updateSpeed){
    establishSpeed(irValue);
  }

  if(irValue == 0xBD42FF00){
    updateSpeed = true;
    updateDistance = false;
  }else if(irValue == 0xB54AFF00){
    updateSpeed = false;
    updateDistance = true;
  }

  moveCar(irValue);
  IrReceiver.resume(); // Enable receiving of the next value
}

void IRController::moveCar(unsigned long irValue){
    
    switch (irValue) {
      case 0xB946FF00:  // Código IR para avanzar
        motorsController->goForward();  // Llamamos al método de MotorsController
        break;
      case 0xBC43FF00:  // Código IR para girar Derecha
        motorsController->turnRight();
        break;
      case 0xBB44FF00 :  // Código IR para girar Izquierda
        motorsController->turnLeft();
        break;
      case 0xEA15FF00:  // Código IR para retroceder
        motorsController->goBackward();  // Llamamos al método de MotorsController
        break;
      case 0xBF40FF00:  // Código IR para detenerse
        motorsController->stopCar();
        break;
    }
}

void IRController::establishDistance(unsigned long irValue){
  switch (irValue) {
    case 0xE916FF00: newValue += "1"; break;  // Tecla 1
    case 0xE619FF00: newValue += "2"; break;  // Tecla 2
    case 0xF20DFF00: newValue += "3"; break;  // Tecla 3
    case 0xF30CFF00: newValue += "4"; break;  // Tecla 4
    case 0xE718FF00: newValue += "5"; break;  // Tecla 5
    case 0xA15EFF00: newValue += "6"; break;  // Tecla 6
    case 0xF708FF00: newValue += "7"; break;  // Tecla 7
    case 0xE31CFF00: newValue += "8"; break;  // Tecla 8
    case 0xA55AFF00: newValue += "9"; break;  // Tecla 9
    case 0xAD52FF00: newValue += "0"; break;  // Tecla 0
    case 0xBF40FF00:  // Botón "OK" o "#" (para confirmar entrada)
      if (newValue.length() > 0) {
        float finalDistance = newValue.toFloat();  // Convertir String a número
        Serial.print("Final Distance: ");
        Serial.println(finalDistance);
        
        // Ejecutar el movimiento
        motorsController->setWantedDistance(finalDistance);

        // Resetear entrada
        newValue = "";
        updateDistance = false;

      }
      break;
    case 0xB54AFF00:  // Botón "C" o "*" para borrar entrada
      newValue = "";
      updateDistance = false;
      break;
  }
}

void IRController::establishSpeed(unsigned long irValue){
  switch (irValue) {
    case 0xE916FF00: newValue = "1"; break;  // Tecla 1
    case 0xE619FF00: newValue = "2"; break;  // Tecla 2
    case 0xF20DFF00: newValue = "3"; break;  // Tecla 3
    case 0xF30CFF00: newValue = "4"; break;  // Tecla 4
    case 0xE718FF00: newValue = "5"; break;  // Tecla 5
    case 0xA15EFF00: newValue = "6"; break;  // Tecla 6
    case 0xF708FF00: newValue = "7"; break;  // Tecla 7
    case 0xE31CFF00: newValue = "8"; break;  // Tecla 8
    case 0xA55AFF00: newValue = "9"; break;  // Tecla 9
    case 0xAD52FF00: newValue = "0"; break;  // Tecla 0
    case 0xBF40FF00:  // Botón "OK" o "#" (para confirmar entrada)
      if (newValue.length() != 0) {      
        // Ejecutar el movimiento
        motorsController->setWantedVelocity((1.1/8. * newValue.toFloat() - 1.1/8.) + 0.9);

      }else{
        // Ejecutar el movimiento
        motorsController->setWantedVelocity(newValue.toFloat());
      }
      // Resetear entrada
      newValue = "";
      updateSpeed = false;
      break;
    case 0xBD42FF00:  // Botón "C" o "*" para borrar entrada
      newValue = "";
      updateSpeed = false;
      break;
  }
}