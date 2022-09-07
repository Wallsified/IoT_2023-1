
/* Mini practica 01: Frecuncia Ojo Humano
  Objetivos:

  I. Encontrar la frecuencia máxima a la que el ojo humano observa el parpadeo de un diodo LED

  Código creado por el Equipo de Arduino y modificado por los alumnos:
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea

*/

#define oneLED 14
void setup() {

  pinMode(oneLED, OUTPUT);
}


void loop() {
  digitalWrite(oneLED, HIGH);   // HIGH = Prendido
  delay(15);                    // Lo minimo que podemos esperar para que se vea la frecuencia del parpadeo.
  digitalWrite(oneLED, LOW);    // LOW = Apagado
  delay(15);                    // Se repite el delay para que al loopear el programa se vuelva a prender y así sucesivamente.
}
