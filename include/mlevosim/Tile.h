#ifndef _TileClass_
#define _TileClass_

#include <random>

#include "mlevosim/Tickable.h"

class Tile : public Tickable
{
private:
protected:
    unsigned int energy = 50;
    unsigned int minEnergy = 0;
    unsigned int maxEnergy = 100;
    unsigned int energyRegen = 3;

public:
    Tile(unsigned int energy = 50,
         unsigned int minEnergy = 0,
         unsigned int maxEnergy = 100,
         unsigned int energyRegen = 3)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(0, 15);

        this->energy = energy+dist(mt);
        this->minEnergy = minEnergy+dist(mt)*5;
        this->maxEnergy = maxEnergy+dist(mt)*10;
        this->energyRegen = energyRegen+(dist(mt)-2);
    }

    unsigned int getEnergy()                    {return this->energy;}
    void         setEnergy(unsigned int energy) {this->energy = energy;}

    unsigned int getMinEnergy()                       {return this->minEnergy;}
    void         setMinEnergy(unsigned int minEnergy) {this->minEnergy = minEnergy;}

    unsigned int getMaxEnergy()                       {return this->maxEnergy;}
    void         setMaxEnergy(unsigned int maxEnergy) {this->maxEnergy = maxEnergy;}

    unsigned int getEnergyRegen()                         {return this->energyRegen;}
    void         setEnergyRegen(unsigned int energyRegen) {this->energyRegen = energyRegen;}

    void nextTick()
    {
        if(this->energy < this->maxEnergy) {
            if(this->energy + this->energyRegen > this->maxEnergy) {
                this->energy = this->maxEnergy;
            } else {
                this->energy += this->energyRegen;
            }
        }
    }
};

#endif //_TileClass_