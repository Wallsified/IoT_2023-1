/* Proyecto Final

  Código modificado por los alumnos:
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea

¿Qué hace el proyecto?

Al final de Monsters University, el juego final de las
"Sustolimpiadas" consiste en una cámara de simulación 
de sustos, en donde el equipo que más puntos-por-susto
consiga, será nombrado campeón. 

Nosotros hicimos una aproximación a dicho juego usando 
lo que aprendimos en el curso de Introducción a Ciencias de
la Computación y algo de creativad inocente.

*/

//Bibliotecas----------------------------------
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SH110X.h"

//Constantes de la Ejecución.
const char* ssid = "INFINITUMA6A4_2.4"; //"Clase_IoT";//"INFINITUMA6A4_2.4";//"Mark Wifi";
const char* password = "Zamudiov3!";//"Zamudiov3!";//"achtzehnpfannkuchen18";
String decibels = "0";

//Stuff de la pantalla.
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1       // Reset pin 
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define i2c_Address 0x3c
const int sampleWindow = 50;  // La pantalla se refresca cada 50ms
unsigned int sample; //Valor de la lectura del micrófono. 

//Objeto AsyncWebServer, puerto 80-------------
AsyncWebServer server(80);

void start_screen() {
  display.begin(i2c_Address, true); //Inicia pantalla              
  display.clearDisplay(); //Limpiamos lo que pudo estar antes. 
  display.setCursor(0, 0); //Coordenadas de inicio. 
  display.setTextSize(1); //Tamaño de letra
  display.setTextColor(SH110X_WHITE); //Color de letra
  display.display(); 
  delay(1000);
  display.clearDisplay();
}

void writeScreen(float decibelLevel) {
  display.setCursor(0, 0);
  display.setTextSize(1.8);
  display.print(decibelLevel); //Imprimimos el valor del micrófono. 
  display.print(" dB");

  for (int x = 16; x < 165; x = x + 17) {
    display.drawLine(x, 32, x, 27, SH110X_WHITE); //División de las partes del grito. 
  }

  display.drawRoundRect(0, 32, 120, 19, 6, SH110X_WHITE);       //borde de la bateria en pantalla
  int r = map(decibelLevel, 0, 120, 1, 120);                       //la bateria tiene el borde la pantalla con eso
  display.fillRoundRect(1, 33, r, 18, 6, SH110X_WHITE);         //y ahora la acompletamos por "dentro"
  display.display();
  display.clearDisplay();
}

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

  if (var == "DECIBEL") {
    return decibels;
  }
  return String();
}

float readDecibels() {
  unsigned long startMillis = millis();                  // no podemos usar delay() en este caso. 
  float peakToPeak = 0;                                  // puntoAPunto. Es el rango de lecturas a trabajar. 
  unsigned int signalMax = 0;                            
  unsigned int signalMin = 700;                         //Aunque el valor máximo es 1024, bajarlo a 700 ayuda a hacerlo más sensible.

  // Consideramos 50 ms para tomar la muestra de db. 
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(34);                             //lectura del microfono
    if (sample < 1024)                                  // quitamos lecturas no necesarias. 
    {
      if (sample > signalMax)
      {
        signalMax = sample;                           // solo val. max.
      }
      else if (sample < signalMin)
      {
        signalMin = sample;                           // solo val. min. 
      }
    }
  }
  peakToPeak = signalMax - signalMin;                    // max - min = amplitud peak-peak 
  float db = map(peakToPeak, 20, 900, 49.5, 90);         //calibramos a que si nos de los decibeles. 
  return db;
}

//Leemos la información que nos manda el micrófono. 
String ReadSensor() {
  float sensorVal = readDecibels();
  Serial.println(sensorVal);
  return String(sensorVal);
}

void setup() {
  //Iniciamos los Leds en output usando un bucle for para recorrer el arreglo.
  Serial.begin(115200);
  
  setup_wifi();
  start_screen();
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
  server.on("/help.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/server.js", "text/js");
  });

  // Imágenes --------------------------------
  server.on("/door.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/door.png", "image/png");
  });

  // Enviar información sobre los decibeles.
  server.on("/decibel", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println(ReadSensor().c_str());
    request->send(200, "text/plain", ReadSensor().c_str());
  });
}

//Loop para ir escribiendo en pantalla la información calculada. 
void loop() {
  float dbToScreen = readDecibels();
  writeScreen(dbToScreen);
  delay(500);
}
