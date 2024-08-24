#include "wifi_manager.h"

WiFiClient client;

void connectToWiFi() {
    Serial.println("Starting WiFi connection...");
    Serial.print("Connecting to SSID: ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("Waiting for WiFi to connect");
    int attempts = 0;
    while ((WiFi.status() != WL_CONNECTED) && attempts < 20) {
        Serial.print(".");
        delay(1000);
        attempts++;
        int status = WiFi.status();
        switch (status) {
            case WL_NO_SSID_AVAIL:
                Serial.println("SSID no disponible");
                break;
            case WL_CONNECT_FAILED:
                Serial.println("Conexión fallida");
                break;
            case WL_IDLE_STATUS:
                Serial.println("WiFi en estado inactivo");
                break;
            default:
                Serial.println("Estado desconocido: " + String(status));
                break;
        }
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("Connected to: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("[Error] No se pudo conectar a WiFi");
    }
}

void disconnectWiFi() {
    WiFi.disconnect();
    Serial.println("Disconnected from WiFi");
}
