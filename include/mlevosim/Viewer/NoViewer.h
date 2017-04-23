#ifndef _NoViewerClass_
#define _NoViewerClass_

#include "mlevosim/Viewer/Viewer.h"

class NoViewer : public  Viewer
{
private:
protected:
public:
    NoViewer()
    {
    }

    bool shouldTick()
    {
        return true;
    }

    bool fowardInTime()
    {
        return true;
    }

    void ticked()
    {

    }

    bool isRunning()
    {
        return true;
    }

    void processInput()
    {

    }

    void draw(SpaceTime::State* state)
    {
    }
};

#endif //_NoViewerClass_