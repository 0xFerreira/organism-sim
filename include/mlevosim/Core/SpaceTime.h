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
        for(Organism* org1 : this->states[this->currentState].organisms) {
            newOrganisms.push_back(org1->clone());
        }

        newWorld->nextTick();   
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(0.90f, 1.0f);

        std::uniform_real_distribution<float> mDist(0, 1);
        std::vector<Organism*> newClonedOrganisms;
        for(Organism* org : newOrganisms) {
            if(org->isAlive()) {
                org->nextTick();
                
                unsigned int tileEnergy = newWorld->tile(org->getPosition().x, org->getPosition().y)->getEnergy();
                newWorld->tile(org->getPosition().x, org->getPosition().y)->setEnergy(tileEnergy*0.75);
                org->receiveEnergy(tileEnergy*0.25);

                if(org->getEnergy() >= 100) {
                    org->setEnergy(50);
                    auto orgClone = org->clone();
                    orgClone->setColor(sf::Color(org->getColor().r*((dist(mt) > 0.95) ? -dist(mt) : dist(mt)), org->getColor().g*((dist(mt) > 0.95) ? -dist(mt) : dist(mt)), org->getColor().b*((dist(mt) > 0.95) ? -dist(mt) : dist(mt)), org->getColor().a));
                    orgClone->move({static_cast<int>(mDist(mt)), static_cast<int>(mDist(mt))});
                    newClonedOrganisms.push_back(orgClone);
                }
            }
        }

        std::vector<Organism*> mergedOrganisms;
        mergedOrganisms.reserve( newOrganisms.size() + newClonedOrganisms.size() );
        mergedOrganisms.insert( mergedOrganisms.end(), newOrganisms.begin(), newOrganisms.end() );
        mergedOrganisms.insert( mergedOrganisms.end(), newClonedOrganisms.begin(),newClonedOrganisms.end() );

        this->states[this->currentState+1].world = newWorld;
        this->states[this->currentState+1].organisms = mergedOrganisms;

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