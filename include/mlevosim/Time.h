#ifndef _TimeClass_
#define _TimeClass_

#include <chrono>

class Time
{
private:
protected:
public:
    static unsigned long long getCurrentTime()
    {
        return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
    }
};

#endif //_TimeClass_