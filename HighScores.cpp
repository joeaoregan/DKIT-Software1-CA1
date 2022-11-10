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
const int SCORE_START_POSITION = 80; // where to put first line of high scores text
std::string score;

// placeholder high scores
const char *scores[10] = {"1. Joe 10,000", "2. Derp 9,000", "3. Mark 8,000", "4. Jimmy 7,000", "5. Paul 6,000", "6. Jamie 5,000", "7. Emily 4,000", "8. Clara 3,000", "9. Katie 2,000", "10. Ava 1,000"};

bool HighScores::init()
{
    // add scrolling background
    GameObject *bg = new Background(); // scrolling background
    objects.push_back(bg);             // add background to state objects list

    // add regular text
    objects.push_back((GameObject *)new Text("CA1 Raylib Application - High Scores", {0, 0}, HEADING, true, WHITE));
    objects.push_back((GameObject *)(new Text("by Joe O'Regan (D00262717)", {0, 570}, SUB_HEADING, true, WHITE)));

    // add plain text placeholder for non-top scores
    for (unsigned int i = 1; i < 10; i++)
    {
        objects.push_back((GameObject *)new Text(scores[i], {50, (float)(SCORE_START_POSITION + (40 * i))}, SUB_HEADING, true, WHITE)); // new line of scores text every 40 pixels
    }

    // add Flashing text
    flashingTextObjs.push_back(new FlashText("Return To Main Menu", {100, 635}, HEADING));
    flashingTextObjs.push_back(new FlashText("Clear High Scores List", {100, 635}, HEADING));
    flashingTextObjs.push_back(new FlashText(scores[0], {50, 65}, HEADING, false)); // Flash top score (needs to be added after buttons, so flashing info text at bottom works)

    // add buttons
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.75f, 500, SCREEN_WIDTH * 0.2f, 50}, "Back")));
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.25f, 500, SCREEN_WIDTH * 0.2f, 50}, "Clear")));

    GameState::init(); // initialise objects in object list

    return true; // successfully initialised -- to do -- check this, or make void function
}

void HighScores::update(float deltaTime)
{
    // std::cout << "menu update" << std::endl;

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
        menuOptionChange(m_menuOption, DECREMENT);
        std::cout << "up key pressed - option: " << m_menuOption << std::endl;
    }
    else if (Input::Instance()->down(DELAY) || Input::Instance()->right(DELAY))
    {
        menuOptionChange(m_menuOption, INCREMENT);
        std::cout << "down key pressed - option: " << m_menuOption << std::endl;
    }

    GameState::update(deltaTime); // update the menu objects
}

void HighScores::draw()
{
    ClearBackground(RED); // clear the screen before rendering the next frame
    GameState::draw();    // render the menu objects
}

bool HighScores::close()
{
    GameState::close(); // clear menu objects from memory

    return true; // successfully exited -- to do -- check this, or make void function
}