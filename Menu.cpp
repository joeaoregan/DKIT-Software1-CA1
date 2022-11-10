/*
    Menu.cpp
    20/10/2022

    Menu state class
*/

#include "Menu.hpp"
#include "Background.hpp"
#include "FlashingText.hpp"
#include "Button.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include "HighScores.hpp"

const int Menu::s_menuID = MENU; // identify current state

enum menu_options
{
    MENU_START = 0,
    MENU_HIGH_SCORE = 1,
    MENU_QUIT = 2
};

bool Menu::init()
{
    // std::cout << "entering menu state" << std::endl;

    // add background
    GameObject *bg = new Background(); // use different background for menu -- to do -- change from game background
    objects.push_back(bg);             // add background to state objects list

    // add title
    GameObject *txt1 = new Text("CA1 Raylib Application", {0, 0}, HEADING, true, WHITE);
    objects.push_back(txt1);
    objects.push_back((GameObject *)(new Text("by Joe O'Regan (D00262717)", {0, 570}, SUB_HEADING, true, WHITE)));

    // add button descriptor flashing text
    flashingTextObjs.push_back(new FlashText("Press Enter to Start", {100, 635}, HEADING)); // Push to menu objects list as GameObject
    flashingTextObjs.push_back(new FlashText("View High Scores", {100, 635}, HEADING));
    flashingTextObjs.push_back(new FlashText("Press Enter to Quit", {100, 635}, HEADING));

    // add buttons
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH / 2.0f, 60, SCREEN_WIDTH * 0.6f, 50}, "Start Game")));
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH / 2.0f, 120, SCREEN_WIDTH * 0.6f, 50}, "High Scores")));
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH / 2.0f, 180, SCREEN_WIDTH * 0.6f, 50}, "Exit")));

    GameState::init(); // initialise objects in object list

    return true; // successfully initialised -- to do -- check this, or make void function
}

void Menu::handleInput()
{
    // action button
    if (Input::Instance()->select(DELAY))
    {
        switch (m_menuOption)
        {
        case MENU_START:
            // std::cout << "start game" << std::endl;
            Game::Instance()->m_pStateMachine->change(new Level());
            break;
        case MENU_HIGH_SCORE:
            // std::cout << "high scores" << std::endl;
            Game::Instance()->m_pStateMachine->change(new HighScores());
            break;
        case MENU_QUIT:
            std::cout << "quit game" << std::endl;
            break;
        }
    }

    // x axis input
    if (Input::Instance()->left(DELAY))
    {
        std::cout << "left key pressed" << std::endl;
    }
    else if (Input::Instance()->right(DELAY))
    {
        std::cout << "right key pressed" << std::endl;
    }
    // y axis input
    if (Input::Instance()->up(DELAY))
    {
        // m_menuOption--;
        menuOptionChange(m_menuOption, DECREMENT);
        // std::cout << "up key pressed - option: " << m_menuOption << std::endl;
    }
    else if (Input::Instance()->down(DELAY))
    {
        // m_menuOption++;
        menuOptionChange(m_menuOption, INCREMENT);
        // std::cout << "down key pressed - option: " << m_menuOption << std::endl;
    }
}

void Menu::update(float deltaTime)
{
    // std::cout << "menu update" << std::endl;
    GameState::update(deltaTime); // update the menu objects
}

void Menu::draw()
{
    ClearBackground(RED); // clear the screen before rendering the next frame
    // DrawRectangle(0, 600, 1280, 120, BLACK); // background for flashing text
    GameState::draw(); // render the menu objects
}

bool Menu::close()
{
    // std::cout << "exiting menu state" << std::endl;

    GameState::close(); // clear menu objects from memory

    return true; // successfully exited -- to do -- check this, or make void function
}