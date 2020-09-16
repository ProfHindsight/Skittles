#define NUMBINS         5
#define MAXANG          180

// Selector Setup.
#include <AccelStepper.h>
#define PIN_STEP 7
#define PIN_DIRECTION 6
// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER, PIN_STEP, PIN_DIRECTION); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

#include "selector.hpp"
const auto selector = Selector(NUMBINS, MAXANG, &stepper);

// RGB sensor setup.
#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Bin setup.
#include "color.hpp"
const auto bins = Bins(NUMBINS, [](const Color &lhs, const Color &rhs) -> bool {
    auto mse = sqrt(
        ((int16_t)lhs.r - (int16_t)rhs.r) * ((int16_t)lhs.r - (int16_t)rhs.r) +
        ((int16_t)lhs.g - (int16_t)rhs.g) * ((int16_t)lhs.g - (int16_t)rhs.g) +
        ((int16_t)lhs.b - (int16_t)rhs.b) * ((int16_t)lhs.b - (int16_t)rhs.b));
    return mse < 10.0f;
});

// Gate setup.
#include "gate.hpp"
const auto gate = Gate(3, 70, 0, 40, 500);

char data[100];

void setup()
{
    // Perform serial startup.
    Serial.begin(9600);
    Serial.println("R, G, B, Bin Assignment");

    // Perform gate startup.
    // gate.attach(3);
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

        else if (c == 'c')
        {
            float red, green, blue;
            tcs.getRGB(&red, &green, &blue);
            uint8_t binAss = bins.getBin(Color(red, green, blue));
            sprintf(data, "%d, %d, %d, %d", red, green, blue, binAss);
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
                sprintf(data, "%d, %d, %d, %d", red, green, blue, binAss);
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
