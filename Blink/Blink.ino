
int leds[5] = {33,25,26,27,14}; 

void setup() {
  for(int i=0; i < 5; i++){
    pinMode(leds[i], OUTPUT);
    }
}

// the loop function runs over and over again forever
void loop() {
  for(int i=0; i < 5; i++){
    digitalWrite(leds[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(leds[i], LOW);    // turn the LED off by making the voltage LOW
    delay(50);
    }
  for(int i=3; i > 0; i--){
    digitalWrite(leds[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(leds[i], LOW);    // turn the LED off by making the voltage LOW
    delay(50); 
    }
                        // wait for a second
}
