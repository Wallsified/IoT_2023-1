/*Objetivos:
 * 1. Observar el comportamiento de la fotorresistencia (LDR) cuando se limita la cantidad de luz.
 * 2. Encender los 5 leds de la placa en función de la luz inducida a la fotorresistencia, es decir, 
 * sin nada de luz que ninguno se enciende y conforme la luz llega al sensor se van iluminando los demás 
 * leds hasta que los 5 se iluminen por completo.
 * 
 * Ideas: 
 * - Estructura con el array de leds y ligarlo a intervalos de voltaje. Si es un intervalo x, prender n led. 
 *  Código creado por los alumnos
 * - Paredes Zamudio Luis Daniel @Wallsified
 * - González Arceo Carlos Eduardo @Carlos-crea
 */


#define PinADC 34 //LDR en la placa

void setup() {
  Serial.begin(115200); //Bits x Segundo/Velocidad de Transferencia del ESP32. Por defecto iniciamos en esa velocidad. 
  pinMode(PinADC, INPUT);
}

void loop() {
  float sensor = 3.3/4096.0 * analogRead(PinADC); //Voltaje = x / Flash Size 
  Serial.println(sensor);
  delay(1000);
  
  // if sensor = intervaloX, entonces prendeLEDS[i]
  

}
