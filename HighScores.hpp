/*
    HighScores.hpp
    10/11/2022

    High score class
    Display the high scores
*/

#ifndef HIGH_SCORES_HPP
#define HIGH_SCORES_HPP

#include "GameState.hpp" // base class header

class HighScores : public GameState // high scores is a child of GameState
{
public:
    virtual bool init();                  // initialise objects
    virtual void handleInput();           // handle user input
    virtual void update(float deltaTime); // update objects
    virtual void draw();                  // render objects
    virtual bool close();                 // clear objects from memory

    virtual game_state getStateID() const { return s_highScoresID; } // current state ID (int using enum)

private:
    static const game_state s_highScoresID; // identify current state
};

#endif