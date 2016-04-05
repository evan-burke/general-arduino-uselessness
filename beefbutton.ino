/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED 7-Segment backpacks 
  ----> http://www.adafruit.com/products/881
  ----> http://www.adafruit.com/products/880
  ----> http://www.adafruit.com/products/879
  ----> http://www.adafruit.com/products/878

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Enable one of these two #includes and comment out the other.
// Conditional #include doesn't work due to Arduino IDE shenanigans.
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

const int brightness = 0;
const int buttonPin = 2;    // the number of the pushbutton pin

int buttonState = 0;

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
    pinMode(13, OUTPUT);
}

void blink(int b) {
 if (b < 0) b = 0;
 if (b > 1000) b=1000;
 for (uint8_t i=0; i<b; i++) {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(200);              // wait for a second
 } //end for
}

void beef() {
  int beefSpeed = 250; // ms between BEEF blinks
  matrix.setBrightness(12);
  matrix.print(0xBEEF, HEX);
  matrix.writeDisplay();
  delay(beefSpeed);
  matrix.setBrightness(0);
  //matrix.clear();
  //matrix.writeDisplay();
  delay(beefSpeed);
}

void loop() {

blink(1);

matrix.clear();
matrix.writeDisplay();
buttonState = digitalRead(buttonPin);

if (buttonState == HIGH) {
 for (uint8_t i=0; i<3; i++) {
   beef();
   delay(20);
 }
  matrix.clear();
  matrix.writeDisplay();
  delay(100);
}


}
