#ifndef __SELECTOR_HPP__
#define __SELECTOR_HPP__

#include <AccelStepper.h>

// Define a stepper and the pins it will use
// #define DEFAULT_STEP_PIN 7
// #define DEFAULT_DIRECTION_PIN 6

class Selector
{
    private:
        AccelStepper stepper;
        uint16_t maxAngle;
        uint32_t binDistance;
        uint32_t binOffset;
        uint8_t numberOfBins;
        
        // 400 steps per revolution, 16th microstepping
        const uint32_t numberOfStepsPerRevolution = 6400;

        void moveTo(uint32_t targetPos)
        {
            this->stepper.moveTo(targetPos);
            while(this->stepper.currentPosition() != targetPos) this->stepper.run();
        }
    
    public:
        Selector(uint8_t numberOfBins, uint16_t maxAngle, AccelStepper& stepper)
        {
            this->stepper = stepper;
            
            if (maxAngle > 0 && maxAngle < 360)
            {
                this->maxAngle = maxAngle;
            }
            else
            {
                this->maxAngle = 0;
            }
            
            
            if (numberOfBins != 0)
            {
                this->binDistance = int(this->numberOfStepsPerRevolution * maxAngle / (numberOfBins + 1));
            }
            else
            {
                this->binDistance = 0;
            }
            this->binOffset = int(this->binDistance / 2);
            this->numberOfBins = numberOfBins;
        }

        void begin(void)
        {
            this->stepper.setMinPulseWidth(1);
            this->stepper.setMaxSpeed(100000);
            this->stepper.setAcceleration(100000);    
        }

        void select(uint8_t bin)
        {
            // I think I want n bins equally distributed from 0 to maxAngle
            // Some n distance between bins, and n/2 distance from the bin to the origin
            // So a total of n sectors, with two of them n/2 offsets
            // Take max angle, divide by number of bins (starting from 0) and add offset
            uint32_t targetPos = this->binDistance * bin + this->binOffset;

            // Blocking function to move to target position
            this->moveTo(targetPos);
        }

        uint8_t getBinCount(void)
        {
            return this->numberOfBins;
        }

        void test(void)
        {
            this->moveTo(500);
            this->moveTo(0);
        }
};

#endif