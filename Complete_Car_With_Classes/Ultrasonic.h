#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include <Arduino.h>

class Ultrasonic {
  private:
    // Guarda la marca de tiempo para realizar lecturas del sensor periódicas
    unsigned long lastUltrasonicTime = 0;
    // Intervalo de lectura del sensor (ms). Ajusta según lo necesario
    const unsigned long ultrasonicInterval = 200;
    int trig = A5;
    int echo = A4;
    int pingT;

    MotorsController* motorsController;

    int pingTime();
    float distance(int pingTravelTime);
    
  public:
    Ultrasonic(MotorsController* motors);
    void init();
    void detectObject();
    void scanPlace();

};

#endif