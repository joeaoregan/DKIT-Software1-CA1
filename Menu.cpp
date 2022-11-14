/*
    Menu.cpp
    20/10/2022

    Menu state class
*/

#include "Menu.hpp"         // this class header
#include "FlashingText.hpp" // flashing text for menu options description
#include "Button.hpp"       // button UI objects
#include "InputHandler.hpp" // handle user input
#include "Game.hpp"         // get state machine to change states
#include "Level.hpp"        // progress to level state
#include "HighScores.hpp"   // progress to high score state
#include "Exit.hpp"         // load exit state

const game_state Menu::s_menuID = MENU; // identify current state

enum menu_options // option button ids
{
    MENU_START = 0,  // Option 1. Start the game
    MENU_HIGH_SCORE, // Option 2. View high scores
    MENU_QUIT        // Option 3. Quit the game
};

/*
init menu state
*/
bool Menu::init()
{
    // std::cout << "entering menu state" << std::endl;

    // add button descriptor flashing text & Push to menu objects list as GameObject
    flashingTextObjs.push_back(new FlashText("Press Enter to Start", {100, 635}, HEADING)); // Option 1. descriptive text
    flashingTextObjs.push_back(new FlashText("View High Scores", {100, 635}, HEADING));     // Option 2. descriptive text
    flashingTextObjs.push_back(new FlashText("Press Enter to Quit", {100, 635}, HEADING));  // Option 3. descriptive text

    float btnX = SCREEN_WIDTH * 0.2f;     // button padding is 20% of screen on sides
    float btnWidth = SCREEN_WIDTH * 0.6f; // button width is 60% of screen
    float btnHeight = 50;
    selectableObjects.push_back((GameObject *)(new Button({btnX, 60, btnWidth, btnHeight}, "Start Game")));   // Option 1. start game button
    selectableObjects.push_back((GameObject *)(new Button({btnX, 120, btnWidth, btnHeight}, "High Scores"))); // Option 2. high scores button
    selectableObjects.push_back((GameObject *)(new Button({btnX, 180, btnWidth, btnHeight}, "Exit")));        // Option 3. exit game button

    GameState::init(); // initialise objects in object list

    return true; // successfully initialised -- to do -- check this, or make void function
}

/*
handle menu state user input
*/
void Menu::handleInput()
{
    GameState::handleInput(); // navigate menu items

    // action button
    if (Input::Instance()->select(DELAY))
    {
        switch (m_menuOption)
        {
        case MENU_START:
            // std::cout << "start game" << std::endl;
            Game::Instance()->getFSM()->change(new Level()); // Change to Level state
            break;
        case MENU_HIGH_SCORE:
            // std::cout << "high scores" << std::endl;
            Game::Instance()->getFSM()->change(new HighScores()); // Change to high score state
            break;
        case MENU_QUIT:
            // std::cout << "quit game" << std::endl;
            Game::Instance()->getFSM()->push(new Exit()); // Show confirm exit state
            break;
        }
    }
}

/*
update menu state
*/
void Menu::update(float deltaTime)
{
    GameState::update(deltaTime); // update the menu objects from parent class update function
}

/*
render menu state
*/
void Menu::draw()
{
    ClearBackground(RED); // clear the screen before rendering the next frame
    GameState::draw();    // render the menu objects using base class default function
}

/*
exit menu state
*/
bool Menu::close()
{
    // std::cout << "exiting menu state" << std::endl;
    GameState::close(); // clear menu objects from memory in parent class

    return true; // successfully exited -- to do -- check this, or make void function
}