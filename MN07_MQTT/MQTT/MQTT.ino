/* Mini Práctica #7: MQTT
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

#define DHTPIN 32 //Pin DHT
#define DHTTYPE 11 //Tipo DHT
#define SW1 15
#define SW2 4
#define PinADC 34 //LDR en la placa
const float constante = 0.6; //para el voltaje
int leds[5] = {14, 27, 26, 25, 33};
float tempCel, humid;
char payback; //hagamos que "payload" mande un char y de ahi a ascci again

DHT dht(DHTPIN, DHTTYPE);

EspMQTTClient client( //Objeto MQTT
  //"INFINITUMA6A4_2.4",
  "pcpuma",           //SSID
  "mango2022",        //Pass
  //"Zamudiov3!",
  "test.mosquitto.org",   // MQTT broker público (Mosquitto)
  "Paredes&Arceo",          // Nombre de indentificación del cliente
  1883                      // Puerto MQTT
);


void setup() {
  pinMode(PinADC, INPUT);
  pinMode(SW1, INPUT_PULLUP); //Nota: el ponerlos como INPUT_PULLUP, en este caso al menos, hace lo mismo que añadir las interrupciones.
  pinMode(SW2, INPUT_PULLUP);
  //  attachInterrupt(SW2, sensor, RISING); //estas funciones ayudan a detectar cambios (LOW/HIGH) en los botones.
  //  attachInterrupt(SW1, sensor2, FALLING);
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }
  Serial.begin(115200);
  dht.begin();
  Serial.println(client.isConnected());
}

void onConnectionEstablished() {
  client.subscribe("Clase_IoT/Paredes&Arceo/SignalRecieved", [](const String & payload) { //El tópico de señales recibidas por MQTT
    Serial.print("Señal MQQT Recibida!: ");
    Serial.println(payload);
    payback = payload.charAt(0);
    switch (payback) {
      case '1':
        digitalWrite(leds[0], HIGH);
        client.publish("Clase_IoT/Paredes&Arceo/LEDs", String("LED 1 Encendido"));
        Serial.println("LED1 Encendido");
        break;
      case '2':
        digitalWrite(leds[1], HIGH);
        client.publish("Clase_IoT/Paredes&Arceo/LEDs", String("LED 2 Encendido"));
        Serial.println("LED2 Encendido");
        break;
      case '3':
        digitalWrite(leds[2], HIGH);
        client.publish("Clase_IoT/Paredes&Arceo/LEDs", String("LED 3 Encendido"));
        Serial.println("LED3 Encendido");
        break;
      case '4':
        digitalWrite(leds[3], HIGH);
        client.publish("Clase_IoT/Paredes&Arceo/LEDs", String("LED 4 Encendido"));
        Serial.println("LED4 Encendido");
        break;
      case '5':
        digitalWrite(leds[4], HIGH);
        client.publish("Clase_IoT/Paredes&Arceo/LEDs", String("LED 5 Encendido"));
        Serial.println("LED5 Encendido");
        break;
      case '0':
        for (int i = 0; i < 5; i++) {
          digitalWrite(leds[i], LOW);
        }
        client.publish("Clase_IoT/Paredes&Arceo/LEDs", String("LEDs Apagados"));
        Serial.println("LEDs Apagados");
        break;
    }
  });
}


int lastState = HIGH;
int actualStateLED1, actualStateLED2;


void switchOne() { //Método que hace la lectura y ejecuta la sequencia del SW1
  actualStateLED1 = digitalRead(SW1);
  if (lastState == HIGH && actualStateLED1 == HIGH)
    sensor();
}

void switchTwo() { //Método que hace la lectura y ejecuta la sequencia del SW2
  actualStateLED2 = digitalRead(SW2);
  if (lastState == HIGH && actualStateLED2 == LOW)
    sensor2();
}

//Sequencia SW1
void sensor() {

  String messHumid = "Nivel de Humedad detectado: " ;
  String extraHumid = messHumid + String (humid);

  if (isnan(humid)) {
    client.publish("Clase_IoT/Paredes&Arceo/DHT/Humedad", "Nan Detectado, favor de presionar de nuevo");
    Serial.println("Nan Detectado, favor de presionar de nuevo");
  }
  else {
    client.publish("Clase_IoT/Paredes&Arceo/DHT/Humedad", String(extraHumid));
    Serial.println (extraHumid);
  }
}

//Sequencia del SW2
void sensor2() {
  String messTemp = "Nivel de Temperatura detectado: ";
  String extraTemp = messTemp + String (tempCel);

  if (isnan(tempCel)) {
    client.publish("Clase_IoT/Paredes&Arceo/DHT/Temperatura", "Nan Detectado, favor de presionar de nuevo");
    Serial.println("Nan Detectado, favor de presionar de nuevo");
  }
  else {
    client.publish("Clase_IoT/Paredes&Arceo/DHT/Temperatura", String(extraTemp));
    Serial.println(extraTemp);
  }
}

//Método que da el voltaje actual en el LDR
void resistance() {
  float sensor = 3.3 / 4096.0 * analogRead(PinADC); //Voltaje = x / Flash Size
  String messVolt = "El Voltaje en la fotoresistencia es de: " + String(sensor) + "V";
  client.publish("Clase_IoT/Paredes&Arceo/LDR", String(messVolt));
  Serial.println(messVolt);
}

void loop() {
  client.loop();
  humid = dht.readHumidity(); //humidity
  tempCel = dht.readTemperature();
  resistance();
  switchOne();
  switchTwo();
  delay(1000);
}
