#ifndef _WorldClass_
#define _WorldClass_

#include <map>
#include <cassert>
#include <string>

#include "mlevosim/Composable/Loggable.h"
#include "mlevosim/Composable/Tickable.h"

#include "mlevosim/Tile.h"

class World : public Loggable, public Tickable
{
private:
protected:
    std::map<unsigned int, std::map<unsigned int, Tile*>> tiles;
    unsigned int width = 1;
    unsigned int height = 1;

public:
    World(unsigned int width, unsigned int height)
    {
        assert(width > 0);
        assert(height > 0);

        this->width = width;
        this->height = height;
    }

    World* clone()
    {
        World* world = new World(*this);

        for(unsigned int i = 0; i < this->width; i++) {
            for(unsigned int ii = 0; ii < this->height; ii++) {
                if(this->tiles.count(i) == 1) {
                    if(this->tiles[i].count(ii) == 1) {
                        world->tiles[i][ii] = new Tile(*this->tiles[i][ii]);
                    }
                }
            }
        }

        return world;
    }

    void terraform()
    {
        for(unsigned int i = 0; i < this->width; i++) {
            for(unsigned int ii = 0; ii < this->height; ii++) {
                this->tiles[i][ii] = new Tile();
            }
            this->log("Terraform column #" + std::to_string(i+1) + "");
        }
    }

    Tile* tile(unsigned int x, unsigned int y)
    {
        if(this->tiles.count(x) == 1) {
            if(this->tiles[x].count(y) == 1) {
                return this->tiles[x][y];
            }
        }

        return nullptr;
    }

    const std::map<unsigned int, std::map<unsigned int, Tile*>>& getTiles()
    {
        return this->tiles;
    }

    void nextTick()
    {
        for(unsigned int i = 0; i < this->width; i++) {
            for(unsigned int ii = 0; ii < this->height; ii++) {
                this->tiles[i][ii]->nextTick();
            }
        }
    }
};

#endif //_WorldClass_