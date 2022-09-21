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

BluetoothSerial BT; //Objeto Bluetooth.
DHT dht(DHTPIN, DHTTYPE); //Objeto DHT

void setup() {
  Serial.begin(115200);
  dht.begin(); //iniciamos el objeto dht
  BT.begin("ESP32_LED_BT"); // Nombre de tu Dispositivo Bluetooth y en modo esclavo
  Serial.println("Da bluchu dibais is redy to pel"); //yeah
  BT.register_callback(callback_function); //función callback de BT
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
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

      if (incoming == 49) { // 1 en ASCII
        digitalWrite(LED1, HIGH);
        BT.println("LED1 Encendido");
      }
      else if (incoming == 50) { //2 en ASCII
        digitalWrite(LED2, HIGH);
        BT.println("LED2 Encendido");
      }
      else if (incoming == 48) { // 0 en ASCII
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        BT.println("LED1 y/o LED2 Apagados");
      }
    }
  }
}


void loop() {
  delay(2000);
  float h = dht.readHumidity(); //humidity
  float f = dht.readTemperature(true); //

  if (isnan(h) || isnan(t) || isnan(f)) {
    return; //evitamos cosas de tipo nan en la impresión. 
  }

  if (digitalRead(SW2)) { //here's where everything bugs
    BT.print("Nivel de Humedad: ");
    BT.println(h);
  }

  if (digitalRead(SW1)) {
    BT.print("Temperatura en °F ");
    BT.println(f);
  }
}
