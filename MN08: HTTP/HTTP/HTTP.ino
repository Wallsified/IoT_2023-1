/* Mini Práctica #8: HTTP
   Objetivos:
  Utilizando el ESP32 como servidor, implemente una interfaz de usuario donde monitoree los
  valores del potenciómetro y la LDR, y que además sea posible modificar el brillo de LED 3
  con PWM y encender los LEDs 1 y 5.

  Código modificado por los alumnos:
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea

*/

//Bibliotecas----------------------------------
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Credenciales Red
const char* ssid = "Mark Wifi";
const char* password = "achtzehnpfannkuchen18"; //achtzehnpfannkuchen18

// Constantes de la ejecución.
const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";
const char* PARAM_INPUT = "value";

// Constantes para PMW
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
String sliderValue = "0";

// Pin LDR
const int sensorPin = 34; 

//LEDs -------------------------------------
#define ledOne 14 
#define ledFive 33 
#define ledThree 26

//Objeto AsyncWebServer, puerto 80-------------
AsyncWebServer server(80);

//Conexión WiFi--------------------------------
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
  delay(2000);

  //Función para error 404
  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send(404, "text/plain", "Error 404");
  });
}

// Acciones a realizar durante la ejecución. 
String processor(const String& var) {

  if (var == "BUTTONPLACEHOLDER") { //switches HTTP
    String buttons = "";
    buttons += "<h4>LED 1</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"14\" " + outputState(ledOne) + "><span class=\"slider1\"></span></label>";
    buttons += "<h4>LED 5</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"33\" " + outputState(ledFive) + "><span class=\"slider2\"></span></label>";
    return buttons;
  }

  if (var == "SLIDERVALUE") { //slider HTTP
    return sliderValue;
  }
  return String();
}

// Estado de salida del LED
String outputState(int output) {
  if (digitalRead(output)) {
    return "checked";
  }
  else {
    return "";
  }
}

// Como tratamos el slider del LED + PWM como una salida String, entonces lo leemos de la misma forma
String ReadSensor() {
  float sensorVal = analogRead(sensorPin) * (3.3 / 4096.0);
  Serial.println(sensorVal);
  return String(sensorVal);
}

void setup() {
  Serial.begin(115200);
  setup_wifi();

  // Setup LED's
  pinMode(ledOne, OUTPUT);
  digitalWrite(ledOne, LOW);
  pinMode(ledFive, OUTPUT);
  digitalWrite(ledFive, LOW);
  pinMode(ledThree, OUTPUT);
  digitalWrite(ledThree, LOW);

  // Setup PMW
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledThree, ledChannel);
  ledcWrite(ledChannel, sliderValue.toInt());

  //Comenzar el servidor-----------------------
  server.begin();

  //Revisar archivos subidos a la memoria flash---
  if (!SPIFFS.begin(true)) {
    Serial.println("Hubo un error en SPIFFS. Vuelve a enviar los archivos.");
    return;
  }

  //Ruta raíz del archivo HTML-----------------
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Archivo CSS--------------------------------
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  //  Archivo JS--------------------------------
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/script.js", "text/js");
  });

  // WIP- Request entre ESP32 -> Switches HTTP -> ON/OFF LEDs
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage1;
    String inputMessage2;
    // Obtener valor del request de los switches. ON/OFF?>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else {
      inputMessage1 = "Mensaje no enviado";
      inputMessage2 = "Mensaje no enviado";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - estado: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });

  // Enviar información sobre LDR (Voltaje)
  server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", ReadSensor().c_str());
  });

  // Request entre ESP32 -> Slider PWM -> LED 3
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    // Obtener valor del slider y convertirlo a intensidad ON.  
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      ledcWrite(ledChannel, sliderValue.toInt());
    }
    else {
      inputMessage = "Mensaje no enviado";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });

}

void loop() {

}
