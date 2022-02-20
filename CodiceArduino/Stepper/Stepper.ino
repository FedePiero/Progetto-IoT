#include <Stepper.h>

int step_mode = 4;

int stepsPerRevolution = 2048 * (step_mode/4) ; 
int mysteps = 1 * stepsPerRevolution;

Stepper myStepper(stepsPerRevolution,8,9,10,11,step_mode);

void setup() {
  myStepper.setSpeed(60);
  Serial.begin(9600);
}

void loop() {
  myStepper.step(-mysteps);
  delay(500);

  myStepper.step(mysteps);
  delay(500);
}
