#include <math.h> //this library is needed for the mathematics behind the color temperature -> RGB values calculations
//Credits for the 'color temperature -> RGB values'-formulas go to http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/
//I only converted it to Arduino-compatible Objective C.

//Output pins:
const int GREEN = 3;
const int RED = 5;
const int BLUE = 9;
//Pin 3, 5 and 9 are PWM enabled pins on the Arduino Pro Mini I used. You SHOULD use pins that are PWM enabled.

//Input pins:
const int tempPot = A0;
const int dimPot = A1;

float dimFactor;
int colorTemp;

float redAmount;
float greenAmount;
float blueAmount;

void setup() {
  Serial.begin(9600); //needed for debug
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

  pinMode(tempPot, INPUT);
  pinMode(dimPot, INPUT);
}

void loop() {
  //Read both potentiometers
  dimFactor = analogRead(dimPot)/1023.0;        //The .0 is a wake-up to the compiler to make this a float-operation instead of an int-operation
  colorTemp = 1000 + analogRead(tempPot)*6;     //This gives a minimum of 1000K and a maximum of 7144K
  
  //debug
  Serial.print("colorTemp: ");
  Serial.print(colorTemp);
  Serial.print(", dimFactor: ");
  Serial.print(dimFactor);
  Serial.print("; ");

  //Calculate Red
  if (colorTemp <= 6600) {
    redAmount = 255;
  } else {
    redAmount = 608.873 / pow(colorTemp-6000, 0.136);
  }

  //Calculate Green
  if (colorTemp <= 6600) {
    greenAmount = 135 * log(colorTemp) - 932.5;
  } else {
    greenAmount = 413 / pow(colorTemp-6000, 0.0755);
  }

  //Calculate Blue
  if (colorTemp >= 6600) {
    blueAmount = 255;
  } else {
    if (colorTemp <= 1900) {
      blueAmount = 0;
    } else {
      blueAmount = 0.0543 * colorTemp - 103.085;
    }
  }

  //Combine the calculated color values with the dimFactor
  //Round the float values to ints so they can be analogWritten
  int redOut = round(redAmount * dimFactor);
  int greenOut = round(greenAmount * dimFactor);
  int blueOut = round(blueAmount * dimFactor);

  Serial.print("rgb(");
  Serial.print(redOut);
  Serial.print(", ");
  Serial.print(greenOut);
  Serial.print(", ");
  Serial.print(blueOut);
  Serial.println(")");

  //Output to the LED-strip
  analogWrite(RED, redOut);
  analogWrite(GREEN, greenOut);
  analogWrite(BLUE, blueOut);
  delay(5);
}
