/* Mini practica 05: Salidas Analógicas
  Objetivos:
  I. Encender LED1 usando PWM
  II. Encender LED4 utilizando DAC
  III. En una gráfica (utilizando el Serial Plotter del Arduino y dos entradas analógicas) mostrar el comportamiento de ámbos métodos.

  Código creado por los alumnos:
  - Paredes Zamudio Luis Daniel @Wallsified
  - González Arceo Carlos Eduardo @Carlos-crea
*/

#define PinPWM 26 //also, LED 3
#define PinDAC 25 // LED 4
#define PinADC 13 // //ADC para PWM
#define PinADC2 12 //ADC para DAC

// Variables para el uso de PWM
const int freq = 1000;
const byte channelPWM = 1; //Recordar que el ESP32 tiene 16 canales de envío.
const byte resolution = 8; //También se puede hacer en 16 bits

void setup() {
  Serial.begin(115200);
  pinMode(PinPWM, OUTPUT);
  pinMode(PinDAC, OUTPUT);
  pinMode(PinADC, INPUT);
  pinMode(PinADC2, INPUT);
  ledcSetup(channelPWM, freq, resolution); //Donde, que tan rápido y como se manda la señal.
  ledcAttachPin(PinPWM, channelPWM); //Que PIN y en que canal se mandará la señal
}

void loop() {
  
  for (int i = 0; i < 256; i++) {
    ledcWrite(channelPWM, i); //Para escribir en el LED sobre PWM
    dacWrite(PinDAC, i);
    float v1 = analogRead(PinADC) * (3.3 / 4046.0); // Voltaje w/ PWM
    float v2 = analogRead(PinADC2) * (3.3 / 4096.0); //Voltaje w/ DAC
    Serial.print("PWM:");
    Serial.print(v1);
    Serial.print(",");
    Serial.print("DAC:");
    Serial.println(v2); //El 'ln' acá nos asegura que en el serial plotter se vean separadas. 
    delayMicroseconds(10000); //Ajuste para que sea más practico de visualizar. 
  }

  for (int i = 255; i > -1; i--) {
    ledcWrite(channelPWM, i);
    dacWrite(PinDAC, i);
    float v1 = analogRead(PinADC) * (3.3 / 4046.0); // Voltaje w/ PWM
    float v2 = analogRead(PinADC2) * (3.3 / 4096.0); //Voltaje w/ DAC
    Serial.print("PWM:");
    Serial.print(v1);
    Serial.print(",");
    Serial.print("DAC:");
    Serial.println(v2);
    delayMicroseconds(10000);
  }
}
