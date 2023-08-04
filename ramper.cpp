#include "ramper.h"
#include <math.h>

Ramper::Ramper() {
  this->maxAccel = 0.05;
  this->maxDecel = 0.05;
}

Ramper::Ramper(float maxAcceleration) {
  this->maxAccel = maxAcceleration;
  this->maxDecel = 0.05;
}

Ramper::Ramper(float maxAcceleration, float maxDeceleration) {
  this->maxAccel = maxAcceleration;
  this->maxDecel = maxDeceleration;
}

float Ramper::get(float curr) {
  if (curr < -1) {
    curr = -1; 
  } else if (curr > 1) {
    curr = 1;
  }

	float val = std::pow(curr, 3);
	float dif = val - this->prev;
	int dirMult = dif > 0 ? 1 : -1;
	// are we accelerating?
	if (std::abs(val) > std::abs(this->prev)) {
		if (std::abs(dif) > this->maxAccel) {
				val = this->prev + (this->maxAccel * dirMult);
			}
	} else if (std::abs(val) < std::abs(this->prev)) {
			if (std::abs(dif) > this->maxDecel) {
			val = this->prev + (this->maxDecel * dirMult);
		}
	}
	this->prev = val;
	return val;
}
