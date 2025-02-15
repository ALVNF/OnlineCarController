#ifndef MOTORS_CONTROLLER_H
#define MOTORS_CONTROLLER_H
#include <Arduino.h>
#include <Servo.h>

enum MovementState{
  STOPPED,
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

class MotorsController{
  private:
  // A byte stores an 8-bit unsigned number, from 0 to 255.
  //Channels Pins
    byte ENA = 5;
    byte ENB = 6;
    byte IN1 = 7;
    byte IN2 = 8;
    byte IN3 = 9;
    byte IN4 = 11;

    int delayTime = 1000;
    int wantedTurnAngle = 180;
    float wantedVelocity = 0.9; // max is 2
    float wantedDistance = 1.0; // meters

    //Servo
    Servo myServo;
    int servoPin =3;


    // Car specs
    float wheelDiameter;
    float trackWidth;

    // Moto specs;
    int outputRpm;
    int pwmVal;

    MovementState movementState;
    unsigned long movementStartTime;
    unsigned long movementDuration;


    float getWheelCircunference();
    void setSpeed(int leftVal, int rightVal);
    float getRPMFromPWM();
    float calculateLinealVelocity();
    float getCorrectionFactor();



  public:
    // MotorsController(){} //Do not use
    MotorsController(float wheelDiameter, float trackWidth, int outputRmp, 
                      int wantedTurnAngle, float wantedVelocity, float wantedDistance);
    void init();
    void calR(int pwm);
    void calL(int pwm);
    void goForward();
    void goBackward();
    void turnRight();
    void turnLeft();
    void stopCar();
    float calculateDistanceTime();
    float calculateTurnTime(float correctionFactor);
    void calculatePWM();
    // void info();

    void manualForward();
    void manualBackward();
    void manualRight();
    void manualLeft();

    int getWantedTurnAngle();
    void setWantedTurnAngle(int turnAngle);
    float getWantedVelocity();
    void setWantedVelocity(float velocity);
    float getWantedDistance();
    void setWantedDistance(float distance);
    void update();

};

#endif