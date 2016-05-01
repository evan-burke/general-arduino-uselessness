
// Gets temp from a DS18B20 digital temperature probe and 
// prints the temp output to an Adafruit i2c 4-segment LED 
// display about once per second. 


/*-----( Import needed libraries )-----*/
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

/*-----( Declare Constants )-----*/
// edit this to reflect where you're connecting the data pint of the temp probe:
#define ONE_WIRE_BUS 7 

/*-----( Declare objects )-----*/
/* Set up a oneWire instance to communicate with any OneWire device*/
OneWire ourWire(ONE_WIRE_BUS);
Adafruit_7segment matrix = Adafruit_7segment();

/* Tell Dallas Temperature Library to use oneWire Library */
DallasTemperature sensors(&ourWire);

/*-----( Declare Variables )-----*/



void setup() /*----( SETUP: RUNS ONCE )----*/
{
  /*-(start serial port to see results )-*/
  delay(50);
  if(Serial) {
    Serial.begin(9600);
  }
  delay(50);

  matrix.begin(0x70);
  matrix.setBrightness(5);
  matrix.print(10000, DEC);
  matrix.writeDisplay();
  
  /*-( Start up the DallasTemperature library )-*/
  sensors.begin();
}/*--(end setup )---*/


void loop() /*----( LOOP: RUNS CONSTANTLY )----*/
{

unsigned long iterStart = millis();
sensors.requestTemperatures(); // Send the command to get temperatures
//Serial.print("DONE  ");

/* -- print elapsed time -- */
if(Serial) {
  float elapsedSec = float(millis() / 1000);
  float elapsedMsec = (millis() % 1000);
  float twodec = (elapsedMsec / 10); // first 2 digits of milliseconds
  Serial.print(elapsedSec, 0); Serial.print(".");
  Serial.print(twodec, 0); Serial.print("s  |   ");

  //Serial.print("Device 1 (index 0) = ");
  Serial.print(sensors.getTempFByIndex(0), 1);
  Serial.println(" Degrees F");
}
matrix.print(sensors.getTempFByIndex(0), 1);
matrix.writeDisplay();

unsigned long iterEnd = millis() ;

unsigned long measureTime = (iterEnd - iterStart);
//Serial.print("receiving from temp probe took this many ms: ");
//Serial.println(measureTime);

// reads from the sensors take an avg of ~750-800ms. 
// this code will keep this consistent if something goes faster for whatever reason
if (measureTime < 1000 && measureTime > 0)  { 
  int timeToDelay = 1000 - measureTime;
  if (timeToDelay > 0) { 
    delay(timeToDelay);
  }
} else {
  // something went wrong? slow us down
  if(Serial) {
    Serial.print("oops what happened. measureTime was: "); Serial.println(measureTime);
  }
  delay(1000);
}





}/* --(end main loop )-- */

/* ( THE END ) */
