/*
  NTC test

  For Arduino

  Use a 5V reference voltage to sense temperature with NTC.

  Schematic:

  (5V)--(R)--+--(NTC)--(GND)
             |
           (MCU)

  created Jan 7, 2022
  by Greg Conmajia

  This example code is in the public domain.

  https://github.com/conmajia/NTC
*/

#include "NTC.h"

NTC t(A0);

void setup() {
  // open the serial port:
  Serial.begin(9600);
}

void loop() {
  // read temperature
  Serial.print("Temperature: ");
  Serial.print(t.celsius());
  Serial.print(" Celcius, ");
  Serial.print(t.fahrenheit());
  Serial.println(" Fahrenheit.");
  delay(1000);
}