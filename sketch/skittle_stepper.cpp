#include <AccelStepper.h>
#include "skittle_stepper.h"
extern AccelStepper stepper;

void stepper_init(void)
{
    /*
    * STEPPER SETUP
    */
    // Set blocking pulse width in us
    stepper.setMinPulseWidth(1);
    stepper.setMaxSpeed(100000);
    stepper.setAcceleration(100000);
    //  stepper.moveTo(5000);
}

void stepper_test(void)
{
    /*
    * STEPPER TESTING CODE
    */
    if (stepper.currentPosition() == 500)
    {
    stepper.moveTo(-stepper.currentPosition());
    }
    else
    {
    stepper.moveTo(500);
    }
}