// RGB sensor setup.
#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Bin setup.
#include "color.hpp"
const auto bins = Bins(5, [](const Color &lhs, const Color &rhs) -> bool {
    auto mse = sqrt(
        ((int16_t)lhs.r - (int16_t)rhs.r) * ((int16_t)lhs.r - (int16_t)rhs.r) +
        ((int16_t)lhs.g - (int16_t)rhs.g) * ((int16_t)lhs.g - (int16_t)rhs.g) +
        ((int16_t)lhs.b - (int16_t)rhs.b) * ((int16_t)lhs.b - (int16_t)rhs.b));
    return mse < 10.0f;
});

// Selector Setup.
#include "selector.hpp"
const auto selector = Selector(bins.size(), 45, 7, 6);

// Gate setup.
#include "gate.hpp"
const auto gate = Gate(70, 0, 40, 500);

char data[100];

void setup()
{
    // Perform serial startup.
    Serial.begin(9600);
    Serial.println("R, G, B, Bin Assignment");

    // Perform gate startup.
    gate.attach(3);
    gate.load();
    gate.read();

    // Perform selector startup.
    selector.begin();

    // Perform color sensor startup.
    tcs.begin();
}

void loop()
{
    if (Serial.available())
    {
        char c = Serial.read();

        if (c == 's')
        {
            Serial.println("Testing Selector");
            for(uint8_t i = 0; i < selector.getBinCount(); i++)
            {
                selector.select(i);
                delay(500);
            }
        }

        if (c == 'r')
        {
            selector.select(0);
        }

        else if (c == 'c')
        {
            float red, green, blue;
            tcs.getRGB(&red, &green, &blue);
            uint8_t binAss = bins.getBin(Color(red, green, blue));
            sprintf(data, "%d, %d, %d, %d", int(red), int(green), int(blue), int(binAss));
            Serial.println(data);
        }

        else if (c == 'e')
        {
            Serial.println("Dropping Skittle");
            gate.drop();

            Serial.println("Loading Skittle");
            gate.load();

            Serial.println("Reading Skittle");
            gate.read();            
        }

        // Some code to run 20 times.
        else if (c == 'g')
        {
            for (uint8_t i = 0; i < 20; i++)
            {
                float red, green, blue;
                tcs.getRGB(&red, &green, &blue);
                uint8_t binAss = bins.getBin(Color(red, green, blue));
                sprintf(data, "%d, %d, %d, %d", int(red), int(green), int(blue), int(binAss));
                Serial.println(data);
                selector.select(binAss);
                gate.drop();
                gate.load();
                gate.read();
            }
        }

        else if (c == '\n')
            ;
        else if (c == '\r')
            ;
        else
        {
            Serial.println(c);
        }
    }
}
