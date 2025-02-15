#include "Arduino.h"
#include "Motors_Controller.h"
#include <math.h>

MotorsController::MotorsController(float wheelDiameter, float trackWidth, int outputRmp, int wantedTurnAngle, float wantedVelocity, float wantedDistance){
  this->wheelDiameter = wheelDiameter;
  this->trackWidth = trackWidth;
  this->outputRpm = outputRmp;
  this->wantedTurnAngle = wantedTurnAngle;
  this->wantedVelocity = wantedVelocity;
  this->wantedDistance = wantedDistance;

  movementState = STOPPED;
  movementStartTime = 0;
  movementDuration = 0;
}

void MotorsController::setWantedTurnAngle(int turnAngle){
  this->wantedTurnAngle = turnAngle;
}

int MotorsController::getWantedTurnAngle(){
  return wantedTurnAngle;
}


void MotorsController::setWantedDistance(float distance){
  this->wantedDistance = distance;
}

float MotorsController::getWantedDistance(){
  return wantedDistance;
}


void MotorsController::setWantedVelocity(float velocity){
  this->wantedVelocity = velocity;
  calculatePWM();
}

float MotorsController::getWantedVelocity(){
  return wantedVelocity;
}

// void MotorsController::info(){
//   Serial.print("Wheel Circumference: ");
//   Serial.println(getWheelCircunference());

//   Serial.print("PWM: ");
//   Serial.println(pwmVal);

//   Serial.print("RPM from PWM: ");
//   Serial.println(getRPMFromPWM());

//   Serial.print("Calculated Linear Velocity: ");
//   Serial.println(calculateLinealVelocity());

//   Serial.print("Time to travel 1 meter: ");
//   Serial.println(calculateDistanceTime());
// }

void MotorsController::init(){
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  calculatePWM();
  myServo.attach(servoPin);

}

float MotorsController::getWheelCircunference(){
  return M_PI * wheelDiameter;
}

void MotorsController::calculatePWM(){
  pwmVal = (wantedVelocity * 60. * 255.) / (getWheelCircunference() * outputRpm);
  setSpeed(pwmVal, pwmVal);
}

void MotorsController::setSpeed(int leftVal, int rightVal){
  analogWrite(ENA, leftVal);
  analogWrite(ENB, rightVal);
}

float MotorsController::getRPMFromPWM(){
  return (float) pwmVal / 255.0 * outputRpm;
}

float MotorsController::calculateLinealVelocity(){
  float rmpActual = getRPMFromPWM();
  float linealVelocityMinutes = rmpActual * getWheelCircunference();
  float linealVelocitySeconds = linealVelocityMinutes / 60.; // 60 seconds

  return linealVelocitySeconds;
}

float MotorsController::getCorrectionFactor(){
  if (wantedVelocity <= 0.9) return 2.08;
  else if (wantedVelocity <= 1.5) return 1.87;
  else return 1.89;
}

float MotorsController::calculateDistanceTime(){
  float timeSeconds = wantedDistance / calculateLinealVelocity();
  float correctionFactor = getCorrectionFactor();
  return timeSeconds * correctionFactor * 1000.0;

}

float MotorsController::calculateTurnTime(float correctionFactor){
  float time = (wantedTurnAngle + 8.53) / (2 * 73.914);
  return time * correctionFactor * 1000.0;
}

void MotorsController::calL(int pwm){
  stopCar();
  analogWrite(ENA, 145);
  analogWrite(ENB, 145);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(5000);

  analogWrite(ENA, pwm);
  analogWrite(ENB, pwm);
  stopCar();
}

void MotorsController::calR(int pwm){
  stopCar();
  analogWrite(ENA, 145);
  analogWrite(ENB, 145);
  // Right Turn (1 0 | 1 0)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(3000);

  analogWrite(ENA, pwm);
  analogWrite(ENB, pwm);
  stopCar();
}

void MotorsController::goForward(){
  myServo.write(90);
  delay(delayTime);
  // To go forward (1 0 | 0 1)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  float timeMS = calculateDistanceTime();
  movementStartTime = millis();
  movementDuration = (unsigned long) timeMS;
  movementState = FORWARD;
}

void MotorsController::goBackward(){


  // To go backwards (0 1 | 1 0)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);


  float timeMS = calculateDistanceTime();
  movementStartTime = millis();
  movementDuration = (unsigned long) timeMS;
  movementState = BACKWARD;
}

void MotorsController::turnRight(){
  myServo.write(0);
  setSpeed(135, 135);

  delay(delayTime);

  // Right Turn (1 0 | 1 0)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  float timeMS = calculateTurnTime(0.9);
  movementStartTime = millis();

  movementDuration = (unsigned long) timeMS;
  movementState = RIGHT;

  
}

void MotorsController::turnLeft(){
  myServo.write(180);
  setSpeed(135, 135);
  delay(delayTime);

  // Left Turn (0 1 | 0 1)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  float timeMS = calculateTurnTime(0.9);
  movementStartTime = millis();
  movementDuration = (unsigned long) timeMS;
  
  movementState = LEFT;

}

void MotorsController::stopCar(){
  // Stop(0 0 | 0 0)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  movementState = STOPPED;
  setSpeed(pwmVal, pwmVal);
}

void MotorsController::update(){
  if (movementState != STOPPED) {
    unsigned long currentTime = millis();
    if (currentTime - movementStartTime >= movementDuration) {
      stopCar();
    }
  }
}


void MotorsController::manualForward(){
  // To go forward (1 0 | 0 1)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void MotorsController::manualBackward(){
  // To go backwards (0 1 | 1 0)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void MotorsController::manualRight(){
  setSpeed(135, 135);
  // Right Turn (1 0 | 1 0)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void MotorsController::manualLeft(){
  setSpeed(135, 135);
  // Left Turn (0 1 | 0 1)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


