#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial BT; // Objeto Bluetooth

String clientName = "ESP32_Vazzvel_Slave";
bool connected;

void setup() {
  Serial.begin(9600);
  BT.begin("ESP32_Vazzvel_Master", true); // Nombre de su dispositivo Bluetooth y en modo maestro
  Serial.println("El dispositivo Bluetooth está en modo maestro.\n Conectando con el anfitrión ...");
  connected = BT.connect(clientName);
  if(connected) {
    Serial.println("¡Conectado exitosamente!");
  } else {
    while(!BT.connected(10000)) {
      Serial.println("No se pudo conectar. Asegúrese de que el dispositivo remoto esté disponible y dentro del alcance, luego reinicie la aplicación."); 
    }
  }
}
void loop() {
  BT.write(49); // Envía 1 en ASCII
  delay(200);
  BT.write(48); // Envía 0 en ASCII
  delay(200);
}
