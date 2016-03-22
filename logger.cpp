#include "logger.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>


void Logger::log(string msg)
{
    std::cout<<msg<<std::endl;
}

void Logger::info(string msg)
{
    log("INFO:"+msg);
}

void Logger::debug(string msg)
{
    log("DEBUG:"+msg);
}

void Logger::error(string msg)
{
    log("ERROR:"+msg+"-"+strerror(errno));
}
