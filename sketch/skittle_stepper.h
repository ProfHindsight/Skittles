// Define a stepper and the pins it will use
#define PIN_STEP 7
#define PIN_DIRECTION 6

#define STEPPER_MAX_STEPS

void stepper_init(void);
void stepper_test(void);

void servo_open(void);
void servo_close(void);
void servo_drop_skittle(void);