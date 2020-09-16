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
    Gate(Servo servo, uint8_t dropPosition, uint8_t loadPosition, uint8_t readPosition, uint16_t delayMs)
    {
        this->servo = servo;
        this->dropPosition = dropPosition;
        this->loadPosition = loadPosition;
        this->readPosition = readPosition;
        this->delayMs = delayMs;
    }

    void drop()
    {
        servo.write(this->dropPosition);
        delay(this->delayMs);
    }

    void load()
    {
        servo.write(this->loadPosition);
        delay(this->delayMs);
    }

    void read()
    {
        servo.write(this->readPosition);
        delay(this->delayMs);
    }
};

#endif
