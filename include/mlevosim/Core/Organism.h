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
    float energy = 50;
    bool dead = false;
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

    bool isAlive()
    {
        return !this->dead;
    }
    
    float getEnergy()
    {
        return this->energy;
    }

    void setEnergy(float energy)
    {
        this->energy = energy;
    }

    void provideInput()
    {
        //this->log("Input Provided for organism #" + std::to_string(this->selfId));
    }

    void receiveEnergy(float energy)
    {
        this->energy += energy;
    }

    void nextTick()
    {
        if(this->energy <= 0) {
            this->dead = true;
            return;
        }

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(0, 9);

        float random = dist(mt);
        Vector2i position = this->getPosition();

        float randomD = dist(mt);
        if(randomD > 6) {
            if(this->energy > 15) {
                if(random > 6 && position.x > 1) {
                    this->move({-1, 0});
                } else if(random > 3 && position.x < 47) {
                    this->move({1, 0});
                }
            }
            this->energy -= 15;
        } else if(randomD > 2) {
            if(this->energy > 15) {
                if(random > 6 && position.y > 1) {
                    this->move({0, -1});
                } else if(random > 3 && position.y < 26) {
                    this->move({0, 1});
                }
            }
            this->energy -= 15;
        }
        //this->log("nextTick for organism #" + std::to_string(this->selfId));
    }
};
int Organism::id = 1;
#endif // _Organism_