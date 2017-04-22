#ifndef _LoggableClass_
#define _LoggableClass_

#include <functional>
#include <iostream>

class Loggable
{
private:
    std::function<void(const std::string&)> logCallback = nullptr;
protected:
    virtual ~Loggable() {}

    void log(const std::string& info)
    {
        if(this->logCallback != nullptr) {
            this->logCallback(info);
        } else {
            std::cout << info << std::endl;
        }
    }
public:
    void registerLogCallback(std::function<void(const std::string&)> lambda)
    {
        this->logCallback = lambda;
    }
};
#endif // _LoggableClass_