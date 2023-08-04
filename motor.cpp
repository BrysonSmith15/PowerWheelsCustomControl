#include "motor.h"
#include <math.h>
#include <softPwm.h>
#include <tuple>
#include <wiringPi.h>

Motor::Motor(int in1, int in2, int ENA) {
	wiringPiSetupGpio();
  softPwmCreate(ENA, 0, 100);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  this->ENA = ENA;
  this->in1 = in1;
  this->in2 = in2;
  this->direction = true;
  this->ramper = Ramper{0.001, 0.05};
}

void Motor::setPower(float power) {
  // ramp power so that the motor does not jump to a value too fast
  // and potentially damage it
  power = this->ramper.get(power) * 100;
  if (power != 0) {
    // clamp power to -100<=p<=100
    if (power > 100) {
      power = 100;
    } else if (power < -100) {
      power = -100;
    }
    this->direction = power > 0;
    digitalWrite(this->in1, direction); 
    digitalWrite(this->in2, !direction);
    softPwmWrite(this->ENA, power);
  } else {
    // set float
    digitalWrite(this->in1, 1);
    digitalWrite(this->in2, 1);
    softPwmWrite(this->ENA, 0);
  }
}

Motor::~Motor() {
  softPwmWrite(this->ENA, 0);
  softPwmStop(this->ENA);
  digitalWrite(this->in1, 0);
  digitalWrite(this->in2, 0);
  pinMode(this->in1, INPUT);
  pinMode(this->in2, INPUT);
}
