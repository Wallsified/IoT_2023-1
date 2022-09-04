/* Mini practica 03: Entradas Digitales Pt I
  Objetivos:

  I. Al presionar el botón 1 (SW1) encender los 5 leds, al presionar el botón 2 (SW2) apagarlos.

  Código creado por los alumnos
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea

*/

int leds[5] = {33, 25, 26, 27, 14}; //array que declara todos los leds en sus pines.
#define SW1 15
#define SW2 4


void setup() {

  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT); // Y los declaramos como OUTPUT todos a la vez.
  }
  pinMode(SW1, INPUT); //Iniciamos nuestros switches como input
  pinMode(SW2, INPUT);

}

void loop() {

  if (digitalRead(SW2) == LOW) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(leds[i], LOW);
    }
  }

  if (digitalRead(SW1) == HIGH) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(leds[i], HIGH);
    }
  }
}
