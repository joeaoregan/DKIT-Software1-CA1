/*
    Menu.cpp
    20/10/2022

    Menu state class
*/

#include "Menu.hpp"
#include "Background.hpp"
#include "Text.hpp"
#include "Button.hpp"

const int Menu::s_menuID = MENU; // identify current state

// struct Button
// {
//     Rectangle rect;
// };

bool Menu::init()
{
    // std::cout << "entering menu state" << std::endl;

    GameObject *bg = new Background(); // use different background for menu -- to do -- change from game background
    objects.push_back(bg);             // add background to state objects list
    GameObject *txt1 = new Text("CA1 Raylib Application", HEADING);
    objects.push_back(txt1);
    objects.push_back((GameObject *)(new Text("by Joe O'Regan (D00262717)", {0, 570}, SUB_HEADING)));
    objects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.2f, 60, SCREEN_WIDTH * 0.6f, 50}, "Start Game")));
    objects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.2f, 120, SCREEN_WIDTH * 0.6f, 50}, "Exit")));
    Text *flashText = new Text("Press Enter to Start", {100, 635}, HEADING);
    flashText->setFlashing(true);
    objects.push_back((GameObject *)flashText);

    GameState::init(); // initialise objects in object list

    return true; // successfully initialised -- to do -- check this, or make void function
}

void Menu::update(float deltaTime)
{
    // std::cout << "menu update" << std::endl;
    GameState::update(deltaTime); // update the menu objects
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