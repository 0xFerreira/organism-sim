#ifndef _LoggableClass_
#define _LoggableClass_

class Loggable
{
private:
    std::function<void(const std::string&)> logCallback = nullptr;
protected:
    void log(const std::string& info)
    {
        this->logCallback(info);
    }
public:
    void registerLogCallback(std::function<void(const std::string&)> lambda)
    {
        this->logCallback = lambda;
    }
};
#endif // _LoggableClass_