#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define LED 2

BluetoothSerial BT; // Objeto Bluetooth

void setup() {
  Serial.begin(9600);
  BT.begin("ESP32_Vazzvel_Slave"); // Nombre de su dispositivo Bluetooth y en modo esclavo
  Serial.println("El dispositivo Bluetooth está listo para emparejarse");
  pinMode (LED, OUTPUT);
}
void loop() {
  if (BT.available()) // Compruebe si recibimos algo de Bluetooth
  {
    int val = BT.read(); // Lee lo que recibimos
    Serial.print("Recibido: ");
    Serial.println(val);
    if (val == 49){ // 1 en ASCII
      digitalWrite(LED, HIGH);
    }
    if (val == 48){ // 0 en ASCII
      digitalWrite(LED, LOW);
    }
  }
}
