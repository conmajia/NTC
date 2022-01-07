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
NTC::NTC(int pin) {
    _pin = pin;
}
NTC::NTC(int pin, int value) : NTC(pin) {
    _ntc = value;
}
NTC::NTC(int pin, int value, int b) : NTC(pin, value) {
    _b = b;
}

///////////////////////////////////
// Public funtions
///////////////////////////////////
float NTC::celsius() {
    float average = 0;
    for (int i = 0; i < _repeat; i++) {
        average = average + analogRead(_pin);
        if (_repeat > 1) delay(10);
    }
    average = average / _repeat;
    // calculate for temperature
    average = 1023 / average - 1;
    average = _resistor / average;
    // Steinhart-Hart Equation
    // ARef = 5V
    float celsius;
    celsius = average / _ntc;
    celsius = log(celsius);
    celsius = celsius / _b;
    celsius = celsius + 1.0 / (NTC_DEFAULT_T - NTC_ABSOLUTE_ZERO);
    celsius = 1.0 / celsius;
    celsius = celsius + NTC_ABSOLUTE_ZERO;
    return celsius;
}
float NTC::fahrenheit() {
    return (9.0 / 5.0) * celsius() + 32.0;
}