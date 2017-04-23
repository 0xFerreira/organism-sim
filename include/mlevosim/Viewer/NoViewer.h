#ifndef _NoViewerClass_
#define _NoViewerClass_

#include "mlevosim/Viewer/Viewer.h"

class NoViewer : public  Viewer
{
private:
protected:
public:
    void draw(TimeTravel::State* state)
    {

    }
};

#endif //_NoViewerClass_