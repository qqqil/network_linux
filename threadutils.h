#ifndef THREADUTILS_H
#define THREADUTILS_H

#include <unistd.h>


class ThreadUtils
{
public:
    ThreadUtils();
    static void sleep(int num);
};

#endif // THREADUTILS_H
