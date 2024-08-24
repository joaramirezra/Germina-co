# Germina-co

Este proyecto tiene como objetivo mejorar el proceso de cultivo utilizando inteligencia artificial para monitoreo y control de condiciones.

## Características

- Control automático de la bomba de agua basado en sensores.
- Integración con la plataforma ThingSpeak para monitoreo remoto.
- Interfaz de usuario minimalista con configuración a través de WiFi.

## Instalación

1. Clona este repositorio:
   ```sh
   git clone https://github.com/tuusuario/germina-co.git
   cd germina-co
   ```
2. Configura las credenciales de WiFi en `config.h`:
   ```cpp
   #define WIFI_SSID "tuSSID"
   #define WIFI_PASSWORD "tuContraseña"
   ```
3. Compila y sube el firmware al dispositivo utilizando Arduino IDE.

## Uso

1. Enciende el dispositivo.
2. Accede a la interfaz de configuración WiFi y conéctate a la red.
3. Monitoriza los datos en tiempo real desde ThingSpeak.

## Contribuir

1. Haz un fork del proyecto.
2. Crea una nueva rama (`git checkout -b feature/nueva-funcionalidad`).
3. Realiza tus cambios y haz un commit (`git commit -m 'Agregar nueva funcionalidad'`).
4. Haz push a la rama (`git push origin feature/nueva-funcionalidad`).
5. Abre un pull request.

## Licencia

Este proyecto está bajo la licencia MIT. Mira el archivo [LICENSE](LICENSE) para más detalles.
