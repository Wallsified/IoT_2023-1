/* Mini Práctica #6: Bluetooth
   Objetivos:
   Usando el protocolo MQTT y la aplicación MQTT Explorer o alguna otra parecida, realice lo siguiente:
      1. Encender los LED dependiendo el valor recibido mediante un tópico, es decir, al
         enviar desde la aplicación un “1” se enciende el LED 1, al enviar “2” se enciende el
         LED 2 y así sucesivamente, todos se apagan cuando se envíe un “0”
      2. Hacer que cada vez que se apriete un botón se publique la temperatura actual y cuando se apriete
         el otro, la humedad.
      3. Publicar cada segundo el voltaje de la fotorresistencia.

  Código creado por los alumnos
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea

*/

#include "EspMQTTClient.h"
#include "DHT.h"

#define LED1 14
#define LED2 26
#define DHTPIN 32 //Pin DHT
#define DHTTYPE 11 //Tipo DHT
#define SW1 15
#define SW2 4
#define PinADC 34 //LDR en la placa
const float constante = 0.6; //para el voltaje

DHT dht(DHTPIN, DHTTYPE);

EspMQTTClient client( //Objeto MQTT
  "Clase_IoT",           //SSID
  "0123456789",        //Pass
  "test.mosquitto.org",   // MQTT broker público (Mosquitto)
  "Paredes&Arceo",          // Nombre de indentificación del cliente
  1883                      // Puerto MQTT
);


void setup() {
  pinMode(PinADC, INPUT);
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  Serial.begin(115200);
  dht.begin();
  Serial.println(client.isConnected());
}

void onConnectionEstablished() {
  client.subscribe("Clase_IoT/Paredes&Arceo/SignalRecieved", [](const String & payload) { //El tópico de señales recibidas por MQTT
    Serial.print("Señal MQQT Recibida!: ");
    Serial.println(payload);

    if (payload == "1") {
      digitalWrite(LED1, HIGH);
      client.publish("Clase_IoT/Paredes&Arceo/LEDs", String("LED 1 Encendido"));
      Serial.println("LED1 Encendido");
    }

    if (payload == "2") {
      digitalWrite(LED2, HIGH);
      client.publish("Clase_IoT/Paredes&Arceo/LEDs", String("LED 2 Encendido"));
      Serial.println("LED2 Encendido");
    }

  });
}

void loop() {
  client.loop();

  float h = dht.readHumidity(); //humidity
  float f = dht.readTemperature(true); //

  if (isnan(h) || isnan(f)) {
    return; //evitamos cosas de tipo nan en la impresión.
  }

  if (digitalRead(SW2)) {
    String messHumid = "Nivel de Humedad detectado: " + String(h);
    client.publish("Clase_IoT/Paredes&Arceo/DHT/Humedad", String(messHumid));
    Serial.println (messHumid);
  }

  if (digitalRead(SW1)) {
    String messTemp = "Nivel de Temperatura detectado: " + String(f);
    client.publish("Clase_IoT/Paredes&Arceo/DHT/Temperatura", String(messTemp));
    Serial.println(messTemp);
  }

  //Para la fotoresistencia.
  float sensor = 3.3 / 4096.0 * analogRead(PinADC); //Voltaje = x / Flash Size
  String messVolt = "El Voltaje en la fotoresistencia es de: " + String(sensor);
  client.publish("Clase_IoT/Paredes&Arceo/LDR", String(messVolt));
  Serial.println(messVolt);

  delay(1000);
}
