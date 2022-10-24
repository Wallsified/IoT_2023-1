#include "CTBot.h"

#define pinPhoto 34
#define LED 14

CTBot myBot;

String ssid = "IZZI-5044";
String pass = "189C27645044";
String token = "5533017969:AAHjuVYZHczNLjjzORZA1G9RJ3TTrOzlQmo";

void setup() {
  Serial.begin(115200);
  pinMode(LED , OUTPUT);
  digitalWrite(LED, LOW);

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
      Serial.print("La fotoresistencia es de ");
      int fr = digitalRead(pinPhoto);
      Serial.print(fr);
      Serial.print(" volts");
      String respuesta1 = (String)"La fotoresistencia es de " + (String)fr + (String)" volts";
      myBot.sendMessage(msg.sender.id, respuesta1);
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
