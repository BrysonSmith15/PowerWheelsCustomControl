#include "joystick.h"
#include "motor.h"
#include <signal.h>
#include <iostream>
#include <unistd.h>

Motor *lMotor = new Motor{17, 27, 22};
Motor *rMotor = new Motor{5, 6, 13};

void cleanup(int param) {
  if (param == SIGINT) {
    delete lMotor;
    delete rMotor;
    exit(0);
  }
}

int main() {
  signal(SIGINT, cleanup);
  Joystick myJoystick{
      "/dev/input/event2", 0.1};
  while (true) {
    myJoystick.getVals();
    lMotor->setPower(myJoystick.joyY);
    rMotor->setPower(myJoystick.joyRY);
    usleep(10000);
  }
  return 0;
}
