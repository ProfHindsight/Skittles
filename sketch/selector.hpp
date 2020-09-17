#ifndef __SELECTOR_HPP__
#define __SELECTOR_HPP__

#include <AccelStepper.h>

class Selector
{
    private:
        AccelStepper stepper;
        uint16_t maxAngle;
        uint32_t binDistance;
        uint8_t numberOfBins;
        
        // 400 steps per revolution, 16th microstepping
        const uint32_t numberOfStepsPerRevolution = 6400;

        void moveTo(uint32_t targetPos)
        {
            this->stepper.moveTo(targetPos);
            while(this->stepper.currentPosition() != targetPos) this->stepper.run();
        }
    
    public:
        Selector(uint8_t numberOfBins, uint16_t maxAngle, uint8_t stepPin, uint8_t directionPin)
        {
            this->stepper = AccelStepper(AccelStepper::DRIVER, stepPin, directionPin);
            
            if (maxAngle < 360)
            {
                this->maxAngle = maxAngle;
            }
            else
            {
                this->maxAngle = 0;
            }
            
            
            if (numberOfBins > 1)
            {
                this->binDistance = int((long long) (this->numberOfStepsPerRevolution * maxAngle) / (numberOfBins - 1) / 360);
            }
            else
            {
                this->binDistance = 0;
            }
            this->numberOfBins = numberOfBins;
        }

        void begin()
        {
            this->stepper.setMinPulseWidth(1);
            this->stepper.setMaxSpeed(100000);
            this->stepper.setAcceleration(50000); 
        }

        void select(uint8_t bin)
        {
            uint32_t targetPos = this->binDistance * bin;

            // Blocking function to move to target position
            if (targetPos < numberOfStepsPerRevolution)
            {
                this->moveTo(targetPos);
            }
        }

        uint8_t getBinCount()
        {
            return this->numberOfBins;
        }

        void test()
        {
            this->moveTo(500);
            this->moveTo(0);
        }
};

#endif