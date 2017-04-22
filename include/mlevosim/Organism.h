#ifndef _Organism_
#define _Organism_

#include <string>

#include "mlevosim/Loggable.h"

class Organism : public Loggable
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

    void provideInput()
    {
        this->log("Input Provided for organism #" + std::to_string(this->selfId));
    }

    void tick()
    {

    }
};
int Organism::id = 1;
#endif // _Organism_