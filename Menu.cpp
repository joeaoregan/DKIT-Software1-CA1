/*
    Menu.cpp
    20/10/2022

    Menu state class
*/

#include "Menu.hpp"
#include "Background.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "InputHandler.hpp"

const int Menu::s_menuID = MENU; // identify current state
const int INCREMENT = 1;         // for readabiity using function to change selected item up
const int DECREMENT = -1;        // for readability using function to change selected item down
const int MENU_ITEMS = 2;        // number of buttons in menu

int selectableObjectsTotal = 0;

bool Menu::init()
{
    // std::cout << "entering menu state" << std::endl;

    GameObject *bg = new Background(); // use different background for menu -- to do -- change from game background
    objects.push_back(bg);             // add background to state objects list

    GameObject *txt1 = new Text("CA1 Raylib Application", {0, 0}, HEADING, true, WHITE);
    objects.push_back(txt1);
    objects.push_back((GameObject *)(new Text("by Joe O'Regan (D00262717)", {0, 570}, SUB_HEADING, true, WHITE)));
    Text *flashText = new Text("Press Enter to Start", {100, 635}, HEADING, true, WHITE); // needs to be Text then cast to GameObject later to set flashing
    flashText->setFlashing(true);                                                         // use Text objects setFlashing function before casting to GameObject
    objects.push_back((GameObject *)flashText);                                           // Push to menu objects list as GameObject
    GameState::init();                                                                    // initialise objects in object list

    // add buttons
    m_menuOption = 0; // 1st button in list of selectable objects is selected by default
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.2f, 60, SCREEN_WIDTH * 0.6f, 50}, "Start Game")));
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.2f, 120, SCREEN_WIDTH * 0.6f, 50}, "Exit")));

    selectableObjectsTotal = selectableObjects.size(); // calculate once

    // initialise buttons
    for (GameObject *obj : selectableObjects)
    {
        obj->init(); // initialise the selectable objects
    }

    return true; // successfully initialised -- to do -- check this, or make void function
}

void menuOptionChange(int &option, int amount)
{
    option += amount;
    if (option > MENU_ITEMS - 1)
    {
        option = 0;
    }
    else if (option < 0)
    {
        option = MENU_ITEMS - 1;
    }
}

void Menu::update(float deltaTime)
{
    // std::cout << "menu update" << std::endl;
    GameState::update(deltaTime); // update the menu objects

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
        std::cout << "up key pressed - option: " << m_menuOption << std::endl;
    }
    else if (Input::Instance()->down(DELAY))
    {
        // m_menuOption++;
        menuOptionChange(m_menuOption, INCREMENT);
        std::cout << "down key pressed - option: " << m_menuOption << std::endl;
    }
}

void Menu::draw()
{
    GameState::draw(); // render the menu objects

    // for (GameObject *obj : selectableObjects) // for every object in this state
    for (int i = 0; i < selectableObjectsTotal; i++) // for every object in this state
    {
        if (i == m_menuOption)
            (*selectableObjects[i]).setSelected(true);
        else
            (*selectableObjects[i]).setSelected(false);
        (*selectableObjects[i]).draw(); // render the object
    }
}

bool Menu::close()
{
    // std::cout << "exiting menu state" << std::endl;

    GameState::close(); // clear menu objects from memory

    return true; // successfully exited -- to do -- check this, or make void function
}