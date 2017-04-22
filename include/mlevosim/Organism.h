#ifndef _Organism_
#define _Organism_

#include <functional>
#include <string>

#include "Loggable.h"

class Organism : public Loggable
{
private:
    int id = 0;

protected:

public:

    Organism(int id)
    {
        this->id = id;
    }

    void provideInput()
    {
        this->log("Input Provided for organism #" + std::to_string(this->id));
    }

    void tick()
    {

    }
};
#endif // _Organism_