//Bibliotecas----------------------------------
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

//Credenciales Red-----------------------------
const char* ssid = "INFINITUMA6A4_2.4";
const char* password = "Zamudiov3!";
const int sensorPin = 34; //LDR

//LEDs GPIO-------------------------------------
#define ledPinBlue 14 //led 1
#define ledPinRed 33 //led 5
#define ledThree 26
const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
const char* PARAM_INPUT = "value";
String sliderValue = "0";

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

//Acciones a realizar--------------------------
String processor(const String& var) {
  //Serial.println(var);
  if (var == "BUTTONPLACEHOLDER") {
    String buttons = "";
    buttons += "<h4>LED 1</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"25\" " + outputState(ledPinBlue) + "><span class=\"slider1\"></span></label>";
    buttons += "<h4>LED 5</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"26\" " + outputState(ledPinRed) + "><span class=\"slider2\"></span></label>";
    return buttons;
  }
  if (var == "SLIDERVALUE") {
    return sliderValue;
  }
  return String();
}

//Estado del led-------------------------------
String outputState(int output) {
  if (digitalRead(output)) {
    return "checked";
  }
  else {
    return "";
  }
}

String ReadSensor() {
  float sensorVal = analogRead(sensorPin) * (3.3 / 4096.0);
  Serial.println(sensorVal);
  return String(sensorVal);
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  //Leds---------------------------------------
  pinMode(ledPinBlue, OUTPUT);
  digitalWrite(ledPinBlue, LOW);
  pinMode(ledPinRed, OUTPUT);
  digitalWrite(ledPinRed, LOW);
  pinMode(ledThree, OUTPUT);
  digitalWrite(ledThree, LOW);

  //Activar PWM--------------------------------
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledThree, ledChannel);
  ledcWrite(ledChannel, sliderValue.toInt());
  
  //Revisar archivos subidos a la memoria flash---
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
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

  //Archivo JS--------------------------------
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/script.js", "text/js");
  });

  //Enviar dato sensor-------------------------
  server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", ReadSensor().c_str());
  });

  //Enviar solicitud a <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage1;
    String inputMessage2;
    //Obtener valor de <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
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

  //Enviar solicitud a <ESP_IP>/slider?value=<inputMessage>
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    //Obtener valor de <ESP_IP>/slider?value=<inputMessage>
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

  //Comenzar el servidor-----------------------
  server.begin();
}

void loop() {

}
