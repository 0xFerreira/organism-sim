#ifndef _Organism_
#define _Organism_

#include <string>

#include "mlevosim/Loggable.h"
#include "mlevosim/Tickable.h"

class Organism : public Loggable, public Tickable
{
private:
    static int id;
    unsigned int selfId = 0;

protected:

public:

    Organism()
    {
        this->selfId = Organism::id;
        Organism::id++;
    }

    Organism* clone()
    {
        return new Organism(*this);
    }

    void provideInput()
    {
        this->log("Input Provided for organism #" + std::to_string(this->selfId));
    }

    void nextTick()
    {
        this->log("nextTick for organism #" + std::to_string(this->selfId));
    }
};
int Organism::id = 1;
#endif // _Organism_