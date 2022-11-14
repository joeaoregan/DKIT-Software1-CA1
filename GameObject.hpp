/*
    GameObject.hpp
    Joe O'Regan
    01/10/2022

    Base class for game objects, such as player, background, etc
*/
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "raylib.h"      // raylib library header
#include "Constants.hpp" // constants used for game objects and debugging
#include <vector>        // lists of objects
#include <string>        // string manipulation

typedef Color Colour; // Spell colour correctly

enum object_id // ids fofr objects for sorting collisions
{
    GAME_OBJECT = 0,   // default object id
    PLAYER = 1,        // player object id
    PLAYER_BULLET = 2, // player bullet object id
    BLOOD_CELL = 3,    // blood cell object id
    EXPLOSION = 4,     // explosion object id
    TEXT = 5,          // text object id
    BUTTON = 6         // button object id
};

/*
    GameObject class - base class for all objects
*/
class GameObject
{
public:
    // constructors
    GameObject();                                                                                    // no args constructor
    GameObject(Vector2 coordinates);                                                                 // construct with just position vector argument
    GameObject(Rectangle rect, std::string src = "", bool collidable = false, int id = GAME_OBJECT); // main constructors
    GameObject(int id) : GameObject()                                                                // construct with just game id
    {
        m_id = id;
    }

    virtual ~GameObject(){}; // deconstructor -- todo - implements

    // pure virtual functions
    virtual void init() = 0;     // init each object
    virtual void move() = 0;     // update each object
    virtual void draw() = 0;     // render each object
    virtual void destroy();      // destroy each object
    virtual void collisions(){}; // check object collision

    inline Vector2 getPosition() const { return {m_rect.x, m_rect.y}; } // get the object coordinates from the texture rectangle
    inline void setPosition(Vector2 position)
    {
        m_rect.x = position.x; // update x coordinate
        m_rect.y = position.y; // update y coordinate
    }

    inline float getSpeed() const { return m_speed; }      // return the objects movement speed / velocity
    inline void setSpeed(float speed) { m_speed = speed; } // set the objects speed

    inline float getX() const { return m_rect.x; }           // rectangle x coordinate
    inline float getY() const { return m_rect.y; }           // rectangle y coordinate
    inline float getWidth() const { return m_rect.width; }   // rectangle width
    inline float getHeight() const { return m_rect.height; } // rectangle height

    inline void setX(float x) { m_rect.x = x; }                     // set rectangle x coordinate
    inline void setY(float y) { m_rect.y = y; }                     // set rectangle y coordinate
    inline void setWidth(float width) { m_rect.width = width; }     // set rectangle width
    inline void setHeight(float height) { m_rect.height = height; } // set rectangle height

    // Textures
    inline Texture2D getTexture() const { return m_sprite; }                              // get the object texture
    inline void setSprite(const char *textureSRC) { m_sprite = LoadTexture(textureSRC); } // set the object texture
    inline void setTexture(Texture2D &texture) { m_sprite = texture; }                    // set the object texture
    inline Rectangle *getSrcRect() { return &m_srcRect; }                                 // source rect for rendering the texture
    inline Rectangle *getRect() { return &m_rect; }                                       // destination rect for rendering the texture

    inline bool getActive() const { return isActive; }        // is the object active
    inline void setActive(bool active) { isActive = active; } // set the object active
    inline void toggleActive() { isActive = !isActive; }      // toggle active flag

    inline float getCenterX() const { return m_rect.x + (m_rect.width / 2); } // for centering text on buttons etc
    inline Vector2 getOrigin() const { return {m_rect.x, m_rect.y}; }         // origin for rotating objects etc

    inline bool canDestroy() const { return m_canDestroy; }             // object can be destoyed / deleted
    inline void setCanDestroy(bool destroy) { m_canDestroy = destroy; } // set the object to be destroyed

    // Animation
    void incrementFrame();                                                       // incement the animation frames of texture
    inline int getFrame() const { return m_currentFrame; }                       // get the current animation frame
    inline void setTotalFrames(int totalFrames) { m_totalFrames = totalFrames; } // set the total animation frames
    inline bool isAnimationFinished() const { return m_isAnimationFinished; }    // check is the animation finished
    inline bool isAnimationLoop() const { return m_isAnimationLoop; }            // does the animation loop or not
    inline void setAnimationLoop(bool loop) { m_isAnimationLoop = loop; }        // set the animation to loop or not

    // Health
    inline int getHealth() const { return m_health; }        // get the health of the object
    inline void setHealth(int health) { m_health = health; } // set the health of the object
    inline int getDamage() const { return m_damage; }        // get the damage the object inflicts on other objects
    inline void setDamage(int damage) { m_damage = damage; } // set the damage the object inflicts

    inline std::vector<GameObject *> getSubObjects() const { return m_subObjects; } // get the sub objects of an object
    inline void addSubObject(GameObject *obj) { m_subObjects.push_back(obj); }      // add a sub object for the object

    inline int getID() const { return m_id; } // get the object id
    inline void setID(int id) { m_id = id; }  // set the object id

    inline bool isSelected() const { return m_selected; }             // check is object selected
    inline void setSelected(bool selected) { m_selected = selected; } // set the object as selected or not

    // collisions
    inline bool getCollision() const { return m_collision; }              // has the object collided
    inline void setCollision(bool collision) { m_collision = collision; } // set the object as collided or not

    inline void setOffset(Vector2 o) { m_collisionRectPositionOffset = o; } // offset for collision rect
    inline Rectangle *getCollisionRect() { return &m_collisionRect; }       // rectangle for collision detection
    // void setCollisionRect(Rectangle rect) { m_collisionRect = rect; } // set collision rect
    inline void setCollisionRect(Rectangle r) { m_collisionRect = {r.x - m_collisionRectPositionOffset.x, r.y - m_collisionRectPositionOffset.y, r.width, r.height}; } // set collision rect with offset

    inline bool isCollidable() const { return m_collidable; }                 // check is the object collidable - todo google is collidable actually a word
    inline void setCollidable(bool collidable) { m_collidable = collidable; } // set the object as collidable or not for collision checks
    // debug collisions using collision rect / bounding boxs

    /*
        Draw rectangle to display the collision rect of the current object
        can pass parameter of the debug flags that may need to check rectangles
    */
    void drawCollisionRect(bool debug = false)
    {
        if (DEBUG_ALL || DEBUG_COLLISIONS || debug) // if debugging all object, or collisions, or the debug flag passed in
        {
            DrawRectangleLines(m_collisionRect.x, m_collisionRect.y, m_collisionRect.width, m_collisionRect.height, YELLOW); // draw the collision rectangle in yellow
        }
    }

    void debug(std::string msg, bool debug = false); // message to display when debugging and flag to set to activate the message

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

    Vector2 m_collisionRectPositionOffset; // offset

    int m_health; // health for object
    int m_damage; // damage object inflicts

    bool m_selected = false; // object is selected

    std::vector<GameObject *> m_subObjects; // list of sub-objects to update rendering etc. e.g. status bars, weapons
};

#endif