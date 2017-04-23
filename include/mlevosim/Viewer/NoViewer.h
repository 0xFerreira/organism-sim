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

    void run()
    {
        while(true) {
            this->spaceTime->foward();
        }

    }
};

#endif //_NoViewerClass_