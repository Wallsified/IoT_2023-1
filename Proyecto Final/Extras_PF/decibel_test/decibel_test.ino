/*
 * Dummy que inicializa la pantalla con el contador de decibeles. Este debe de ser la base de lo que
 * queremos al final. 
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define i2c_Address 0x3c 

const int sampleWindow = 50;                              // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup()
{
  Serial.begin(115200);                                    //Serial comms for debugging
  display.begin(i2c_Address, true);              //OLED display start
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.display();
  delay(1000);
  display.clearDisplay();
}

//--------------------------------------------------------------------------------------------
//                                         MAIN LOOP
//--------------------------------------------------------------------------------------------

void loop()
{
  unsigned long startMillis = millis();                  // Start of sample window
  float peakToPeak = 0;                                  // peak-to-peak level

  unsigned int signalMax = 0;                            //minimum value
  unsigned int signalMin = 1024;                         //maximum value

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = digitalRead(36);                             //get reading from microphone
    if (sample < 1024)                                  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;                           // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;                           // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
  float db = map(peakToPeak, 20, 900, 49.5, 90);         //calibrate for deciBels
  display.setCursor(0, 0);                               //cursor to upper left
  display.setTextSize(1.5);                                //set text size to 2
  display.print(db);                                     //write calibrated deciBels
  display.print(" dB");                                  //write units


  for (int x = 16; x < 165; x = x + 17) {                 //draw scale
    display.drawLine(x, 32, x, 27, SH110X_WHITE);
  }
  display.drawRoundRect(0, 32, 120, 19, 6, SH110X_WHITE);       //draw outline of bar graph
  int r = map(db, 0, 120, 1, 120);                       //set bar graph for width of screen
  display.fillRoundRect(1, 33, r, 18, 6, SH110X_WHITE);         //draw bar graph with a width of r
  display.display();                                     //show all that we just wrote & drew
  display.clearDisplay();                                //clear the display


}
