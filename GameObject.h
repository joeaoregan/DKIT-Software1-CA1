/*
    Joe O'Regan
    01/10/2022
*/

#include "raylib.h"

class GameObject
{
public:
    GameObject();
    ~GameObject();

    virtual void move();
    virtual void collisions();

    Vector2 getPosition()
    {
        return m_position;
    }

    void setPosition(Vector2 position)
    {
        m_position = position;
    }

    float getSpeed()
    {
        return m_speed;
    }

    void setSpeed(float speed)
    {
        m_speed = speed;
    }

    float getX()
    {
        return m_position.x;
    }

    float getY()
    {
        return m_position.y;
    }

    void setX(float x)
    {
        m_position.x = x;
    }

    void setY(float y)
    {
        m_position.y = y;
    }

    int getWidth()
    {
        return m_width;
    }

    void setWidth(int width)
    {
        m_width = width;
    }

    int getHeight()
    {
        return m_height;
    }

    void setHeight(int height)
    {
        m_height = height;
    }

private:
    Vector2 m_position;
    float m_speed;
    int m_height;
    int m_width;
};