#ifndef _TileClass_
#define _TileClass_

#include "mlevosim/Tickable.h"
class Tile : public Tickable
{
private:
protected:
    unsigned int energy = 50;
    unsigned int minEnergy = 0;
    unsigned int maxEnergy = 100;
    unsigned int energyRegen = 1;

public:
    Tile(unsigned int energy = 50,
         unsigned int minEnergy = 0,
         unsigned int maxEnergy = 100,
         unsigned int energyRegen = 1)
    {
        this->energy = energy;
        this->minEnergy = minEnergy;
        this->maxEnergy = maxEnergy;
        this->energyRegen = energyRegen;
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