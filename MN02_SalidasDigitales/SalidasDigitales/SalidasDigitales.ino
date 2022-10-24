/* Mini practica 02: Salidas digitales
 *  
 *  Enciende los Leds 1 a 5 de ida y de regreso uno por uno.
 *  
 *  Autores:
 *   González Arceo Carlos Eduardo
 *   Paredez Zamudio Luis Daniel
 */

//Primero creamos un arreglo que tenga el numero de los pines de cada Led.
int leds[5] = {33,25,26,27,14}; 

void setup() {
  //Iniciamos los Leds en output usando un bucle for para recorrer el arreglo.
  for(int i=0; i < 5; i++){
    pinMode(leds[i], OUTPUT);
    }
}

void loop() {
  // Aqui recorremos el arreglo de las posiciones 0 a 4, apagando y encendiendo los Leds 1 a 5.
  for(int i=0; i < 5; i++){
    digitalWrite(leds[i], HIGH);   // Enciende el Led correspondiente.
    delay(50);                       // Esperamos 50 microsegundos.
    digitalWrite(leds[i], LOW);    // Apaga el Led correspondiente.
    delay(50);
    }
  // Aqui recorremos el arreglo de las posiciones 3 a 1 para evitar encender y apagar dos veces los 
  // Leds 1 y 5 dos veces en el loop de regreso
  for(int i=3; i > 0; i--){
    digitalWrite(leds[i], HIGH);   
    delay(50);                     
    digitalWrite(leds[i], LOW);    
    delay(50); 
    }
                       
}
