#include <Servo.h>
#include "skittle_servo.h"
#include <Arduino.h>
extern Servo servo;

/*
 * SERVO FUNCTIONS
 */
void servo_open(void)
{
  servo.write(MIN_SERVO_POS);
}

void servo_close(void)
{
  servo.write(MAX_SERVO_POS);
}

void servo_drop_skittle(void)
{
  servo_open();
  delay(SERVO_DELAY);
  servo_close();
}

void servo_init(void)
{
    // Initialize the pin
    servo.attach(PIN_SERVO);
    // Set the servo motor angle
    servo.write(MAX_SERVO_POS);
}

void servo_test(void)
{
    servo.write(MIN_SERVO_POS);
    delay(SERVO_DELAY);
    servo.write(MAX_SERVO_POS);
}