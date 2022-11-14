/*
    Game.cpp
    1/10/2022

    Game class
    Implements singleton pattern, so only one instace of game active at a time
*/

#include "Game.hpp"         // This class header file
#include "Menu.hpp"         // State machine starts game in menu state
#include "InputHandler.hpp" // handle user input
#include "Player.hpp"       // Player in Game class, then pass through levels -- todo - implement more than one level -- array of players for multiplayer
#include "StateMachine.hpp" // FSM - manage states

Game *Game::s_pGame = 0; // one instance of Game exists using singleton pattern

/*
    initialise the game
*/
bool Game::init()
{
    // m_bRunning = true;   // is the game running
    bool success = true; // in sdl you get boolean confirmation of textures loading etc. -- todo take this out it's not needed, make init void

    // player = new Player(); // player game object

    m_currentGameState = MENU; // the game starts in Menu state

    FSM::Instance()->change(new Menu()); // start game in menu state

    return success; // not needed as no checks carried out -- todo - remove or perform initialisation checks
}

/*
    update the game state
*/
void Game::update(float deltaTime)
{
    FSM::Instance()->update(deltaTime); // update the current state
}

/*
    handle user input
*/
void Game::handleEvents()
{
    FSM::Instance()->handleInput(); // handle user input for current state
}

/*
    render the game state
*/
void Game::draw()
{
    FSM::Instance()->draw(); // render the current state
}

/*
    exit the current state
*/
void Game::close()
{
    std::cout << "cleaning game" << std::endl;
    Input::Instance()->close();
}

void Game::reset(int level)
{
    // todo -- RESET game / level, clear totals etc
}