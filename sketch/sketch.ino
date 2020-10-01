// RGB sensor setup.
#include "sensor.hpp"
const auto sensor = Sensor();

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

// LEDs setup
#include "leds.hpp"
const auto leds = Leds(5, 9, 11 ,10);

char data[100];

void setup()
{
    // Perform serial startup.
    Serial.begin(9600);
    Serial.println("R, G, B, Bin Assignment");

    // Perform LED setup.
    leds.begin();

    // Perform gate startup.
    gate.attach(3);
    gate.drop();
    gate.read();
    
    // Perform color sensor startup.
    sensor.begin();
    bins.setBlank(sensor.read());

    // Prime the gate
    gate.load();
    gate.read();

    // Perform selector startup.
    selector.begin();
}

void loop()
{
    // static uint8_t binAss;
    // static Color color;

    // for(uint8_t i = 0; i < 5; i++)
    // {
    //     binAss = bins.getBin(sensor.read());
    //     if(binAss != -1)
    //     {
    //         break;
    //     }
    //     gate.load();
    //     gate.read();
    // }
    
    // if(binAss == -1)
    // {
    //     selector.select(0);
    //     exit(-1);
    // }
    
    // color = sensor.getLast();
    // sprintf(data, "%d, %d, %d, %d", color.r, color.g, color.b, binAss);
    // Serial.println(data);

    // selector.select(binAss);
    // gate.drop();
    // gate.load();
    // gate.read();
    leds.turnOn(Leds::white);
    delay(1000);
    leds.turnOff(Leds::white);
    leds.turnOn(Leds::red);
    delay(1000);
    leds.turnOff(Leds::red);
    leds.turnOn(Leds::green);
    delay(1000);
    leds.turnOff(Leds::green);
    leds.turnOn(Leds::blue);
    delay(1000);
    leds.turnOff(Leds::blue);
}
