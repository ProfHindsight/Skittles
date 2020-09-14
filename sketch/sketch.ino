#include <Servo.h>
#include "skittle_servo.h"
Servo servo;

#include <AccelStepper.h>
#include "skittle_stepper.h"
AccelStepper stepper(AccelStepper::DRIVER, PIN_STEP, PIN_DIRECTION); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

/*
 * COLOR SENSOR GLOBALS
 */
#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

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



void setup()
{
  /*
   * DEBUG SETUP
   */
  Serial.begin(9600);
  Serial.println("R, G, B");

  servo_init();
  stepper_init();

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
      Serial.println("Testing Stepper");
      stepper_test();
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
      Serial.println("Testing Servo");
      servo_test();
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
