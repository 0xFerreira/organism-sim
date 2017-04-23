#ifndef _ViewerClass_
#define _ViewerClass_

#include "mlevosim/Core/SpaceTime.h"

class Viewer
{
private:
protected:
    Viewer() {}
    ~Viewer() {}
public:
    virtual void draw(SpaceTime::State* state, float deltaTime) = 0;
    virtual bool isRunning() = 0;
    virtual void processInput() = 0;
    virtual bool shouldTick() = 0;
    virtual void ticked() = 0;
    virtual bool fowardInTime() = 0;
};

#endif //_ViewerClass_