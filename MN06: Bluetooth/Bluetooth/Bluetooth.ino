/* Mini Práctica #6: Bluetooth
   Objetivos:
   1. Usando la aplicación Serial Bluetooth Terminal o alguna otra parecida, desarrolle lo siguiente:
      a. Encender los LED dependiendo el valor enviado, es decir, al enviar un “1” se
         enciende el LED 1, al enviar “2” se enciende el LED 2 y así sucesivamente,
         todos se apagan cuando se envíe un “0”
      b. Hacer que cada vez que se apriete un botón, recibir la temperatura actual en
         el smartphone y cuando se apriete el otro, la humedad.

  Código creado por los alumnos
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea

*/

#include "BluetoothSerial.h"
#include "DHT.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define LED1 14
#define LED2 26
#define DHTPIN 32 //Pin DHT
#define DHTTYPE 11 //Tipo DHT
#define SW1 15
#define SW2 4

float tempCel, humid;
int leds[5] = {14, 27, 26, 25, 33};

BluetoothSerial BT; //Objeto Bluetooth.
DHT dht(DHTPIN, DHTTYPE); //Objeto DHT

void setup() {
  Serial.begin(115200);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  attachInterrupt(SW2, sensor, RISING); //estas funciones ayudan a detectar cambios (LOW/HIGH) en los botones.
  attachInterrupt(SW1, sensor2, FALLING);
  dht.begin(); //iniciamos el objeto dht
  BT.begin("ESP32_LED_BT"); // Nombre de tu Dispositivo Bluetooth y en modo esclavo
  Serial.println("Da bluchu dibais is redy to pel"); //yeah
  BT.register_callback(callback_function); //función callback de BT

  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void callback_function(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_START_EVT) {
    Serial.println("Inicializado SPP");
  }
  else if (event == ESP_SPP_SRV_OPEN_EVT ) {
    Serial.println("Cliente conectado");
  }
  else if (event == ESP_SPP_CLOSE_EVT  ) {
    Serial.println("Cliente desconectado");
  }
  else if (event == ESP_SPP_DATA_IND_EVT ) {
    Serial.println("Datos recibidos");
    while (BT.available()) { // Mientras haya datos por recibir
      int incoming = BT.read(); // Lee un byte de los datos recibidos

      Serial.print("Recibido: ");
      Serial.println(incoming);

      if (incoming == 48) { // 0 en ASCII
        for (int i = 0; i < 5; i++) {
          digitalWrite(leds[i], LOW);
        }
        BT.println("LEDs Apagados");
      }

      switch (incoming) {
        case 49:
          digitalWrite(leds[0], HIGH);
          Serial.println("LED1 Encendido");
          BT.println("LED1 Encendido");
          break;
        case 50:
          digitalWrite(leds[1], HIGH);
          Serial.println("LED2 Encendido");
          BT.println("LED2 Encendido");
          break;
        case 51:
          digitalWrite(leds[2], HIGH);
          Serial.println("LED3 Encendido");
          BT.println("LED3 Encendido");
          break;
        case 52:
          digitalWrite(leds[3], HIGH);
          Serial.println("LED4 Encendido");
          BT.println("LED4 Encendido");
          break;
        case 53:
          digitalWrite(leds[4], HIGH);
          Serial.println("LED5 Encendido");
          BT.println("LED5 Encendido");
          break;
      }
    }
  }
}


void sensor() {
  BT.print("Nivel de Humedad: ");
  BT.println(humid);
  Serial.print("Nivel de Humedad: ");
  Serial.println(humid);
}

void sensor2() {
  BT.print("Temperatura en °C: ");
  BT.println(tempCel);
  Serial.print("Temperatura en °C: ");
  Serial.println(humid);
}

void loop() {
  humid = dht.readHumidity(); //humidity
  tempCel = dht.readTemperature(); //
  if (isnan(humid) || isnan(tempCel)) {
    return; //evitamos cosas de tipo nan en la impresión.
  }
  delay(1000);

}
