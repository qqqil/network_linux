#include "clockutils.h"

ClockUtils::ClockUtils()
{
   
}


clock_t ClockUtils::start()
{
    clk = clock();
    return clk;
}


clock_t ClockUtils::end()
{
    clock_t end= clock();
    duration = end - clk;
    return end;
}
void ClockUtils::reset(){
    clk = clock();
    duration = 0;
}


clock_t ClockUtils::getDuration(){

    return duration;
}
