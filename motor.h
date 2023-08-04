#include "ramper.h"
#include <chrono>

class Motor {
public:
  Motor(int in1, int in2, int ENA);
  void setPower(float power);
  ~Motor();

private:
  // forward = true
  bool direction;

  Ramper ramper;

  int in1;
  int in2;
  int ENA;
	std::chrono::high_resolution_clock::time_point lastReversed = std::chrono::high_resolution_clock::now();
};
