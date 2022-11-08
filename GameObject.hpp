/*
    GameObject.hpp
    Joe O'Regan
    01/10/2022

    Base class for game objects, such as player, background, etc
*/
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "raylib.h"
#include "Constants.hpp"
#include <vector>
#include <string>

typedef Color Colour; // Spell colour correctly

class GameObject
{
public:
    GameObject();
    GameObject(Vector2 coordinates);
    GameObject(std::string src, Rectangle rect, bool collidable);
    ~GameObject();

    virtual void init() = 0;
    virtual void move() = 0;
    virtual void collisions();
    virtual void draw() = 0;
    virtual void destroy() = 0;

    Vector2 getPosition() { return m_position; }
    void setPosition(Vector2 position) { m_position = position; }

    float getSpeed() { return m_speed; }
    void setSpeed(float speed) { m_speed = speed; }

    float getX() { return m_position.x; }
    float getY() { return m_position.y; }
    void setX(float x) { m_position.x = x; }
    void setY(float y) { m_position.y = y; }

    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
    void setWidth(int width) { m_width = width; }
    void setHeight(int height) { m_height = height; }

    Texture2D getTexture() { return m_sprite; }
    void setSprite(const char *textureSRC) { m_sprite = LoadTexture(textureSRC); }
    void setTexture(Image image) { m_sprite = LoadTextureFromImage(image); }

    bool getActive() { return isActive; }
    void setActive(bool active) { isActive = active; }
    void toggleActive() { isActive = !isActive; }

    bool getCollision() { return m_collision; }
    void setCollision(bool collision) { m_collision = collision; }

    Rectangle *getRect()
    {
        m_boundingBox = {m_position.x, m_position.y, (float)m_sprite.width, (float)m_sprite.height};
        return &m_boundingBox;
    }

    bool isCollidable() { return m_collidable; }
    void setCollidable(bool collidable) { m_collidable = collidable; }

    bool canDestroy() { return m_canDestroy; }
    void setCanDestroy(bool destroy) { m_canDestroy = destroy; }

    void incrementFrame();
    int getFrame() { return m_currentFrame; }
    void setTotalFrames(int totalFrames) { m_totalFrames = totalFrames; }
    bool isAnimationFinished() { return m_isAnimationFinished; }
    bool isAnimationLoop() { return m_isAnimationLoop; }
    void setAnimationLoop(bool loop) { m_isAnimationLoop = loop; }

    int getHealth() { return m_health; }
    void setHealth(int health) { m_health = health; }

    int getDamage() { return m_damage; }
    void setDamage(int damage) { m_damage = damage; }

    std::vector<GameObject *> getSubObjects() { return m_subObjects; }
    void addSubObject(GameObject *obj) { m_subObjects.push_back(obj); }

private:
    Vector2 m_position;
    float m_speed;
    int m_height, m_width;
    Texture2D m_sprite;
    bool isActive;
    bool m_collision;
    bool m_collidable;

    bool m_canDestroy;

    int m_currentFrame, m_totalFrames;
    bool m_isAnimationFinished, m_isAnimationLoop;

    Rectangle m_boundingBox;

    int m_health, m_damage;

    std::vector<GameObject *> m_subObjects; // list of sub-objects to update rendering etc. e.g. status bars, weapons
};

#endif