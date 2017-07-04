#ifndef _Organism_
#define _Organism_

#include <string>

#include "mlevosim/Composable/Loggable.h"
#include "mlevosim/Composable/Tickable.h"
#include "mlevosim/Composable/Positionable.h"

class Organism : public Loggable, public Tickable, public Positionable
{
private:
    float energy = 50;
    bool dead = false;

    sf::Color color;
protected:

public:

    Organism()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(0, 255);

        this->setColor(sf::Color(dist(mt), dist(mt), dist(mt), 255));
    }

    Organism* clone()
    {
        Organism* org = new Organism();

        org->energy = this->energy;
        org->dead = this->dead;

        org->setColor(this->getColor());
        auto lP = this->getLastPosition();
        org->setPosition(this->getPosition());
        org->setLastPosition(lP);
        return org;
    }

    bool isAlive()
    {
        return !this->dead;
    }

    void setColor(sf::Color color)
    {
        this->color = color;
    }

    sf::Color getColor()
    {
        return this->color;
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
                if(random > 6 && position.x > 0) {
                    this->move({-1, 0});
                } else if(random > 3 && position.x < WORLD_WIDTH-1) {
                    this->move({1, 0});
                }
            }
            this->energy -= 15;
        } else if(randomD > 2) {
            if(this->energy > 15) {
                if(random > 6 && position.y > 0) {
                    this->move({0, -1});
                } else if(random > 3 && position.y < WORLD_HEIGHT-1) {
                    this->move({0, 1});
                }
            }
            this->energy -= 15;
        }

        if(position.x == this->getPosition().x && this->getPosition().y == position.y) {
            this->setLastPosition(this->getPosition());
        }
        //this->log("nextTick for organism #" + std::to_string(this->selfId));
    }
};
#endif // _Organism_
