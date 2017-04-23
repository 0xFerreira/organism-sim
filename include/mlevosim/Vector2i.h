#ifndef _Vector2iStruct_
#define _Vector2iStruct_

struct Vector2i
{
    int x = 0;
    int y = 0;

    Vector2i(int x = 0, int y = 0)
    {
        this->x = x;
        this->y = y;
    }

    Vector2i& operator+(const Vector2i& other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    Vector2i& operator-(const Vector2i& other)
    {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }

    Vector2i& operator*(const Vector2i& other)
    {
        this->x *= other.x;
        this->y *= other.y;

        return *this;
    }

    Vector2i& operator/(const Vector2i& other)
    {
        this->x /= other.x;
        this->y /= other.y;

        return *this;
    }

    Vector2i& operator*(float other)
    {
        this->x *= other;
        this->y *= other;

        return *this;
    }
};
#endif //_Vector2iStruct_