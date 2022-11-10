/*
    HighScores.hpp
    10/11/2022

    High score class
    Display the high scores
*/

#ifndef HIGH_SCORES_HPP
#define HIGH_SCORES_HPP

#include "GameState.hpp"

class HighScores : public GameState
{
public:
    bool checkCollision(Rectangle *a, Rectangle *b);

    virtual bool init();                  // initialise objects
    virtual void handleInput();           // handle user input
    virtual void update(float deltaTime); // update objects
    virtual void draw();                  // render objects
    virtual bool close();                 // clear objects from memory

    virtual int getStateID() const { return s_highScoresID; } // current state ID (int using enum)

private:
    static const int s_highScoresID; // identify current state
};

#endif