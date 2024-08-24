#include "MotorPump.h"
#include <Arduino.h>

MotorPump::MotorPump(int pumpPin) : pin(pumpPin), isOn(false) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH); // Inicialmente la bomba está apagada
}

void MotorPump::runForSeconds(unsigned int seconds) {
  digitalWrite(pin, LOW); // Encender la bomba
  isOn = true;
  delay(seconds * 1000);
  digitalWrite(pin, HIGH); // Apagar la bomba
  isOn = false;
}

bool MotorPump::getStatus() {
  return isOn;
}
