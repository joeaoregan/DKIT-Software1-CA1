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

enum object_id
{
    GAME_OBJECT = 0,
    PLAYER = 1,
    BULLET = 2,
    BLOOD_CELL = 3,
    EXPLOSION = 4,
    TEXT = 5
};

class GameObject
{
public:
    // constructor
    GameObject();
    GameObject(Vector2 coordinates);
    GameObject(Rectangle rect, std::string src = "", bool collidable = false);
    GameObject(int id)
    {
        m_id = id;
    }

    ~GameObject(){}; // deconstructor

    // pure virtual functions
    virtual void init() = 0; // init each object
    virtual void move() = 0; // update each object
    virtual void draw() = 0; // render each object

    virtual void destroy(); // destroy each object
    virtual void collisions(){};

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

    int getID() { return m_id; }
    void setID(int id) { m_id = id; }

    bool isSelected() { return m_selected; }
    void setSelected(bool selected) { m_selected = selected; }

private:
    int m_id;              // identify the type of object
    Vector2 m_position;    // object position
    float m_speed;         // how quickly the object moves
    int m_height, m_width; // object dimensions
    Texture2D m_sprite;    // object sprite texture
    bool isActive;         // draw the object on screen
    bool m_collision;      // the object has collided with another object
    bool m_collidable;     // object can collide with others

    bool m_canDestroy; // object can be removed from memory

    int m_currentFrame;         // current frame of sprite animation
    int m_totalFrames;          // number of frames for animation
    bool m_isAnimationFinished; // is sprite animation finished
    bool m_isAnimationLoop;     // does the animation loop

    Rectangle m_boundingBox; // bounding box of object (might be redundant for now)

    int m_health; // health for object
    int m_damage; // damage object inflicts

    bool m_selected = false; // object is selected

    std::vector<GameObject *> m_subObjects; // list of sub-objects to update rendering etc. e.g. status bars, weapons
};

#endif