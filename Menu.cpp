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

const int Menu::s_menuID = MENU; // identify current state
const int INCREMENT = 1;         // for readabiity using function to change selected item up
const int DECREMENT = -1;        // for readability using function to change selected item down

int totalMenuItems = 0;     // number of buttons in menu
int totalFlashingItems = 0; // number of flashing text;

Text *flashText1;
Text *flashText2;
Text *flashText3;

std::vector<FlashText *> flashingTextObjs;

// enum menu_options
// {
//     START = 0,
//     HIGH_SCORES = 1,
//     QUIT_GAME = 2
// };

void menuOptionChange(int &option, int amount)
{
    option += amount;
    if (option > totalMenuItems - 1)
    {
        option = 0;
    }
    else if (option < 0)
    {
        option = totalMenuItems - 1;
    }

    // flashText1->setActive(option == START);
    // flashText2->setActive(option == HIGH_SCORES);
    // flashText3->setActive(option == QUIT_GAME);
    // for (int i = 0; i < totalFlashingItems; i++)
    // {
    //     (*flashingTextObjs[i]).setActive(i == option);
    // }
}

bool Menu::init()
{
    // std::cout << "entering menu state" << std::endl;

    GameObject *bg = new Background(); // use different background for menu -- to do -- change from game background
    objects.push_back(bg);             // add background to state objects list

    GameObject *txt1 = new Text("CA1 Raylib Application", {0, 0}, HEADING, true, WHITE);
    objects.push_back(txt1);
    objects.push_back((GameObject *)(new Text("by Joe O'Regan (D00262717)", {0, 570}, SUB_HEADING, true, WHITE)));

    // Flashing text
    flashingTextObjs.push_back(new FlashText("Press Enter to Start", {100, 635}, HEADING, true, WHITE)); // Push to menu objects list as GameObject
    flashingTextObjs.push_back(new FlashText("View High Scores", {100, 635}, HEADING, true, WHITE));
    flashingTextObjs.push_back(new FlashText("Press Enter to Quit", {100, 635}, HEADING, true, WHITE));

    GameState::init(); // initialise objects in object list

    // add buttons
    m_menuOption = 0; // 1st button in list of selectable objects is selected by default

    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.2f, 60, SCREEN_WIDTH * 0.6f, 50}, "Start Game")));
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.2f, 120, SCREEN_WIDTH * 0.6f, 50}, "High Scores")));
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.2f, 180, SCREEN_WIDTH * 0.6f, 50}, "Exit")));

    totalMenuItems = selectableObjects.size();    // calculate once
    totalFlashingItems = flashingTextObjs.size(); // calculate once

    // initialise buttons
    for (GameObject *obj : selectableObjects)
    {
        obj->init(); // initialise the selectable objects
    }

    menuOptionChange(m_menuOption, 0); // don't change, set flashing text

    return true; // successfully initialised -- to do -- check this, or make void function
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

    for (GameObject *obj : flashingTextObjs)
    {
        obj->move();
    }
}

void Menu::draw()
{
    ClearBackground(RED); // clear the screen before rendering the next frame
    // DrawRectangle(0, 600, 1280, 120, BLACK); // background for flashing text
    GameState::draw(); // render the menu objects

    // for (GameObject *obj : selectableObjects) // for every object in this state
    for (int i = 0; i < totalMenuItems; i++) // for every object in this state
    {
        if (i == m_menuOption)
            (*selectableObjects[i]).setSelected(true);
        else
            (*selectableObjects[i]).setSelected(false);
        (*selectableObjects[i]).draw(); // render the object
    }

    for (int i = 0; i < totalFlashingItems; i++)
    {
        (*flashingTextObjs[i]).setActive(i == m_menuOption);
        flashingTextObjs[i]->setFlashing(true);
        flashingTextObjs[i]->draw();
        // if (flashingTextObjs[i]->getFlashing())
        //     std::cout << "derp" << std::endl;
    }
}

bool Menu::close()
{
    // std::cout << "exiting menu state" << std::endl;

    GameState::close(); // clear menu objects from memory

    return true; // successfully exited -- to do -- check this, or make void function
}