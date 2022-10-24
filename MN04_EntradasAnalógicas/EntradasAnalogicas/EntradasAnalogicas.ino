/*Objetivos:
 * 1. Observar el comportamiento de la fotorresistencia (LDR) cuando se limita la cantidad de luz.
 * 2. Encender los 5 leds de la placa en función de la luz inducida a la fotorresistencia, es decir, 
 * sin nada de luz que ninguno se enciende y conforme la luz llega al sensor se van iluminando los demás 
 * leds hasta que los 5 se iluminen por completo.
 * 
 *  Código creado por los alumnos
 * - Paredes Zamudio Luis Daniel @Wallsified
 * - González Arceo Carlos Eduardo @Carlos-crea
 */

//Primero creamos un arreglo que tenga el numero de los pines de cada Led.
int leds[5] = {33,25,26,27,14}; 
#define PinADC 34 //LDR en la placa
float constante = 0.6;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT); // Y los declaramos como OUTPUT todos a la vez.
  }
  Serial.begin(115200); //Bits x Segundo/Velocidad de Transferencia del ESP32. Por defecto iniciamos en esa velocidad. 
  pinMode(PinADC, INPUT);
}

void loop() {
  float sensor = 3.3/4096.0 * analogRead(PinADC); //Voltaje = x / Flash Size 
  int division = sensor/ constante; //La idea es que a cierto voltaje prenda una x cantidad de leds...
  Serial.println(sensor); //Lo mandamos a la pantalla del serial para ver sus cambios. 
  if(division > 0){
    for(int i=0; i < division; i++){
      digitalWrite(leds[i], HIGH);
    }
  }
  if(division < 5){
    for(int i=4; i >= division; i--){ //..Y que la misma falta de voltaje, apague otra cantidad y de leds. 
        digitalWrite(leds[i], LOW);
      }
  }
  delay(100);
  

}
