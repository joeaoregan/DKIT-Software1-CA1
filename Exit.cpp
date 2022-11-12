/*
    Exit.cpp
    12/11/2022

    Exit confirmation state
    display 2 buttons asking to confirm quitting game
    - overlayed, no background
*/

#include "Exit.hpp"
#include "FlashingText.hpp"
#include "Button.hpp"
#include "InputHandler.hpp"
#include "Game.hpp" // change states
#include "Menu.hpp"
#include <string>

const game_state Exit::s_exitID = EXIT_GAME; // identify current state

enum menu_options_exit
{
    QUIT_NO = 0,  // option 1. resume game
    QUIT_YES = 1, // option 2. quit game
};

const int BUTTON_Y = SCREEN_HEIGHT * 0.7f;       // place the buttons 70% of the screen height
const float BUTTON_HEIGHT = 50.0f;               // button height
const float BUTTON_WIDTH = SCREEN_WIDTH * 0.2f;  // button width 20% of screen width
const float BUTTON_OFFSET = BUTTON_WIDTH / 2.0f; // offset the buttons to center on width

bool Exit::init()
{
    setNoBackground(); // No background used for this state

    // add Flashing text
    flashingTextObjs.push_back(new FlashText("Return to Game", {100, 635}, HEADING));
    flashingTextObjs.push_back(new FlashText("Exit", {100, 635}, HEADING));

    // add buttons
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.75f - BUTTON_OFFSET, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT}, "Resume"))); // Option 1: Resume the game
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.25f - BUTTON_OFFSET, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT}, "Exit")));   // Option 2: Exit the game

    GameState::init(); // initialise objects in object list

    return true; // successfully initialised -- to do -- check this, or make void function
}

void Exit::handleInput()
{
    // close window or ESC from Exit, should exit
    // if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
    if (WindowShouldClose())
    {
        Game::Instance()->exitWindowRequested = true;
    }

    GameState::handleInput(); // navigate menu items

    // action button
    if (Input::Instance()->select(DELAY))
    {
        switch (m_menuOption)
        {
        case QUIT_NO:
            Game::Instance()->m_pStateMachine->pop(); // return to game / menu or whatever previous state is
            break;
        case QUIT_YES:
            Game::Instance()->exitWindowRequested = true;
            break;
        }
    }
}

void Exit::update(float deltaTime)
{
    GameState::update(deltaTime); // update the menu objects
}

void Exit::draw()
{
    DrawRectangle(0, 0, 1280, 600, {75, 75, 75, 10}); // fade colour -- unexpected fade, looks cool though
    DrawRectangle(0, 600, 1280, 120, BLACK);          // Cover over previous text

    GameState::draw(); // render the menu objects
}

bool Exit::close()
{
    GameState::close(); // clear menu objects from memory

    return true; // successfully exited -- to do -- check this, or make void function
}