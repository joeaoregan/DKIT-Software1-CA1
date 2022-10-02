/*
    Joe O'Regan
    01/10/2022
*/
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "raylib.h"
#include "Constants.hpp"
#include <vector>

class GameObject
{
public:
    GameObject();
    GameObject(Vector2 coordinates);
    ~GameObject();

    virtual void init();
    virtual void move();
    virtual void collisions();
    virtual void draw();
    virtual void destroy();

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

    Texture2D getTexture()
    {
        return m_sprite;
    }

    void setSprite(const char *textureSRC)
    {
        m_sprite = LoadTexture(textureSRC);
    }

    void setTexture(Image image)
    {
        m_sprite = LoadTextureFromImage(image);
    }

    bool getActive()
    {
        return isActive;
    }

    void toggleActive()
    {
        isActive = !isActive;
    }

    void setActive(bool active)
    {
        isActive = active;
    }

private:
    Vector2 m_position;
    float m_speed;
    int m_height;
    int m_width;
    Texture2D m_sprite;
    bool isActive;
};

#endif