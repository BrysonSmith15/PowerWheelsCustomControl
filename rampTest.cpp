#include "ramper.h"
#include "joystick.h"
#include <iostream>
#include <unistd.h>

int main() {
    Joystick myJoystick{"/dev/input/event0", 0.1};
    Ramper myRamper{0.01, 0.01};
    while (true) {
        myJoystick.getVals();
        std::cout << "R " << myRamper.get(myJoystick.joyY) * 100 << " P " << myJoystick.joyY * 100 << '\n';
				usleep(10000);
    }
}
