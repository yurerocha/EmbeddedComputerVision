#ifndef UTIL_H
#define UTIL_H

#include <string>

#define DEBUGGING_LEVEL 1

struct Coordinates {
    double x;
    double y;
};

enum States {doNothing, calibrate, detect, leave};

void logAndAbort(const std::string message);

#endif