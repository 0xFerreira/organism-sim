#ifndef _SpaceTimeClass_
#define _SpaceTimeClass_

#include <vector>
#include <map>

#include "mlevosim/Composable/Loggable.h"

#include "mlevosim/Core/World.h"
#include "mlevosim/Core/Organism.h"

class SpaceTime : public Loggable
{
public:
    struct State
    {
        World* world = nullptr;
        std::vector<Organism*> organisms;
    };
private:

protected:
    std::map<unsigned int, State> states;
    unsigned int currentState = 0;
    unsigned int maxState = 0;

    void calculateNextState()
    {
        World* newWorld = this->states[this->currentState].world->clone();

        std::vector<Organism*> newOrganisms;
        for(Organism* org : this->states[this->currentState].organisms) {
            newOrganisms.push_back(org->clone());
        }

        newWorld->nextTick();

        for(Organism* org : newOrganisms) {
            if(org->isAlive()) {
                org->nextTick();
                
                unsigned int tileEnergy = newWorld->tile(org->getPosition().x, org->getPosition().y)->getEnergy();
                newWorld->tile(org->getPosition().x, org->getPosition().y)->setEnergy(tileEnergy*0.75);
                org->receiveEnergy(tileEnergy*0.25);

                if(org->getEnergy() >= 100) {
                    org->setEnergy(50);
                    newOrganisms.push_back(org->clone());
                }
            }
        }


        this->states[this->currentState+1].world = newWorld;
        this->states[this->currentState+1].organisms = newOrganisms;

        this->currentState++;

        this->maxState = this->currentState;

        this->log("Calculated tick #" + std::to_string(this->currentState));
    }

public:
    SpaceTime()
    {

    }

    State* now()
    {
        return &this->states[this->currentState];
    }

    State* past()
    {
        if((int)this->currentState-1 >= 0) {
            return &this->states[this->currentState-1];
        }
        return this->now();
    }
    //Very Naive implementation
    int usedMemory()
    {
        float worldsSize = sizeof(World)*this->currentState;
        float tilesSize  = sizeof(Tile)*48*27*this->currentState;
        float organismsSize = sizeof(Organism)*this->now()->organisms.size()*this->currentState;
        float totalUsed = (organismsSize+tilesSize+worldsSize)/1000000.0f;

        return totalUsed;
    }

    SpaceTime* backward(unsigned int timeUnit = 1)
    {
        if((int)this->currentState - (int)timeUnit >= 0) {
            this->currentState -= timeUnit;
        } else {
            this->currentState = 0;
        }
        this->log("Set to tick #" + std::to_string(this->currentState));
        return this;
    }

    SpaceTime* foward(unsigned int timeUnit = 1)
    {
        if(this->currentState + timeUnit <= this->maxState) {
            this->currentState += timeUnit;
        } else {
            this->currentState = this->maxState;
            this->calculateNextState();
        }
        this->log("Set to tick #" + std::to_string(this->currentState));
        return this;
    }

    SpaceTime* registerWorld(World* world)
    {
        this->now()->world = world;
        return this;
    }

    SpaceTime* registerOrganisms(const std::vector<Organism*>& organisms)
    {
        this->now()->organisms = organisms;
        return this;
    }
};

#endif //_SpaceTimeClass_