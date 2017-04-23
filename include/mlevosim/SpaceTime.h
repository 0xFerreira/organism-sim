#ifndef _SpaceTimeClass_
#define _SpaceTimeClass_

#include <vector>
#include <map>

#include "mlevosim/Tickable.h"
#include "mlevosim/Loggable.h"

#include "mlevosim/World.h"
#include "mlevosim/Organism.h"

class SpaceTime : public Loggable, public Tickable
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
public:
    SpaceTime()
    {

    }

    State* now()
    {
        return &this->states[this->currentState];
    }
    void registerWorld(World* world)
    {
        this->now()->world = world;
    }

    void registerOrganisms(const std::vector<Organism*>& organisms)
    {
        this->now()->organisms = organisms;
    }

    void nextTick()
    {
        World* newWorld = this->states[this->currentState].world->clone();

        std::vector<Organism*> newOrganisms;
        for(Organism* org : this->states[this->currentState].organisms) {
            newOrganisms.push_back(org->clone());
        }

        newWorld->nextTick();

        for(Organism* org : newOrganisms) {
            org->nextTick();
        }

        this->states[this->currentState+1].world = newWorld;
        this->states[this->currentState+1].organisms = newOrganisms;

        this->currentState++;
    }

};

#endif //_SpaceTimeClass_