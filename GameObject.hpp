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
    PLAYER_BULLET = 2,
    BLOOD_CELL = 3,
    EXPLOSION = 4,
    TEXT = 5,
    BUTTON = 6
};

class GameObject
{
public:
    // constructor
    GameObject();
    GameObject(Vector2 coordinates);
    GameObject(Rectangle rect, std::string src = "", bool collidable = false, int id = GAME_OBJECT);
    GameObject(int id) : GameObject()
    {
        m_id = id;
    }

    virtual ~GameObject(){}; // deconstructor

    // pure virtual functions
    virtual void init() = 0; // init each object
    virtual void move() = 0; // update each object
    virtual void draw() = 0; // render each object

    virtual void destroy(); // destroy each object
    virtual void collisions(){};

    Vector2 getPosition() { return {m_rect.x, m_rect.y}; }
    void setPosition(Vector2 position)
    {
        m_rect.x = position.x;
        m_rect.y = position.y;
    }

    float getSpeed() { return m_speed; }
    void setSpeed(float speed) { m_speed = speed; }

    float getX() { return m_rect.x; }
    float getY() { return m_rect.y; }
    float getWidth() { return m_rect.width; }
    float getHeight() { return m_rect.height; }

    void setX(float x) { m_rect.x = x; }
    void setY(float y) { m_rect.y = y; }
    void setWidth(float width) { m_rect.width = width; }
    void setHeight(float height) { m_rect.height = height; }

    // Textures
    Texture2D getTexture() { return m_sprite; }
    void setSprite(const char *textureSRC) { m_sprite = LoadTexture(textureSRC); }
    // void setTexture(Image image) { m_sprite = LoadTextureFromImage(image); }
    void setTexture(Texture2D &texture) { m_sprite = texture; }
    Rectangle *getSrcRect() { return &m_srcRect; } // source rect for rendering the texture
    Rectangle *getRect() { return &m_rect; }       // destination rect for rendering the texture

    bool getActive() { return isActive; }
    void setActive(bool active) { isActive = active; }
    void toggleActive() { isActive = !isActive; }

    float getCenterX() { return m_rect.x + (m_rect.width / 2); } // for centering text on buttons etc
    Vector2 getOrigin() { return {m_rect.x, m_rect.y}; }         // origin for rotating objects etc

    bool canDestroy() { return m_canDestroy; }
    void setCanDestroy(bool destroy) { m_canDestroy = destroy; }

    // Animation
    void incrementFrame();
    int getFrame() { return m_currentFrame; }
    void setTotalFrames(int totalFrames) { m_totalFrames = totalFrames; }
    bool isAnimationFinished() { return m_isAnimationFinished; }
    bool isAnimationLoop() { return m_isAnimationLoop; }
    void setAnimationLoop(bool loop) { m_isAnimationLoop = loop; }

    // Health
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

    // collisions
    bool getCollision() { return m_collision; }
    void setCollision(bool collision) { m_collision = collision; }

    Rectangle *getCollisionRect() { return &m_collisionRect; } // rectangle for collision detection
    // void setCollisionRect(Rectangle rect) { m_collisionRect = rect; } // set collision rect
    void setCollisionRect(Rectangle r) { m_collisionRect = {r.x - offset.x, r.y - offset.y, r.width, r.height}; } // set collision rect
    void setOffset(Vector2 o) { offset = o; }                                                                     // offset for collision rect

    bool isCollidable() { return m_collidable; }
    void setCollidable(bool collidable) { m_collidable = collidable; }
    // debug collisions using collision rect / bounding boxs
    void drawCollisionRect(bool debug = false)
    {
        if (DEBUG_ALL || DEBUG_COLLISIONS || debug)
        {
            DrawRectangleLines(m_collisionRect.x, m_collisionRect.y, m_collisionRect.width, m_collisionRect.height, YELLOW);
        }
    }

    void debug(std::string msg, bool debug = false);

    Vector2 offset;

private:
    int m_id;           // identify the type of object
    float m_speed;      // how quickly the object moves
    Texture2D m_sprite; // object sprite texture
    bool isActive;      // draw the object on screen
    bool m_collision;   // the object has collided with another object
    bool m_collidable;  // object can collide with others

    bool m_canDestroy; // object can be removed from memory

    int m_currentFrame;         // current frame of sprite animation
    int m_totalFrames;          // number of frames for animation
    bool m_isAnimationFinished; // is sprite animation finished
    bool m_isAnimationLoop;     // does the animation loop

    Rectangle m_srcRect;       // source rectanglefor rendering the texture
    Rectangle m_rect;          // bounding box of object (might be redundant for now)
    Rectangle m_collisionRect; // allow for collision on different shape to sprite, e.g. for transparent areas

    int m_health; // health for object
    int m_damage; // damage object inflicts

    bool m_selected = false; // object is selected

    std::vector<GameObject *> m_subObjects; // list of sub-objects to update rendering etc. e.g. status bars, weapons
};

#endif