#ifndef _LoggerClass_
#define _LoggerClass_

#include <iostream>
#include <string>

class Logger
{
private:
protected:
    static int logCount;
public:
    static void write(const std::string& info)
    {
        std::cout << "[#" << Logger::logCount++ << "] " << info << std::endl;
    }
};
int Logger::logCount = 0;
#endif // _LoggerClass_