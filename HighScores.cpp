/*
    HighScores.cpp
    10/11/2022

    High score class
    Display the high scores
*/

#include "HighScores.hpp"
#include "Background.hpp"
#include "FlashingText.hpp"
#include "Button.hpp"
#include "InputHandler.hpp"
#include "Game.hpp" // change states
#include "Menu.hpp"
#include <string>

const int HighScores::s_highScoresID = HIGH_SCORES; // identify current state

enum menu_options
{
    SCORES_BACK = 0,
    SCORES_CLEAR = 1,
};

// Text *scores[4];
const int SCORE_START_POSITION = 80;
std::string score;

const char *scores[10] = {"1. Joe 10,000", "2. Derp 9,000", "3. Mark 8,000", "4. Jimmy 7,000", "5. Paul 6,000", "6. Jamie 5,000", "7. Emily 4,000", "8. Clara 3,000", "9. Katie 2,000", "10. Ava 1,000"};

bool HighScores::init()
{
    GameObject *bg = new Background(); // scrolling background
    objects.push_back(bg);             // add background to state objects list

    objects.push_back((GameObject *)new Text("CA1 Raylib Application - High Scores", {0, 0}, HEADING, true, WHITE));
    objects.push_back((GameObject *)(new Text("by Joe O'Regan (D00262717)", {0, 570}, SUB_HEADING, true, WHITE)));

    // for (unsigned int i = 0; i < sizeof(scores); i++)
    for (unsigned int i = 0; i < 10; i++)
    {
        // std::string newStr = std::to_string(i + 1) + ". " + score + std::to_string(10000 - (100 * i));
        // std::string newStr = "derp";
        // score = std::to_string(i + 1) + ". " + score + std::to_string(10000 - (100 * i));
        // const char *scoreStr = score.c_str();
        objects.push_back((GameObject *)new Text(scores[i], {50, (float)(SCORE_START_POSITION + (40 * i))}, SUB_HEADING, true, WHITE));
    }

    // Flashing text
    flashingTextObjs.push_back(new FlashText("Return To Main Menu", {100, 635}, HEADING, true, WHITE));
    flashingTextObjs.push_back(new FlashText("Clear High Scores List", {100, 635}, HEADING, true, WHITE));

    GameState::init(); // initialise objects in object list

    // add buttons
    m_menuOption = 0; // 1st button in list of selectable objects is selected by default

    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.75f, 500, SCREEN_WIDTH * 0.2f, 50}, "Back")));
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.25f, 500, SCREEN_WIDTH * 0.2f, 50}, "Clear")));

    m_totalMenuItems = selectableObjects.size();    // calculate once
    m_totalFlashingItems = flashingTextObjs.size(); // calculate once

    // initialise buttons
    for (GameObject *obj : selectableObjects)
    {
        obj->init(); // initialise the selectable objects
    }

    menuOptionChange(m_menuOption, 0); // don't change, set flashing text

    return true; // successfully initialised -- to do -- check this, or make void function
}

void HighScores::update(float deltaTime)
{
    // std::cout << "menu update" << std::endl;
    GameState::update(deltaTime); // update the menu objects

    // action button
    if (Input::Instance()->select(DELAY))
    {
        switch (m_menuOption)
        {
        case SCORES_BACK:
            Game::Instance()->m_pStateMachine->change(new Menu());
            break;
        case SCORES_CLEAR:
            std::cout << "high scores cleared" << std::endl;
            break;
        }
    }

    // switch menu options
    if (Input::Instance()->up(DELAY) || Input::Instance()->left(DELAY))
    {
        // m_menuOption--;
        menuOptionChange(m_menuOption, DECREMENT);
        std::cout << "up key pressed - option: " << m_menuOption << std::endl;
    }
    else if (Input::Instance()->down(DELAY) || Input::Instance()->right(DELAY))
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

void HighScores::draw()
{
    ClearBackground(RED); // clear the screen before rendering the next frame
    // DrawRectangle(0, 600, 1280, 120, BLACK); // background for flashing text
    GameState::draw(); // render the menu objects

    // for (GameObject *obj : selectableObjects) // for every object in this state
    for (int i = 0; i < m_totalMenuItems; i++) // for every object in this state
    {
        if (i == m_menuOption)
            (*selectableObjects[i]).setSelected(true);
        else
            (*selectableObjects[i]).setSelected(false);
        (*selectableObjects[i]).draw(); // render the object
    }

    for (int i = 0; i < m_totalFlashingItems; i++)
    {
        (*flashingTextObjs[i]).setActive(i == m_menuOption);
        flashingTextObjs[i]->setFlashing(true);
        flashingTextObjs[i]->draw();
    }
}

bool HighScores::close()
{
    GameState::close(); // clear menu objects from memory

    return true; // successfully exited -- to do -- check this, or make void function
}