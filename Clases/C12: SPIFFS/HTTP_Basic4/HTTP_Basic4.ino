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

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
  delay(2000);

  //Función para error 404
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Error 404");
  });
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  //Inicializar SPIFFS-------------------------
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
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
