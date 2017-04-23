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

    unsigned int x = 0;
    unsigned int y = 0;

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
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(0, 9);
        float random = dist(mt);
        if(random > 6 && this->x > 1) {
            this->x += -1;
        } else if(random > 3 &&this->x < 47) {
            this->x += 1;
        }
        random = dist(mt);
        if(random > 6 && this->y > 1) {
            this->y += -1;
        } else if(random > 3 && this->y < 26) {
            this->y += 1;
        }
        this->log("nextTick for organism #" + std::to_string(this->selfId));
    }
};
int Organism::id = 1;
#endif // _Organism_