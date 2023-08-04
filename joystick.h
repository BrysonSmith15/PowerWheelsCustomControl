#pragma once

struct Joystick {
public:
  float joyY;
  float joyX;
  float joyRY;
  float joyRX;
  bool aPressed = false;
  bool xPressed = false;
  bool bPressed = false;
  bool yPressed = false;
  bool rbPressed = false;
  bool lbPressed = false;
  bool startPressed = false;
  bool selectPressed = false;
  bool leftPressed = false;
  bool rightPressed = false;
  bool xboxPressed = false;
  Joystick(const char *devicePath, float deadband);
  ~Joystick();
  void getVals();

private:
  int fd;
  float deadband;
  float roundHundreths(float x);
};
