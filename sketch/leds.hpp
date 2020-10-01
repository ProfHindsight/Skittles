#ifndef __LEDS_HPP__
#define __LEDS_HPP__

#include <Arduino.h>

class Leds
{
private:
    uint8_t ledPins[4];

public:
    Leds(uint8_t whitePin, uint8_t redPin, uint8_t greenPin, uint8_t bluePin)
    {
        this->ledPins[0] = whitePin;
        this->ledPins[1] = redPin;
        this->ledPins[2] = greenPin;
        this->ledPins[3] = bluePin;
    }

    typedef enum color
    {
        white = 0,
        red = 1,
        green = 2,
        blue = 3
    } color_t;

    void begin()
    {
        for (int i = 0; i < 4; i++)
        {
            pinMode(this->ledPins[i], OUTPUT);
            digitalWrite(this->ledPins[i], LOW);
        }
    }

    void allOff()
    {
        for (int i = 0; i < 4; i++)
        {
            digitalWrite(this->ledPins[i], LOW);
        }
    }

    void allOn()
    {
        for (int i = 0; i < 4; i++)
        {
            digitalWrite(this->ledPins[i], HIGH);
        }
    }

    void turnOn(color_t led)
    {
        digitalWrite(this->ledPins[led], HIGH);
    }
    
    void turnOff(color_t led)
    {
        digitalWrite(this->ledPins[led], LOW);
    }
};

#endif
