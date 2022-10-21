/*
    Game.hpp
    Joe O'Regan
    01/10/2022

    Game class
    Implements singleton pattern, so only one instace of game active at a time
*/
#ifndef GAME_HPP
#define GAME__HPP

#include "StateMachine.hpp"

class Game
{
public:
    ~Game() {} // deconstructor

    static Game *Instance()
    {
        if (s_pGame == 0) // if there is no game instance
        {
            s_pGame = new Game(); // create one
            return s_pGame;       // use it
        }
        return s_pGame; // otherwise use existing instance
    }

    bool init();           // initialise game
    void update();         // update the game
    void handleEvents();   // handle game events
    void draw();           // render the game
    void close();          // remove objects from memory
    void reset(int level); // reset the current level

    StateMachine *m_pStateMachine; // state handler (finite state machine (FSM))

    bool isRunning() { return m_bRunning; } // getter: game running?
    int getScore() { return m_Score; }      // getter: score
    int getLevel() { return m_Level; }      // getter: level
    Font getFont() { return m_fontRetro; }  // getter: font

    int m_currentGameState; // current game state

private:
    Game() : m_Score(0), m_Level(1), m_fontRetro(LoadFont("resources/fonts/Retro.ttf")) {} // constructor

    int m_Score;      // game current score
    int m_Level;      // game current level
    Font m_fontRetro; // font for text

    static Game *s_pGame; // singleton instance of game
    bool m_bRunning;      // is the game running
};

#endif