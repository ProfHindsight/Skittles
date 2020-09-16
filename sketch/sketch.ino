#include <Servo.h>
Servo servo;
#define PIN_SERVO 3
#define MIN_SERVO_POS 32
#define MAX_SERVO_POS 120
#define SERVO_DELAY 150




/*
 * COLOR SENSOR GLOBALS
 */
#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup()
{
  /*
   * DEBUG SETUP
   */
  Serial.begin(9600);
  Serial.println("R, G, B");

  /*
   * SERVO SETUP
   */
  // Initialize the pin
  servo.attach(PIN_SERVO);
  // Set the servo motor angle
  servo.write(MAX_SERVO_POS);

  /*
   * COLOR SENSOR SETUP
   */
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
    else if (c == 'c')
    {
      /*
      * COLOR SENSOR TESTING CODE
      */
      float red, green, blue;
      tcs.getRGB(&red, &green, &blue);
      Serial.print(int(red));
      Serial.print(',');
      Serial.print(int(green));
      Serial.print(',');
      Serial.println(int(blue));
    }
    else if (c == 'e')
    {
      /*
      * SERVO TESTING CODE
      */
      Serial.println("Dropping Skittle");
      servo.write(MIN_SERVO_POS);
      delay(SERVO_DELAY);
      servo.write(MAX_SERVO_POS);
    }
    else if (c == '\n');
    else if (c == '\r');
    else
    {
      Serial.println(c);
    }
  }

  // This function must be called as often as possible and will step the motor once per call.
  stepper.run();
}
