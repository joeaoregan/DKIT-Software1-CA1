/*
    Game.cpp
    1/10/2022

    Game class
    Implements singleton pattern, so only one instace of game active at a time
*/

#include "Game.hpp"
#include "Menu.hpp"
#include "InputHandler.hpp"
#include "Player.hpp"

Game *Game::s_pGame = 0;
GameObject *player;

bool Game::init()
{
    m_bRunning = true;
    bool success = true;

    player = new Player();

    m_currentGameState = MENU;

    m_pStateMachine = new StateMachine();
    m_pStateMachine->change(new Menu());

    return success;
}

void Game::update(float deltaTime)
{
    m_pStateMachine->update(deltaTime);
}

void Game::handleEvents()
{
    m_pStateMachine->handleInput();
}

void Game::draw()
{
    // to do
    m_pStateMachine->draw();
}

void Game::close()
{
    std::cout << "cleaning game" << std::endl;
    Input::Instance()->close();
}

void Game::reset(int level)
{
    // to do
}