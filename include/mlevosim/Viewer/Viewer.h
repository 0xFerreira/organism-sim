#ifndef _ViewerClass_
#define _ViewerClass_

#include "mlevosim/Core/TimeTravel.h"

class Viewer
{
private:
protected:
    Viewer() {}
    ~Viewer() {}
public:
    virtual void draw(TimeTravel::State* state) = 0;
};

#endif //_ViewerClass_