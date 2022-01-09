/*
  NTC.cpp

  Copyright (c) 2022, Greg Conmajia

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "NTC.h"
#include "Arduino.h"

// constructors
NTC::NTC() {
    this->_pin = NTC_NA;
}
NTC::NTC(int pin) {
    this->_pin = pin;
}
NTC::NTC(int pin, int value) : NTC(pin) {
    this->_ntc = value;
}
NTC::NTC(int pin, int value, int b) : NTC(pin, value) {
    this->_b = b;
}
///////////////////////////////////
// Public funtions
///////////////////////////////////
float NTC::celsius() {
    int raw = 0;
    for (int i = 0; i < this->_repeat; i++) {
        raw += analogRead(this->_pin);
        if (this->_repeat > 1) delay(10);
    }
    raw /= this->_repeat;
    float average;
    average = raw / this->_repeat;
    // calculate for temperature
    average = 1023 / average - 1;
    average = this->_resistor / average;
    // Steinhart-Hart Equation
    // ARef = 5V
    float celsius;
    celsius = average / this->_ntc;
    celsius = log(celsius);
    celsius = celsius / this->_b;
    celsius = celsius + 1.0 / (NTC_DEFAULT_T - NTC_ABSOLUTE_ZERO);
    celsius = 1.0 / celsius;
    celsius = celsius + NTC_ABSOLUTE_ZERO;
    return celsius;
}
float NTC::fahrenheit() {
    return (9.0 / 5.0) * celsius() + 32.0;
}