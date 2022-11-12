/*
    GameState.cpp
    20/10/2022

    Game State class
    Base class for game state classes
*/

#include "GameState.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Pause.hpp"
#include "Exit.hpp"
#include "Background.hpp"

bool GameState::init()
{
    // add scrolling background if not pushed state
    if (!m_noBackground)
    {
        GameObject *bg = new Background(); // scrolling background
        objects.push_back(bg);             // add background to state objects list
    }

    objects.push_back(new Text("CA1 Raylib Application", {0, 0}, HEADING, true, WHITE)); // Add heading

    if (!(getStateID() != LEVEL_1 || getStateID() != LEVEL_2 || getStateID() != LEVEL_3)) // using this space to display the score
    {
        objects.push_back((GameObject *)(new Text("by Joe O'Regan (D00262717)", {0, 570}, SUB_HEADING, true, WHITE))); // Add Subheading
    }

    m_totalMenuItems = 0;     // clear loop totals
    m_totalFlashingItems = 0; // clear loop totals

    m_menuOption = 0; // first selectable object is highlighted by default

    for (GameObject *obj : objects) // for every object in this state
    {
        (*obj).init(); // initialise the objects
    }

    // selectable objects
    for (GameObject *btn : selectableObjects) // for every object in this state
    {
        (*btn).init(); // initialise the objects
    }
    m_totalMenuItems = selectableObjects.size(); // calculate once

    // flashing text
    for (FlashText *ft : flashingTextObjs) // for every object in this state
    {
        (*ft).init(); // initialise the objects
    }
    m_totalFlashingItems = flashingTextObjs.size(); // calculate once

    // std::cout << "total flashing text objects: " << m_totalFlashingItems << std::endl;
    // std::cout << "total selectable objects: " << m_totalMenuItems << std::endl;

    menuOptionChange(m_menuOption, 0); // don't change, highlights first button as selected

    return true; // return true if no errors (possibly no need if no raylib functions causing errors)
}

void GameState::handleInput()
{
    if (WindowShouldClose())
    {
        Game::Instance()->m_pStateMachine->push(new Exit());
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        switch (getStateID())
        {
        case PAUSE:
            // std::cout << "change to level state" << std::endl;
            // if (Game::Instance()->isPaused())
            // {
            //     Game::Instance()->setPaused(false);
            // Game::Instance()->m_pStateMachine->pop(); // back to game
            // }
            break;
        case MENU:
            Game::Instance()->m_pStateMachine->push(new Exit()); // show exit screen
            break;
        case LEVEL_1:
        case LEVEL_2:
        case LEVEL_3:
            std::cout << "change to pause state" << std::endl;
            if (!Game::Instance()->isPaused())
            {
                Game::Instance()->setPaused(true);
                Game::Instance()->m_pStateMachine->push(new Pause()); // pause
            }
            break;
        case HIGH_SCORES:
            Game::Instance()->m_pStateMachine->change(new Menu()); // Menu
            break;
        case EXIT_GAME:
            Game::Instance()->exitWindowRequested = true;
            break;
        default:
            break;
        }
    }

    // switch menu options
    if (Input::Instance()->up(DELAY))
    {
        menuOptionChange(m_menuOption, DECREMENT);
        std::cout << "up key pressed - option: " << m_menuOption << std::endl;
    }
    else if (Input::Instance()->down(DELAY))
    {
        menuOptionChange(m_menuOption, INCREMENT);
        std::cout << "down key pressed - option: " << m_menuOption << std::endl;
    }

    // Pause state uses left and right to change volume level
    if (getStateID() != PAUSE)
    {
        if (Input::Instance()->left(DELAY))
        {
            menuOptionChange(m_menuOption, DECREMENT);
            std::cout << "left key pressed - option: " << m_menuOption << std::endl;
        }
        else if (Input::Instance()->right(DELAY))
        {
            menuOptionChange(m_menuOption, INCREMENT);
            std::cout << "right key pressed - option: " << m_menuOption << std::endl;
        }
    }

    // mouse button pressed
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        std::cout << "mouse right-click" << std::endl;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        std::cout << "mouse left-click" << std::endl;
    }

    // mouse over buttons
    for (unsigned int i = 0; i < selectableObjects.size(); i++)
    {
        if (Input::Instance()->mouseOver((*selectableObjects[i]).getRect(), GetMousePosition()))
        {
            std::cout << "mouse over button : " << i << std::endl;
        }
    }
}

void GameState::update(float deltaTime)
{
    // regular objects
    for (GameObject *obj : objects) // for every object in this state
    {
        (*obj).move(); // update the objects
    }
    // selectable objects
    for (GameObject *btn : selectableObjects) // for every object in this state
    {
        (*btn).move(); // update the selectable objects
    }
    // flashing text
    for (FlashText *ft : flashingTextObjs) // for every object in this state
    {
        (*ft).move(); // update the flashing text objects
    }
}

void GameState::draw()
{
    for (GameObject *obj : objects) // for every object in this state
    {
        (*obj).draw(); // render the objects
    }

    // selectable objects / buttons etc
    for (int i = 0; i < m_totalMenuItems; i++) // for every object in this state
    {
        if (i == m_menuOption)
            (*selectableObjects[i]).setSelected(true); // highlight the current selected object
        else
            (*selectableObjects[i]).setSelected(false); // unselected object rendered differently
        (*selectableObjects[i]).draw();                 // render the object
    }

    // flashing text
    for (int i = 0; i < m_totalFlashingItems; i++)
    {
        if ((*flashingTextObjs[i]).canHide())
        {
            (*flashingTextObjs[i]).setActive(i == m_menuOption);
        }
        flashingTextObjs[i]->setFlashing(true);
        flashingTextObjs[i]->draw();
    }
}

bool GameState::close()
{
    // Regular objects
    for (GameObject *obj : objects) // for every object in this state
    {
        (*obj).destroy(); // clear object from memory
    }
    // flashing text
    for (FlashText *ft : flashingTextObjs) // for every object in this state
    {
        (*ft).destroy(); // clear object from memory
    }
    // selectable objects
    for (GameObject *btn : selectableObjects) // for every object in this state
    {
        (*btn).destroy(); // clear object from memory
    }

    objects.clear();
    flashingTextObjs.clear();
    selectableObjects.clear();

    return true;
}

void GameState::menuOptionChange(int &option, int amount)
{
    option += amount;

    if (option > m_totalMenuItems - 1)
    {
        option = 0;
    }
    else if (option < 0)
    {
        option = m_totalMenuItems - 1;
    }
}