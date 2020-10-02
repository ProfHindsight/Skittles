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
const auto gate = Gate(75, 0, 40, 500);

// LEDs setup
#include "leds.hpp"
const auto leds = Leds(5, 9, 11 ,10);

char data[100];
uint16_t r,g,b,w;

void setup()
{
    // Perform serial startup.
    Serial.begin(9600);
    Serial.println("Xy where X is the RGB/Clear value and y is illuminating LED");
    Serial.println("Rw,Gw,Bw,Ww,Rr,Gr,Br,Wr,Rg,Gg,Bg,Wg,Rb,Gb,Bb,Wb,Ra,Ga,Ba,Wa");

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

        
    
    for(int i = 0; i < 20; i++)
    {
        gate.drop();
        gate.load();
        gate.read();
        leds.turnOn(Leds::white);
        sensor.getRaw(&r, &g, &b, &w);
        sensor.getRaw(&r, &g, &b, &w);
        sensor.getRaw(&r, &g, &b, &w);
        sprintf(data, "%d,%d,%d,%d,", r, g, b, w);
        Serial.print(data);
        leds.turnOff(Leds::white);
        leds.turnOn(Leds::red);
        sensor.getRaw(&r, &g, &b, &w);
        sensor.getRaw(&r, &g, &b, &w);
        sensor.getRaw(&r, &g, &b, &w);
        sprintf(data, "%d,%d,%d,%d,", r, g, b, w);
        Serial.print(data);
        leds.turnOff(Leds::red);
        leds.turnOn(Leds::green);
        sensor.getRaw(&r, &g, &b, &w);
        sensor.getRaw(&r, &g, &b, &w);
        sensor.getRaw(&r, &g, &b, &w);
        sprintf(data, "%d,%d,%d,%d,", r, g, b, w);
        Serial.print(data);
        leds.turnOff(Leds::green);
        leds.turnOn(Leds::blue);
        sensor.getRaw(&r, &g, &b, &w);
        sensor.getRaw(&r, &g, &b, &w);
        sensor.getRaw(&r, &g, &b, &w);
        sprintf(data, "%d,%d,%d,%d,", r, g, b, w);
        Serial.print(data);
        leds.turnOff(Leds::blue);
        leds.allOn();
        sensor.getRaw(&r, &g, &b, &w);
        sensor.getRaw(&r, &g, &b, &w);
        sensor.getRaw(&r, &g, &b, &w);
        sprintf(data, "%d,%d,%d,%d", r, g, b, w);
        Serial.println(data);
        leds.allOff();
    }
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

}
