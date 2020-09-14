/*
 * SERVO GLOBALS
 */
#include <Servo.h>
Servo servo;
#define PIN_SERVO 3
#define MIN_SERVO_POS 32
#define MAX_SERVO_POS 120
#define SERVO_DELAY 150

/*
 * STEPPER GLOBALS
 */
#include <AccelStepper.h>
#define PIN_STEP 7
#define PIN_DIRECTION 6
// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER, PIN_STEP, PIN_DIRECTION); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

/*
 * COLOR SENSOR GLOBALS
 */
#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
/*
    Red Green Blue
Red 155 212 184
Green 146 232 187
Purple  137 209 182
Orange  187 224 189
Yellow  198 255 195
*/

typedef enum colors
{
  red = 0,
  green = 1,
  purple = 2,
  orange = 3,
  yellow = 4,
  unknown = 5
} colors_t;

typedef struct color
{
  colors_t color;
  uint8_t r;
  uint8_t g;
  uint8_t b;
} color_t;

color_t color_table[] =
    {
        {red, 155, 212, 184},
        {green, 146, 232, 187},
        {purple, 137, 209, 182},
        {orange, 187, 224, 189},
        {yellow, 198, 255, 195},
        {unknown, 0, 0, 0}};

int indexofSmallestElement(double arr[], int len)
{
  int index = 0;

  for (int i = 1; i < len; i++)
  {
    if (arr[i] < arr[index])
      index = i;
  }
  return index;
}

colors_t color_from(int red, int green, int blue)
{
  float color_diff;
  float minimum_diff = 1000;
  color_t matching_color = color_table[5];

  for (uint8_t i = 0; i < 5; i++)
  {
    //    color_diff =
    //      abs(red - color_table[i].r) +
    //      abs(green - color_table[i].g) +
    //      abs(blue - color_table[i].b);

    color_diff = sqrt(
        abs(red - color_table[i].r) * abs(red - color_table[i].r) +
        abs(green - color_table[i].g) * abs(green - color_table[i].g) +
        abs(blue - color_table[i].b) * abs(blue - color_table[i].b));

    if (color_diff < minimum_diff)
    {
      minimum_diff = color_diff;
      matching_color = color_table[i];
    }
  }
  return matching_color.color;
}

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
   * STEPPER SETUP
   */
  // Set blocking pulse width in us
  stepper.setMinPulseWidth(1);
  stepper.setMaxSpeed(100000);
  stepper.setAcceleration(10000);
  //  stepper.moveTo(5000);

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

      colors_t result = color_from(int(red), int(green), int(blue));
      Serial.print("Color Guess: ");
      Serial.println(result);
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
