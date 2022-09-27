//Bibliotecas----------------------------------
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

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
 
void setup(){
  Serial.begin(115200);
  setup_wifi();
  
  //Comenzar el servidor-----------------------
  server.begin();

  //GET texto plano----------------------------
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hola, grupo de IoT");
  }); 

  server.on("/pageA", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Web A");
  });
  
  server.on("/pageB", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Web B");
  });
}
 
void loop(){

}
