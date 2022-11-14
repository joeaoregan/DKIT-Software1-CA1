/*
    Exit.cpp
    12/11/2022

    Exit confirmation state
    display 2 buttons asking to confirm quitting game
    - overlayed, no background
*/

#include "Exit.hpp"         // header file for this class
#include "FlashingText.hpp" // flashing text use to display selected button information
#include "Button.hpp"       // button UI element
#include "InputHandler.hpp" // handle user input
#include "Game.hpp"         // change states
// #include "Menu.hpp" // test returning to menu, or creating new menu

const game_state Exit::s_exitID = EXIT_GAME; // identify current state

enum menu_options_exit // options used in menu
{
    QUIT_NO = 0,  // option 1. resume game
    QUIT_YES = 1, // option 2. quit game
};

const int BUTTON_Y = SCREEN_HEIGHT * 0.7f;       // place the buttons 70% of the screen height
const float BUTTON_HEIGHT = 50.0f;               // button height
const float BUTTON_WIDTH = SCREEN_WIDTH * 0.2f;  // button width 20% of screen width
const float BUTTON_OFFSET = BUTTON_WIDTH / 2.0f; // offset the buttons to center on width

/*
    initialise exit confirmation state
*/
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

/*
    handle user input for exit state
*/
void Exit::handleInput()
{
    // close window or ESC from Exit, should exit
    // if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
    if (WindowShouldClose()) // exit window button pressed
    {
        Game::Instance()->exitWindowRequested = true;
    }

    GameState::handleInput(); // navigate menu items in parent class -- just realised everything is not a game object, like I said in my design doc, oh well

    // action button
    if (Input::Instance()->select(DELAY)) // check if the action button is pressed with delay
    {
        switch (m_menuOption) // switch on current menu option
        {
        case QUIT_NO:                          // option 1. no
            Game::Instance()->getFSM()->pop(); // return to game / menu or whatever previous state is
            break;
        case QUIT_YES:                                    // option 2. yes
            Game::Instance()->exitWindowRequested = true; // close the window
            break;
        }
    }
}

/*
    update exit state game objects
*/
void Exit::update(float deltaTime)
{
    GameState::update(deltaTime); // update the menu objects
}

/*
    render exit state textures and shapes
*/
void Exit::draw()
{
    DrawRectangle(0, 0, 1280, 600, {75, 75, 75, 10}); // fade colour -- unexpected fade, looks cool though
    DrawRectangle(0, 600, 1280, 120, BLACK);          // Cover over previous text
    GameState::draw();                                // render the menu objects
}

/*
    clear objects when closing the exit state
*/
bool Exit::close()
{
    GameState::close(); // clear menu objects from memory

    return true; // successfully exited -- to do -- check this, or make void function
}