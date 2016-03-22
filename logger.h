#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>

using std::string;

class Logger{
public:
    static void log(string msg);
    static void info(string msg);
    static void debug(string msg);
    static void error(string msg);
};
#endif // LOGGER_H
