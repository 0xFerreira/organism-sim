#ifndef _TileClass_
#define _TileClass_

class Tile
{
private:
protected:
    unsigned int energy = 100;
    unsigned int minEnergy = 0;
    unsigned int maxEnergy = 100;
    unsigned int energyRegen = 1;

public:
    Tile(unsigned int energy = 100,
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
};

#endif //_TileClass_