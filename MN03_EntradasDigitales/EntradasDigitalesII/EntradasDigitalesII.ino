
/* Mini practica 03: Entradas Digitales Pt II
  Objetivos:

  I. Encender un led al pulsar un botón dejando el estado del led permanente, al presionar de nuevo el botón cambiar de estado el led.

  Código creado por los alumnos
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea

*/

#define oneLED 14 //LED 1 a prender. 
#define SW1 4 //Switch #2 solo por comodidad.
#define extraLED 33
byte ultimoEstado = LOW; //Del botón
byte estadoLED = LOW; //Del led. 

void setup() {
  pinMode(oneLED, OUTPUT);
  pinMode(extraLED, OUTPUT); //Prendía solo asi que desde acá lo apagamos.
  pinMode(SW1, INPUT);
}

void loop() {
  byte estadoBoton = digitalRead(SW1); //variable para almacenar el estado del boton PushUp/PushDown
  if (estadoBoton != ultimoEstado) { //Comparamos estados, hay 4 posibilidades. H-H, L-L, L-H, H-L. 
    ultimoEstado = estadoBoton; //Si son iguales no entramos al loop. 
    if (estadoBoton == LOW) { //Esto nos ayuda a apagar y prender. Realmente nos importa que este apagado o no, entonces primero validamos eso. 
      estadoLED = (estadoLED == HIGH) ? LOW : HIGH; //One-liner. Si se cumple la condición, entonces mandamos LOW, si no, HIGH
      digitalWrite(oneLED, estadoLED); // Y finalmente lo escribimos en el LED. 
    }
  }
  delay(50); //El delay quita un gran porcentaje de falsos positivos.
}
