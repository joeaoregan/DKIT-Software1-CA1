/*
    Level.cpp
    20/10/2022

    Level state class
    Seperate state for level
*/

#include "Game.hpp"         // access game singleton for scores etc.
#include "Constants.hpp"    // constant values for window and debugging
#include "Level.hpp"        // this class header file
#include "Player.hpp"       // player instance -- todo maybe create in game class and move between levels
#include "BloodCell.hpp"    // blood cell obstacle
#include "Explosion.hpp"    // explosion for destroying blood cells
#include "Pause.hpp"        // enter pause state from play state
#include "InputHandler.hpp" // handle user input

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

    if (aLeft > SCREEN_WIDTH || aRight < 0.0f || bLeft > SCREEN_WIDTH || bRight < 0.0f) // if A or B is off the screen on either side
    {
        return false; // An object is off screen can't score points or lose health
    }

    // If any of the sides from A are outside of B
    if (aBottom < bTop) // if the bottom of A is higher up the screen than the top of B
    {
        return false; // A is over B
    }
    else if (aTop >= bBottom) // if the top of A is lower down the screen than the bottom of B
    {
        return false; // A is under B
    }
    else if (aRight <= bLeft) // if the right side of A is to the left of the left side of B
    {
        return false; // A is left of B
    }
    else if (aLeft >= bRight) // if the left side of A is to the right side of B
    {
        return false; // A is right of B
    }

    std::cout << "collision" << std::endl;
    return true; // If none of the sides from A are outside B -> Collision!
}

/*
init level class
*/
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

    for (unsigned int i = 0; i < playerObjects.size(); i++) // for each game object
    {
        niceList.push_back(playerObjects[i]); // add player sub objects to player objects list
    }

    txtScoreWidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), TextFormat("Score: %08i", Game::Instance()->getScore()), fontSizeHeading, 1).x / 2); // calculate the score center position (done once now, with 8 positions of integer)

    return true; // no errors in initialising -- to do -- check for errors in initialising
}

/*
handle user input for level state
*/
void Level::handleInput()
{
    GameState::handleInput(); // call game state base class user input function for default user input

    if (IsKeyPressed(KEY_ESCAPE)) // if the escape key is pressed
    {
        // todo -- figure out why key press is carrying over between level and pause states
        std::cout << "level - why is this happening" << std::endl;
    }
}

/*
update level state
*/
void Level::update(float deltaTime)
{
    GameState::update(deltaTime); // update the game objects, functionality inherited from GameState

    for (GameObject *obj : naughtyList) // for every object in this state
    {
        (*obj).move(); // update the object
    }

    handleCollisions(); // handle collisions for level state -- todo call collision handling separately for states
}

/*
    Handle collisions between player objects & obstacles / enemy objects
*/
void Level::handleCollisions()
{
    for (unsigned int i = 0; i < niceList.size(); i++) // for each player object
    {
        (*niceList[i]).move();            // update the object
        if (!niceList[i]->isCollidable()) // if the object is collidable (e.g. status bar wouldn't be)
            continue;                     // don't bother doing anything else

        for (unsigned int j = 0; j < naughtyList.size(); j++) // for each object on the enemey / obstacle list
        {
            if (!naughtyList[j]->getActive())                                           // if the object is active
                continue;                                                               // if the enemy object / obstacle isn't active, no need to do anything
            if (naughtyList[j]->getID() == EXPLOSION && niceList[i]->getID() != PLAYER) // if the object is an explosion and the player object isn't the player ship
                continue;                                                               // skip the rest as explosions only collide with players

            collision = checkCollision(niceList[i]->getRect(), naughtyList[j]->getRect()); // flag if player objects collide with obstacles

            if (collision) // what to do if there is a collision
            {
                collision = false; // reset collision flag

                if (naughtyList[j]->getID() != EXPLOSION) // if the object is not already an explosion
                {
                    GameObject *exp = new Explosion(naughtyList[j]->getPosition()); // Add an explosion where the object was destroyed
                    naughtyList.push_back(exp);                                     // add to list of objects to render
                }

                niceList[i]->setCollision(true);    // flag collision has happened for this player object
                naughtyList[j]->setCollision(true); // flag collision has happened for this enemy / obstacle object

                // std::cout << "new expl osion created: " << naughtyList[j]->getPosition().x << ":" << naughtyList[j]->getPosition().y << std::endl;
                Player *playerType = dynamic_cast<Player *>(niceList[i]);                              // Cast player object from base class GameObject to perform it's own functions that base class doesn't have
                if (playerType != nullptr && niceList[i]->getCollision() && !playerType->isFlashing()) // do this if casting worked, the player has collided, and isn't flashing from previous collision
                {
                    if (naughtyList[j]->getID() == EXPLOSION && naughtyList[j]->getActive()) // if the player has collided with a blood explosion
                    {
                        splat = 200;                      // cover screen in blood -- todo - delete object from list? - niceList[i]->setCollidable(false)
                        naughtyList[j]->setActive(false); // the object no longer needs to be active
                    }
                    else
                    {
                        // niceList[i]->setHealth(niceList[i]->getHealth() - naughtyList[j]->getDamage()); // reduce health by the amount of damage inflicted
                        playerType->setHealth(playerType->getHealth() - naughtyList[j]->getDamage()); // deduct the damage the enemy object inflicts from the players health
                        std::cout << "Player Health: " << niceList[i]->getHealth() << std::endl;      // todo -- debug message all comments
                    }
                }
            }
        }
    }
}

/*
render draw state
*/
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

    // Blood on screen (red fade)
    DrawRectanglePro({0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, {0, 0}, 0, {230, 41, 55, (unsigned char)splat}); // BLOOD fade in at start and when player collides with blood splatter / blood explosion -- todo make this an object
    splat -= 5;                                                                                            // red fade effect for starting level and blood on screen
    if (splat < 0 || splat > 255)                                                                          // if splat overlay rectangle goes out of bounds
        splat = 0;                                                                                         // reset value to 0
}

/*
exit level state
*/
bool Level::close()
{
    // std::cout << "exiting level state" << std::endl;

    GameState::close(); // clear the objects in the state from memory

    return true; // no errors in exiting -- to do -- check for errors in exiting, or create void function
}