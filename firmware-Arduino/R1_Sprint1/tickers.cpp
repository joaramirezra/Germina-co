#include "tickers.h"
#include "config.h"
#include "wifi_manager.h"
#include "MotorPump.h"
#include <ThingSpeak.h>
#include <WiFi.h>

Ticker heartbeatTicker;
Ticker statusTicker;

extern WiFiClient client;

int heartbeatCount = 0;
unsigned long lastThingSpeakUpdateTime = 0;
const unsigned long thingSpeakUpdateInterval = 300000; // 5 minutes
int failedAttempts = 0;

void setupTickers() {
    connectToWiFi(); // Assuming this function is defined in wifi_manager.h
    if (WiFi.status() == WL_CONNECTED) {
        sendDataToThingSpeak(25.5);
    }
    heartbeatTicker.attach(60, heartbeat);
    statusTicker.attach(300, attemptThingSpeakUpdate); // Every 5 minutes
}

void heartbeat() {
    Serial.print("Heartbeat signal, count : ");
    Serial.println(heartbeatCount);
    heartbeatCount++;
}

void attemptThingSpeakUpdate() {
    checkWiFiConnection(); // Assuming this function is defined in wifi_manager.h
    if (WiFi.status() == WL_CONNECTED && millis() - lastThingSpeakUpdateTime >= thingSpeakUpdateInterval) {
        sendDataToThingSpeak(heartbeatCount);
    }
}

void sendDataToThingSpeak(float value) {
    if (client.connect(server, 80)) {
        String postStr = API_KEY;
        postStr += "&field1=";
        postStr += String(value);
        postStr += "\r\n\r\n";

        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + String(API_KEY) + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(postStr.length());
        client.print("\n\n");
        client.print(postStr);

        unsigned long timeout = millis();
        while (client.connected() && !client.available()) {
            if (millis() - timeout > 10000) {
                Serial.println("HTTP request timeout");
                client.stop();
                handleFailedAttempt();
                return;
            }
            delay(100);
        }

        bool success = false;
        while (client.available()) {
            String line = client.readStringUntil('\r');
            Serial.println(line);
            if (line.startsWith("HTTP/1.1")) {
                success = (line.indexOf("200 OK") > 0);
            }
        }

        client.stop();

        if (success) {
            Serial.println("ThingSpeak update successful");
            lastThingSpeakUpdateTime = millis();
            failedAttempts = 0;
        } else {
            Serial.println("ThingSpeak update failed");
            handleFailedAttempt();
        }
    } else {
        Serial.println("Connection to ThingSpeak failed");
        handleFailedAttempt();
    }
}

void handleFailedAttempt() {
    failedAttempts++;
    if (failedAttempts < 5) {
        unsigned long delayTime = 1000 * pow(2, failedAttempts);
        Serial.printf("Retrying in %lu seconds\n", delayTime / 1000);
        delay(delayTime);
        sendDataToThingSpeak(heartbeatCount);
    } else {
        Serial.println("Max retry attempts reached. Will try again next cycle.");
        failedAttempts = 0;
    }
}