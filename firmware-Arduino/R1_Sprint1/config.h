#ifndef CONFIG_H
#define CONFIG_H

// Credenciales de WiFi
extern const char* WIFI_SSID;
extern const char* WIFI_PASS;

// Configuraciones del servidor
extern const char* SERVER;  // Cambia esto para mantener consistencia o elimina si es redundante
extern const char* API_KEY;
extern const char* server;  // Corregido: añadido punto y coma

// Configuraciones de la bomba
#define PIN_BOMBA 13
#define TIMER_STATUS 600

#endif // CONFIG_H
