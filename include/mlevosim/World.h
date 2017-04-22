#ifndef _WorldClass_
#define _WorldClass_

#include <map>
#include <cassert>
#include <string>

#include "mlevosim/Loggable.h"
#include "mlevosim/Tile.h"

class World : public Loggable
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

    void populate()
    {
        for(unsigned int i = 0; i < width; i++) {
            for(unsigned int ii = 0; ii < height; ii++) {
                this->tiles[i][ii] = new Tile();
            }
            this->log("Column #" + std::to_string(i+1) + " populated");
        }
    }

    Tile* tile(unsigned int x, unsigned int y)
    {
        return this->tiles[x][y];
    }
};

#endif //_WorldClass_