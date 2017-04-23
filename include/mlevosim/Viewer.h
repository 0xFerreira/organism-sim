#ifndef _ViewerClass_
#define _ViewerClass_

#include "mlevosim/SpaceTime.h"

class Viewer
{
private:
protected:
    ~Viewer() {}
public:
    virtual void draw(SpaceTime::State* state) = 0;
    virtual bool isRunning() = 0;
};

#endif //_ViewerClass_