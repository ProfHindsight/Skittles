// Stepper setup.
#include <AccelStepper.h>
#define PIN_STEP 7
#define PIN_DIRECTION 6
// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER, PIN_STEP, PIN_DIRECTION); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

// RGB sensor setup.
#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Bin setup.
#include "color.hpp"
const auto bins = Bins(3, [](const Color &lhs, const Color &rhs) -> bool {
    auto mse = sqrt(
        ((int16_t)lhs.r - (int16_t)rhs.r) * ((int16_t)lhs.r - (int16_t)rhs.r) +
        ((int16_t)lhs.g - (int16_t)rhs.g) * ((int16_t)lhs.g - (int16_t)rhs.g) +
        ((int16_t)lhs.b - (int16_t)rhs.b) * ((int16_t)lhs.b - (int16_t)rhs.b));
    return mse < 10.0f;
});

// Gate setup.
#include "gate.hpp"
const auto gate = Gate(3, 32, 120, 60, 500);

void setup()
{
    Serial.begin(9600);
    Serial.println("R, G, B");

    // Move gate to load position.
    gate.load();

    // Set blocking pulse width in us
    stepper.setMinPulseWidth(1);
    stepper.setMaxSpeed(100000);
    stepper.setAcceleration(10000);
    //  stepper.moveTo(5000);

    tcs.begin();
}

void loop()
{
    if (Serial.available())
    {
        char c = Serial.read();
        if (c == 's')
        {
            Serial.println("Moving Stepper");
            if (stepper.currentPosition() == 500)
            {
                stepper.moveTo(-stepper.currentPosition());
            }
            else
            {
                stepper.moveTo(500);
            }
        }
        else if (c == 'c')
        {
            float red, green, blue;
            tcs.getRGB(&red, &green, &blue);
            Serial.print(int(red));
            Serial.print(',');
            Serial.print(int(green));
            Serial.print(',');
            Serial.println(int(blue));

            Serial.print("Bin assignment: ");
            Serial.println(bins.getBin(Color(red, green, blue)));
        }
        else if (c == 'e')
        {
            Serial.println("Reading Skittle");
            gate.read();

            Serial.println("Dropping Skittle");
            gate.drop();

            Serial.println("Loading Skittle");
            gate.load();
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

    // This function must be called as often as possible and will step the motor once per call.
    stepper.run();
}
