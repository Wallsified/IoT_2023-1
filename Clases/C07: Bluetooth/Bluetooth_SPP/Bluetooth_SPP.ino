/*
ESP_SPP_INIT_EVT: Cuando el modo SPP es inicializado
ESP_SPP_UNINIT_EVT: Cuando el modo SPP es desinicializado
ESP_SPP_DISCOVERY_COMP_EVT: Cuando se completa el descubrimiento de servicios
ESP_SPP_OPEN_EVT: Cuando un cliente SPP abre una conexión
ESP_SPP_CLOSE_EVT: Cuando se cierra una conexión SPP
ESP_SPP_START_EVT: Cuando se inicializa el servidor SPP
ESP_SPP_CL_INIT_EVT: Cuando un cliente SPP inicializa una conexión
ESP_SPP_DATA_IND_EVT: Al recibir datos a través de una conexión SPP
ESP_SPP_CONG_EVT: Cuando cambia el estado de congestión en una conexión SPP
ESP_SPP_WRITE_EVT: Al enviar datos a través de SPP.
ESP_SPP_SRV_OPEN_EVT: Cuando un cliente se conecta al servidor SPP
ESP_SPP_SRV_STOP_EVT: Cuando el servidor SPP se detiene
*/

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define LED 27

BluetoothSerial BT;

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
        digitalWrite(LED, HIGH);
        BT.println("LED encendido");
      }
      else if (incoming == 48) { // 0 en ASCII
        digitalWrite(LED, LOW);
        BT.println("LED apagado");
      }
    }
  }
}
void setup() {
  Serial.begin(115200);
  BT.begin("ESP32_LED_BT"); // Nombre de tu Dispositivo Bluetooth y en modo esclavo
  Serial.println("El dispositivo Bluetooth está listo para emparejar");
  BT.register_callback(callback_function);
  pinMode (LED, OUTPUT);
}

void loop() {
  Serial.println("Hola");
}
