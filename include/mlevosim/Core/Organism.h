#ifndef _Organism_
#define _Organism_

#include <string>

#include "mlevosim/Composable/Loggable.h"
#include "mlevosim/Composable/Tickable.h"
#include "mlevosim/Composable/Positionable.h"

class Organism : public Loggable, public Tickable, public Positionable
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
        //this->log("Input Provided for organism #" + std::to_string(this->selfId));
    }

    void nextTick()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(0, 9);

        float random = dist(mt);
        Vector2i position = this->getPosition();

        if(dist(mt) > 4) {
            if(random > 6 && position.x > 1) {
                this->move({-1, 0});
            } else if(random > 3 && position.x < 47) {
                this->move({1, 0});
            }
        } else {
            random = dist(mt);
            if(random > 6 && position.y > 1) {
                this->move({0, -1});
            } else if(random > 3 && position.y < 26) {
                this->move({0, 1});
            }
        }
        //this->log("nextTick for organism #" + std::to_string(this->selfId));
    }
};
int Organism::id = 1;
#endif // _Organism_