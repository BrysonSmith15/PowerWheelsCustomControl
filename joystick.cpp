#include "joystick.h"

#include <fcntl.h>
#include <iostream>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

#include <vector>

using namespace std;

Joystick::Joystick(const char *devicePath, float deadband) {
  this->fd = open(devicePath, O_RDONLY | O_NONBLOCK);
  if (this->fd < 0) {
    cout << "Improper joystick path given, exiting" << endl;
    exit(1);
  }
  this->joyY = 0;
  this->joyX = 0;
  this->joyRY = 0;
  this->joyRX = 0;
  this->deadband = deadband;
}

void Joystick::getVals() {
  struct input_event ev;
  ssize_t bytesRead = read(this->fd, &ev, sizeof(ev));
  if (bytesRead == sizeof(ev)) {
    if (ev.type == EV_ABS) {
      if (ev.code == ABS_Y) {
        // left joystick Y
        this->joyY =
            roundHundreths((float)ev.value / -32768.0); // this is the value to
                                                        // make 1.0 forward
        if (-this->deadband < this->joyY && this->joyY < this->deadband) {
          this->joyY = 0.0;
        }
      } else if (ev.code == ABS_X) {
        // left joystick Y
        this->joyX =
            roundHundreths((float)ev.value / -32768.0); // this is the value to
                                                        // make 1.0 forward
        if (-this->deadband < this->joyX && this->joyX < this->deadband) {
          this->joyX = 0.0;
        }
      } else if (ev.code == ABS_RY) {
            this->joyRY = 
                roundHundreths((float)ev.value / -32768.0);
            if (-this->deadband < this->joyRY && this->joyRY < this->deadband) {
                    this->joyRY = 0.0;
                }
        } else if (ev.code == ABS_RX) {
            this->joyRX = 
                roundHundreths((float)ev.value / -32768.0);
            if (-this->deadband < this->joyRX && this->joyRX < this->deadband) {
                    this->joyRX = 0.0;
            }
        }
    } else if (ev.type == EV_KEY) {
      if (ev.code == BTN_A) {
        this->aPressed = ev.value;
      } else if (ev.code == 305) {
        this->bPressed = ev.value;
      } else if (ev.code == 307) {
        this->xPressed = ev.value;
      } else if (ev.code == 308) {
        this->yPressed = ev.value;
      } else if (ev.code == 311) {
        this->rbPressed = ev.value;
      } else if (ev.code == 310) {
        this->lbPressed = ev.value;
      } else if (ev.code == 315) {
        this->startPressed = ev.value;
      } else if (ev.code == 314) {
        this->selectPressed = ev.value;
      } else if (ev.code == 317) {
        this->leftPressed = ev.value;
      } else if (ev.code == 318) {
        this->rightPressed = ev.value;
      } else if (ev.code == 316) {
        this->xboxPressed = ev.value;
      } else {
        std::cout << ev.code << "\n";
      }
    }
  }
}

float Joystick::roundHundreths(float x) { return floor(x * 100 + 0.5) / 100; }

Joystick::~Joystick() { close(this->fd); }
