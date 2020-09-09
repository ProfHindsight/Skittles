/*
 * SERVO GLOBALS
 */
#include <Servo.h>
Servo servo
#define PIN_SERVO       3

/*
 * STEPPER GLOBALS
 */
#include <AccelStepper.h>
#define PIN_STEP        7
#define PIN_DIRECTION   6
// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER, PIN_STEP, PIN_DIRECTION); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

/*
 * COLOR SENSOR GLOBALS
 */
#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  /*
   * DEBUG SETUP
   */
  Serial.begin(9600);

  
  /*
   * SERVO SETUP
   */
  // Initialize the pin
  servo.attach(PIN_SERVO);
  // Set the servo motor angle
  servo.write(90);

  /*
   * STEPPER SETUP
   */
  // Set blocking pulse width in us
  stepper.setMinPulseWidth(1);
  stepper.setMaxSpeed(100);
  stepper.setAcceleration(20);
  stepper.moveTo(500);

  /*
   * COLOR SENSOR SETUP
   */
  tcs.begin()
}

void loop() {
   // If at the end of travel go to the other end
  if (stepper.distanceToGo() == 0)
    stepper.moveTo(-stepper.currentPosition());

  stepper.run();

}
