/* Mini Práctica #10: Google Assistant
   Objetivos:
  1. Mediante Sinric Pro, crear un dispositivo que encienda y apague tres leds de la
  tarjeta con el ESP32, de manera de switch.
  2. Utilizando las aplicaciones Google Home y Google Assistant, configurar el
  dispositivo creado del punto anterior para encenderlo y apagarlo mediante
  instrucciones con voz utilizando el asistente de Google.

  Código modificado por los alumnos:
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea

*/

//Usamos esta parte para poder ver que hace el ESP32 en el monitor serial
#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#define DEBUG_ESP_PORT Serial
#define NDEBUG
#endif

//Como Sinric trabaja con otros modelos de ESP, este ifdef añade la libreria Wifi si si es el ESP32
#ifdef ESP32
#include <WiFi.h>
#define LED1 14
#define LED2 27
#define LED3 26
#endif

#include <Arduino.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

#define WIFI_SSID         "INFINITUMA6A4_2.4"
#define WIFI_PASS         "Zamudiov3!"
#define APP_KEY           "f0c7aa17-b734-49b1-98ef-e8f046661a1b"  //constantes de Sinric    
#define APP_SECRET        "1da18685-857c-46e7-ae49-964e9548a03b-8044e8aa-d3ec-4669-815e-2511833f0d2d"

/* C++ tiene está cosa curiosa llamada "struct" y "vector". Es como declarar un constructor de un objeto en Java (struct) y luego
   creas como un array (el vector) de tipo struct y pones las asignaciones a las propiedades del struct.
*/
struct LEDInfo {
  String deviceId; //ID dado por Sinric
  String name; //nombre que le daremos al dispositivo
  int pin; //pin relacionado al dispositivo
};

std::vector<LEDInfo> leds = {
  {"6359fb0db8a7fefbd627fa21", "LED 1", LED1},
  {"635a01af333d12dd2adc8873", "LED 2", LED2},
  {"635a0205b8a7fefbd6280d7e", "LED 3", LED3},
};

bool onPowerState(const String &deviceId, bool &state) {
  for (auto &led : leds) {            //Para cada "led" (nombre de nuestro "iterador") en nuestro vector "leds"...
    if (deviceId == led.deviceId) {
      Serial.printf("El LED %s está %s\r\n", led.name.c_str(), state ? "encendido" : "apagado");
      digitalWrite(led.pin, state);
      return true;
    }
  }
  return false; // Si la info del led no corresponde a lo establecido en el vector, entonces regresa falso en automático.
}

//Método que pone los leds en nuestro vector como outputs.
void setupLEDPins() {
  for (auto &led : leds)
    pinMode(led.pin, OUTPUT);
}

//Método para inicializar la conexión Wifi.
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Conectando...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  Serial.printf("Connectado!\r\n[WiFi]: La IP del dispositivo es: %s\r\n", WiFi.localIP().toString().c_str());
}

//Método para inicializar la conexión a Sinric Pro
void setupSinricPro() {
  for (auto &led : leds) {
    SinricProSwitch &mySwitch = SinricPro[led.deviceId];   // creamos un dispositivo con la info del vector para cada ID
    //Nota: por defecto, no existen los dispositivos con los IDS, pero esa linea justamente los crea para su uso posterior.
    mySwitch.onPowerState(onPowerState);                     // y a cada dispositivo le añadimos el método onPowerState
  }

  SinricPro.onConnected([]() {
    Serial.printf("Connectado a SinricPro\r\n");
  });
  SinricPro.onDisconnected([]() {
    Serial.printf("El dispositivo ha sido desconectado de Sinric Pro\r\n");
  });

  SinricPro.begin(APP_KEY, APP_SECRET); //Inicializamos Sinric con las claves privadas.
}

void setup() {
  Serial.begin(115200);
  setupLEDPins();
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
