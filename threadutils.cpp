#include "threadutils.h"

ThreadUtils::ThreadUtils()
{
}

void ThreadUtils::sleep(int num)
{
    usleep(num * 1000);//sleep for num milliseconds
}
