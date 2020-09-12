/*
 * SERVO GLOBALS
 */
#include <Servo.h>
Servo servo;
#define PIN_SERVO       3
#define MIN_SERVO_POS   32
#define MAX_SERVO_POS   120
#define SERVO_DELAY     150

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


void setup() {
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
  servo.write(90);

  /*
   * STEPPER SETUP
   */
  // Set blocking pulse width in us
  stepper.setMinPulseWidth(1);
  stepper.setMaxSpeed(100000);
  stepper.setAcceleration(100000);
//  stepper.moveTo(5000);

  /*
   * COLOR SENSOR SETUP
   */
  tcs.begin();
}

void loop() {
  if(Serial.available())
  {
    char c = Serial.read();
    switch(c)
    {
      case 's':
      
        /*
         * STEPPER TESTING CODE
         */
          if(stepper.currentPosition() == 500)
          {
            stepper.moveTo(-stepper.currentPosition());
          }
          else
          {
            stepper.moveTo(500);
          }
        
      break;
      case 'c':
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
      break;
      case 'e':
      
        /*
         * SERVO TESTING CODE
         */
        servo_drop_skittle();


      break;
    }
    
  }
  
  // This function must be called as often as possible and will step the motor once per call.
  stepper.run();
}
