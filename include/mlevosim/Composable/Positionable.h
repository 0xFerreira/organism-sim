#ifndef _PositionableClass_
#define _PositionableClass_

#include "mlevosim/Vector2i.h"

class Positionable
{
private:
    Vector2i position;

protected:
    Positionable() {};
    ~Positionable() {}

public:
    void setPosition(const Vector2i& position)
    {
        this->position.x = position.x;
        this->position.y = position.y;
    }

    void move(const Vector2i& positionDelta)
    {
        this->position.x += positionDelta.x;
        this->position.y += positionDelta.y;
    }

    Vector2i getPosition()
    {
        return this->position;
    }

};
#endif // _PositionableClass_