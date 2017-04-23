#ifndef _TickableClass_
#define _TickableClass_

class Tickable
{
private:

protected:
    Tickable() {}
    ~Tickable() {}

public:
    virtual void nextTick() = 0;

};

#endif //_TickableClass_