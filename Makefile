CC=g++
CFLAGS= -std=c++11 -Wall -pedantic -g
SOURCES= main.cpp motor.cpp joystick.cpp ramper.cpp 
DEPS= motor.h joystick.h ramper.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=exec

all: $(EXECUTABLE)
    echo "Make has finished."

$(EXECUTABLE): $(OBJECTS)
    $(CC)  $(OBJECTS) -o $@

.cpp.o:
    $(CC) $(CFLAGS) -c $*.cpp

clean: 
    $(RM) *.o *~ $(EXECUTABLE),
