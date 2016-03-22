#ifndef CLOCKUTILS_H
#define CLOCKUTILS_H

#include <time.h>

class ClockUtils
{
public:
    ClockUtils();
    clock_t start();
    clock_t end();
    clock_t getDuration();
    void reset();
private:
    clock_t clk;
    clock_t duration;
};

#endif // CLOCKUTILS_H
