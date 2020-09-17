#ifndef __GATE_HPP__
#define __GATE_HPP__

#include <Servo.h>

class Gate
{
private:
    Servo servo;
    uint8_t dropPosition;
    uint8_t loadPosition;
    uint8_t readPosition;
    uint16_t delayMs;

public:
    Gate(uint8_t dropPosition, uint8_t loadPosition, uint8_t readPosition, uint16_t delayMs)
    {
        this->dropPosition = dropPosition;
        this->loadPosition = loadPosition;
        this->readPosition = readPosition;
        this->delayMs = delayMs;
    }

    void attach(uint8_t pin)
    {
        this->servo.attach(pin);
    }

    void drop()
    {
        this->servo.write(this->dropPosition);
        delay(this->delayMs);
    }

    void load()
    {
        this->servo.write(this->loadPosition);
        delay(this->delayMs);
    }

    void read()
    {
        this->servo.write(this->readPosition);
        delay(this->delayMs);
    }
};

#endif
