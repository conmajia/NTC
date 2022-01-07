/*
 * ntc.h - Simple NTC thermistor library for arduino
 * Greg Conmajia <conmajia@gmail.com>
 * Jan. 7, 2022
 * Released into the public domain.
 */

#ifndef _NTC_H_
#define _NTC_H_

#define NTC_ABSOLUTE_ZERO       -273.15     // Absolute Zero = -273.15 Celsius
#define NTC_NaN                 0xffff      // Not a Number
#define NTC_NA                  0xff        // Not Available
#define NTC_DEFAULT_B           3450        // common B parameter: 3000 to 4000
#define NTC_DEFAULT_T           25          // nominal T parameter is almost always 25(C)
#define NTC_DEFAULT_VALUE       10000       // resistance of the NTC
#define NTC_DEFAULT_RESISTOR    10000       // series resistor in the voltage divider
#define NTC_DEFAULT_REPEAT      5           // repeated sample count of a single temperature read

// Definition of the NTC sensor class
class NTC {
    public:
        explicit NTC(int pin);              // initializer (10K)
        explicit NTC(int pin, int value);   // initializer with resistance value
        explicit NTC(int pin, int value, int B); // initializer with resistance value and B parameters
        float celsius();                    // return current temperature in Celsius
        float fahrenheit();                 // return current temperature in Fahrenheit
    private:
        int _pin = NTC_NA;
        int _b = NTC_DEFAULT_B;
        int _t = NTC_DEFAULT_T;
        int _repeat = NTC_DEFAULT_REPEAT;
        int _ntc = NTC_DEFAULT_VALUE;
        int _resistor = NTC_DEFAULT_RESISTOR;
        int _sampled_value = NTC_NaN;
        float _last_celsius = NTC_NaN;
        float _last_fahrenheit = NTC_NaN;
};

#endif