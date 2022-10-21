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
#include "Level.hpp"

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

void Game::update()
{
    m_pStateMachine->update();
}

void Game::handleEvents()
{
    InputHandler::Instance()->update();

    if (IsKeyDown(KEY_ENTER))
    {
        m_pStateMachine->change(new Level());
    }
}

void Game::draw()
{
    // to do
    m_pStateMachine->draw();
}

void Game::close()
{
    std::cout << "cleaning game" << std::endl;
    InputHandler::Instance()->close();
}

void Game::reset(int level)
{
    // to do
}