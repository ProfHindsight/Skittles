#ifndef __SENSOR_HPP__
#define __SENSOR_HPP__

// RGB sensor setup.
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "color.hpp"

class Sensor
{
private:
    Adafruit_TCS34725 tcs;
    Color color;
    float red, green, blue;

public:
    Sensor()
    {
        this->tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
    }

    void begin()
    {
        this->tcs.begin();
    }

    Color& read()
    {
        this->tcs.getRGB(&this->red, &this->green, &this->blue);
        this->color.from(this->red, this->green, this->blue);

        return this->color;
    }

    void getRaw(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *white)
    {
        this->tcs.getRawData(red, green, blue, white);
    }

    Color& getLast()
    {
        return this->color;
    }
};

#endif
