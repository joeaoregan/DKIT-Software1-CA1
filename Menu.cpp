/*
    Menu.cpp
    20/10/2022

    Menu state class
*/

#include "Menu.hpp"
#include "BackgroundMenu.hpp"

const int Menu::s_menuID = MENU; // identify current state

bool Menu::init()
{
    // std::cout << "entering menu state" << std::endl;

    GameObject *bg = new BackgroundMenu(); // use different background for menu -- to do -- change from game background
    objects.push_back(bg);                 // add background to state objects list

    GameState::init(); // initialise objects in object list

    return true; // successfully initialised -- to do -- check this, or make void function
}

void Menu::update()
{
    GameState::update(); // update the menu objects
}

void Menu::draw()
{
    GameState::draw(); // render the menu objects
}

bool Menu::close()
{
    // std::cout << "exiting menu state" << std::endl;

    GameState::close(); // clear menu objects from memory

    return true; // successfully exited -- to do -- check this, or make void function
}