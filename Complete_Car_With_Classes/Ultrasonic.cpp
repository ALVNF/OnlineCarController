#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(MotorsController* motors){
  this->motorsController = motors;
}

void Ultrasonic::init(){
  pinMode(trig, OUTPUT);
  pinMode(echo,INPUT);
}

int Ultrasonic::pingTime(){
  int pingTravelTime;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(trig, LOW);
  // Evitar que pulseIn bloquee demasiado: por defecto 1 s. Ajustamos a 30000 us.
  pingTravelTime = pulseIn(echo, HIGH, 30000UL);
  return pingTravelTime;
}

float Ultrasonic::distance(int pingTravelTime){
  return (pingTravelTime * 343.) / (2*1e6);
}

void Ultrasonic::scanPlace(){

}


void Ultrasonic::detectObject(){
  unsigned long currentMillis =millis();
  if(currentMillis -  lastUltrasonicTime >= ultrasonicInterval){
    lastUltrasonicTime = currentMillis;
    int pingT = pingTime();
    float dist = distance(pingT);
    if(dist < 0.7){
      motorsController->setWantedVelocity((1.1/8. * 1 - 1.1/8.) + 0.9);
    }
    if(dist<0.25){
      motorsController->stopCar();
    }
  }
}