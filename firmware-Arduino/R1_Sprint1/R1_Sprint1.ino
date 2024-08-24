#include <Arduino.h> // Necessary for core Arduino functions and definitions
#include "config.h" // Contain configuration settings
#include "wifi_manager.h" // Manage WiFi connections
#include "MotorPump.h" // To control a motor pump
//#include <ThingSpeak.h> // Necessary for interfacing with the ThingSpeak API
#include "tickers.h" // Include the new Ticker header

MotorPump pump(PIN_BOMBA);

void setup() {
Serial.begin(115200); // Initialize serial communication
// connectToWiFi();
//setupTickers(); // Set up the tickers

//ThingSpeak.begin(client); // Initialize ThingSpeak
//sendDataToThingSpeak(25.5);
// disconect internet to reduce consumption
}

void loop() {
// Nothing to do here, all tasks are managed by Tickers
}