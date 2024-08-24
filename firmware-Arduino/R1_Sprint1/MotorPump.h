#ifndef MotorPump_h
#define MotorPump_h

#include <Arduino.h>

class MotorPump {
  private:
    int pin;
    bool isOn;
  
  public:
    MotorPump(int pumpPin);
    void runForSeconds(unsigned int seconds);
    bool getStatus();
};

#endif
