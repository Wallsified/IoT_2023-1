/* Mini práctica 9: Bots
   Objetivos:
   1. Usando un bot propio de Telegram, realice lo siguiente:
      a. Con base en el control de lazo cerrado PID, escribir el setpoint. Observar 
         mediante el serial plotter el comportamiento del PID.
      b. Encender y apagar el LED 1.
      c. Solicitar el voltaje de la fotorresistencia con un comando del bot.

  Código creado por los alumnos
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea

*/

#include "CTBot.h"
#include "DHT.h"

#define pinPhoto 34
#define LED 14
#define PinADC 34 //LDR en la placa
#define DHTPIN 32 //Pin DHT
#define DHTTYPE 11 //Tipo DHT
const float constante = 0.6; //para el voltaje

CTBot myBot;

String ssid = "IZZI-5044";
String pass = "189C27645044";
String token = "5533017969:AAHjuVYZHczNLjjzORZA1G9RJ3TTrOzlQmo";

void setup() {
  Serial.begin(115200);
  pinMode(LED , OUTPUT);
  digitalWrite(LED, LOW);
  pinMode(PinADC, INPUT);

  Serial.println("Comenzando Bot de Telegram...");

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  delay(1000);

  if (myBot.testConnection()) {
    Serial.println("Conectado al Bot");
  } else {
    Serial.println("Error: No se ha conectado con el Bot");
  }

}

void loop() {
  TBMessage msg;

  if (myBot.getNewMessage(msg)) {
    
    if (msg.text.equalsIgnoreCase("/start")) {
      Serial.println("Nueva interacción con");
      Serial.print(msg.sender.username);
      myBot.sendMessage(msg.sender.id, "Bienvenido, ya puede mandar sus instrucciones");
      
    } else  if (msg.text.equalsIgnoreCase("/resistencia")) {

      float sensor = 3.3 / 4096.0 * analogRead(PinADC); //Voltaje = x / Flash Size
      String messVolt = "El Voltaje en la fotoresistencia es de: " + String(sensor) + "V";
      Serial.println("La fotoresistencia es de ");
      Serial.print(sensor);
      Serial.print(" volts");
      myBot.sendMessage(msg.sender.id, messVolt);
      Serial.println("Respuesta enviada");
      
    } else  if (msg.text.equalsIgnoreCase("/enciende")) {
      
      digitalWrite(LED, HIGH);
      Serial.println("Led 1 encendido");
      String respuesta2 = "LED encendido";
      myBot.sendMessage(msg.sender.id, respuesta2);
      
    } else  if (msg.text.equalsIgnoreCase("/apaga")) {
      
      digitalWrite(LED, LOW);
      Serial.println("Led 1 apagado");
      String respuesta3 = "LED apagado";
      myBot.sendMessage(msg.sender.id, respuesta3);
      
    } else {
      myBot.sendMessage(msg.sender.id, "Intenta de nuevo con /start");
    }

  }

}
