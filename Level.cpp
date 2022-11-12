/*
    Level.cpp
    20/10/2022

    Level state class
    Seperate state for level
*/

#include "Game.hpp"
#include "Constants.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "BloodCell.hpp"
#include "Explosion.hpp"
#include "Pause.hpp"
#include "InputHandler.hpp"

const game_state Level::s_levelID = LEVEL_1; // int more efficient than string, enum more readable

int txtScoreWidthCenter; // center the score at top of screen

bool collision = false; // collision detected

/*
    Check object collisions -- todo - move to its own file
*/
bool Level::checkCollision(Rectangle *a, Rectangle *b)
{

    // Calculate the sides of rect A
    float aLeft = (*a).x;                 // left of rectangle a
    float aRight = (*a).x + (*a).width;   // right of rectangle a
    float aTop = (*a).y;                  // top of rectangle a
    float aBottom = (*a).y + (*a).height; // bottom of rectangle a

    // Calculate the sides of rect B
    float bLeft = (*b).x;                 // left of rectangle b
    float bRight = (*b).x + (*b).width;   // right of rectangle b
    float bTop = (*b).y;                  // top of rectangle b
    float bBottom = (*b).y + (*b).height; // bottom of rectangle b

    if (aLeft > SCREEN_WIDTH || aRight > SCREEN_WIDTH)
    {
        return false; // object is off screen can't score points or lose health
    }

    // If any of the sides from A are outside of B
    if (aBottom < bTop)
    {
        return false; // A is over B
    }
    else if (aTop >= bBottom)
    {
        return false; // A is under B
    }
    else if (aRight <= bLeft)
    {
        return false; // A is left of B
    }
    else if (aLeft >= bRight)
    {
        return false; // A is right of B
    }

    std::cout << "collision" << std::endl;
    return true; // If none of the sides from A are outside B -> Collision!
}

bool Level::init()
{
    // std::cout << "entering level state" << std::endl;
    player = new Player();      // Instantiate player object
    player->init();             // Initialise player object
    niceList.push_back(player); // Add player to list of player objects for collision

    for (int i = 0; i < NUM_BLOOD_CELLS; i++) // set the number of blood cell objects in constants header file
    {
        GameObject *bc = new BloodCell(); // create bloodcell
        naughtyList.push_back(bc);        // add blood cells to obstacle list
    }

    GameState::init(); // initialise the list of objects

    std::vector<GameObject *> playerObjects = ((Player *)player)->getSubObjects(); // player sub objects to update, render, etc.

    for (unsigned int i = 0; i < playerObjects.size(); i++)
    {
        (*playerObjects[i]).setActive(false); // set player objects inactive
        niceList.push_back(playerObjects[i]); // add player sub objects to player objects list
    }

    txtScoreWidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), TextFormat("Score: %08i", Game::Instance()->getScore()), fontSizeHeading, 1).x / 2); // calculate the score center position (done once now, with 8 positions of integer)

    return true; // no errors in initialising -- to do -- check for errors in initialising
}

void Level::handleInput()
{
    GameState::handleInput();

    if (IsKeyPressed(KEY_ESCAPE))
    {
        // todo -- figure out why key press is carrying over between level and pause states
        std::cout << "level - why is this happening" << std::endl;
    }
}

void Level::update(float deltaTime)
{
    GameState::update(deltaTime); // update the game objects, functionality inherited from GameState

    for (unsigned int i = 0; i < niceList.size(); i++)
    {
        (*niceList[i]).move(); // update the object
        if (!niceList[i]->isCollidable())
            continue; // if the object can't collide, don't bother doing anything else
        for (unsigned int j = 0; j < naughtyList.size(); j++)
        {
            collision = checkCollision(niceList[i]->getRect(), naughtyList[j]->getRect()); // flag if player objects collide with obstacles

            // what to do if there is a collision
            if (collision)
            {
                collision = false; // reset collision flag

                GameObject *exp = new Explosion(naughtyList[j]->getPosition()); // Add an explosion where the object was destroyed
                objects.push_back(exp);                                         // add to list of objects to render
                // std::cout << "new explosion created: " << naughtyList[j]->getPosition().x << ":" << naughtyList[j]->getPosition().y << std::endl;

                niceList[i]->setCollision(true);    // flag collision has happened for this object
                naughtyList[j]->setCollision(true); // flag collision has happened for this object

                Player *playerType = dynamic_cast<Player *>(niceList[i]);                              // Cast playe object from base class GameObject to perform it's own functions that base class doesn't have
                if (playerType != nullptr && niceList[i]->getCollision() && !playerType->isFlashing()) // do this if casting worked, the player has collided, and isn't flashing from previous collision
                {
                    // niceList[i]->setHealth(niceList[i]->getHealth() - naughtyList[j]->getDamage()); // reduce health by the amount of damage inflicted
                    playerType->setHealth(playerType->getHealth() - naughtyList[j]->getDamage()); // deduct the damage the enemy object inflicts from the players health
                    std::cout << "Player Health: " << niceList[i]->getHealth() << std::endl;      // todo -- debug message all comments
                }
            }
        }
    }

    for (GameObject *obj : naughtyList) // for every object in this state
    {
        (*obj).move(); // update the object
    }
}

void Level::draw()
{
    GameState::draw(); // render the background objects first

    for (GameObject *obj : niceList) // for every object in this state
    {
        (*obj).draw(); // render the object
    }

    for (GameObject *obj : naughtyList) // for every object in this state
    {
        (*obj).draw(); // render the object
    }

    DrawTextEx(Game::Instance()->getFont(), TextFormat("Score: %08i", Game::Instance()->getScore()), {(float)txtScoreWidthCenter, 10.0F}, fontSizeHeading, 1, WHITE); // display the score
    DrawTextEx(Game::Instance()->getFont(), TextFormat("Level: %01i", Game::Instance()->getLevel()), {20.0F, 10.0F}, fontSizeHeading, 1, WHITE);                      // display the current level
}

bool Level::close()
{
    // std::cout << "exiting level state" << std::endl;

    GameState::close(); // clear the objects in the state from memory

    return true; // no errors in exiting -- to do -- check for errors in exiting, or create void function
}