#include "EspMQTTClient.h"

int cont = 0;

EspMQTTClient client(
  "Clase_IoT",           //SSID
  "0123456789",        //Pass
  //"192.168.0.100",          // MQTT broker local (Raspberry)
  "test.mosquitto.org",   // MQTT broker público (Mosquitto)
  "ESP32_Vazzvel",          // Nombre de indentificación del cliente
  1883                      // Puerto MQTT
);


void setup() {
  Serial.begin(115200);
  Serial.println(client.isConnected());
}

void onConnectionEstablished(){
  client.subscribe("Vazzvel/Sub", [](const String & payload) {
    Serial.print("El mensaje recibido es: ");
    Serial.println(payload);
  });
}

void loop() {
  client.loop();
  cont++;
  if(cont%5 == 0){
    int val = random(0, 25);
    client.publish("Vazzvel/Pub", String(val));
    Serial.print("El mensaje enviado es: ");
    Serial.println(val);
  }
  delay(500);
} 
