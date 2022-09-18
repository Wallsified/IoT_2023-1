#include "BluetoothSerial.h"
#include "DHT.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define LED1 14
#define LED2 26
#define DHTPIN 32
#define DHTTYPE 11
#define SW1 15
#define SW2 4

BluetoothSerial BT;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  BT.begin("ESP32_LED_BT"); // Nombre de tu Dispositivo Bluetooth y en modo esclavo
  Serial.println("Da bluchu dibais is redy to pel");
  BT.register_callback(callback_function);
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
      else if (incoming == 50) {
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
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    return;
  }
  
  if (digitalRead(SW2 == HIGH)) {
    BT.print("Nivel de Humedad: ");
    BT.println(h);
  }

  if (digitalRead(SW1 == LOW)) {
    BT.print("Temperatura en °C ");
    BT.println(f);
  }
}
