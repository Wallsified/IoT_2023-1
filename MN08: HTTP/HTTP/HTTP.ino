/* Mini Práctica #8: HTTP
   Objetivos:
   
   Utilizando el ESP32 como servidor, implemente una interfaz de usuario donde monitoree los
   valores del potenciómetro y la LDR, y que además sea posible modificar el brillo de LED 3
   con PWM y encender los LEDs 1 y 5.

  Código creado por los alumnos
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea

*/


//Bibliotecas----------------------------------
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

//Credenciales Red-----------------------------
const char* ssid = "Clase_IoT";
const char* password = "0123456789";

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
  
  Serial.println("  WiFi conectado. Dirección IP: " + WiFi.localIP());
  delay(2000);

  //404
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Error 404");
  });
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  //Inicializar SPIFFS-------------------------
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS\n Please mount the files again.");
    return;
  }

  //Comenzar el servidor-----------------------
  server.begin();

  //GET HTML-----------------------------------
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false);
  });

  server.on("/pageA", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/pageA.html", String(), false);
  });
  
  //Cargar style.css---------------------------
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
}

void loop() {

}
