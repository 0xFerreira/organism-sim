#ifndef _ViewerClass_
#define _ViewerClass_

#include "mlevosim/Core/SpaceTime.h"

class Viewer
{
private:
protected:
    SpaceTime* spaceTime = nullptr;

    Viewer() {}
    ~Viewer() {}
public:
    virtual void run() = 0;

    void registerSpaceTime(SpaceTime* spaceTime)
    {
        this->spaceTime = spaceTime;
    }
};

#endif //_ViewerClass_