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

#define LED 14
#define PinPhoto 34 //LDR en la placa
#define PinDAC 26
#define PinADC 32
#define PinPOT 35

const double kp = 2 , ki = 0.25 , kd = 0.005;
const float constante = 0.6; //para el voltaje
const int umbral = 3000;

unsigned long currentTime, previousTime;
double elapsedTime;
double lastError, P_Error, I_Error, D_Error;
double inPut, outPut;
float setPoint = 0;

CTBot myBot;

String ssid = "Clase_IoT";
String pass =  "0123456789";
String token = "5533017969:AAHjuVYZHczNLjjzORZA1G9RJ3TTrOzlQmo"; //Token del bot

void setup() {
  Serial.begin(115200);
  pinMode(LED , OUTPUT);
  digitalWrite(LED, LOW);
  pinMode(PinPhoto, INPUT);
  pinMode(PinDAC, OUTPUT);
  pinMode(PinADC, INPUT);
  pinMode(PinPOT, INPUT);

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  delay(500);

  if (myBot.testConnection()) {
    Serial.print("Conectado");//Comprobamos que el bot este conectado.
  }

}

void loop() {
  inPut = (3.3 / 4096.0) * analogRead(PinADC); //Se lee el voltaje del sensor

  currentTime = millis(); //Se guarda el tiempo actual
  elapsedTime = currentTime - previousTime; //Se calcula el tiempo transcurrido

  P_Error = setPoint - inPut; //Se  obtiene el error proporcional
  I_Error += P_Error * elapsedTime; //Se obtiene el error Integral
  D_Error = (P_Error - lastError) / elapsedTime; //Se obtiene el error derivativo
  outPut = (kp * P_Error) + (ki * I_Error) + (kd * D_Error); //Se calcula la salida del controlador

  lastError = P_Error;
  previousTime = currentTime; //Actualizamos los valores de error y tiempo

  dacWrite(PinDAC, outPut);

  Serial.println("\n Input: ");
  Serial.print(inPut);
  Serial.print(",");
  Serial.print("Setpoint: ");
  Serial.print(setPoint);

  TBMessage msg;

  if (myBot.getNewMessage(msg)) { //Revisamos si el bot recivio un mensaje

    if (msg.text.equalsIgnoreCase("/start")) { //comando para comprobar que esta en servicio el bot 
      myBot.sendMessage(msg.sender.id, "Bienvenido, ya puede mandar sus instrucciones");

    } else  if (msg.text.equalsIgnoreCase("/resistencia")) { //comando para pedir la fotoresistencia.

      float sensor = 3.3 / 4096.0 * analogRead(PinPhoto); //Voltaje = x / Flash Size
      String messVolt = "El Voltaje en la fotoresistencia es de: " + String(sensor) + "V";
      myBot.sendMessage(msg.sender.id, messVolt);

    } else  if (msg.text.equalsIgnoreCase("/enciende")) { //Comando para encender el LED 1

      digitalWrite(LED, HIGH);
      String respuesta2 = "LED encendido";
      myBot.sendMessage(msg.sender.id, respuesta2);

    } else  if (msg.text.equalsIgnoreCase("/apaga")) { //Comando para apagar el LED 1.

      digitalWrite(LED, LOW);
      String respuesta3 = "LED apagado";
      myBot.sendMessage(msg.sender.id, respuesta3);

    } else  if (msg.text.toFloat() > 0 && msg.text.toFloat() <= 3.3) { //Aceptamos numeros entre 0 y 3.3 para setpoint
      float newPot = msg.text.toFloat();
      setPoint = newPot;
      myBot.sendMessage(msg.sender.id, "Setpoint establecido");
    }
  }

  delay(50);

}
