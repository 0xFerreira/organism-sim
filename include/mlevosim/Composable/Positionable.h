#ifndef _PositionableClass_
#define _PositionableClass_

#include "mlevosim/Vector2i.h"

class Positionable
{
private:
    Vector2i position;
    Vector2i lastPosition;
    bool transitionDone = false;
protected:
    Positionable() {};
    ~Positionable() {}

public:

    bool isTransitionDone()
    {
        return this->transitionDone;
    }

    void setTransitionDone()
    {
        this->transitionDone = true;
    }

    void setPosition(const Vector2i& position)
    {
        this->lastPosition = this->position;
        this->transitionDone = false;
        this->position = position;
    }

    void move(const Vector2i& positionDelta)
    {
        this->lastPosition = this->position;
        this->transitionDone = false;
        this->position.x += positionDelta.x;
        this->position.y += positionDelta.y;
    }

    Vector2i getPosition()
    {
        return this->position;
    }

    Vector2i getLastPosition()
    {
        return this->lastPosition;
    }


};
#endif // _PositionableClass_