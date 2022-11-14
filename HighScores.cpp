/*
    HighScores.cpp
    10/11/2022

    High score class
    Display the high scores
*/

#include "HighScores.hpp"   // header file for this class
#include "FlashingText.hpp" // flash top score
#include "Button.hpp"       // option 1. back to menu, option 2. clear scores -- todo - implement clear scores button
#include "InputHandler.hpp" // handle user input
#include "StateMachine.hpp" // FSM - change states
#include "Menu.hpp"         // return to menu state
#include <string>           // use strings to display scores

const game_state HighScores::s_highScoresID = HIGH_SCORES; // identify current state

enum menu_options // menu option ids
{
    SCORES_BACK = 0,  // Option 1. return to menu
    SCORES_CLEAR = 1, // Option 2. -- todo - clear scores
};

const int BUTTON_Y = SCREEN_HEIGHT * 0.7f;       // place the buttons 70% of the screen height
const float BUTTON_HEIGHT = 50.0f;               // button height
const float BUTTON_WIDTH = SCREEN_WIDTH * 0.2f;  // button width 20% of screen width
const float BUTTON_OFFSET = BUTTON_WIDTH / 2.0f; // offset the buttons to center on width

// Text *scores[4];
const int SCORE_START_POSITION = 80; // where to put first line of high scores text

// placeholder high scores
const char *scores[10] = {"1. Joe 10,000", "2. Derp 9,000", "3. Mark 8,000", "4. Jimmy 7,000", "5. Paul 6,000", "6. Jamie 5,000", "7. Emily 4,000", "8. Clara 3,000", "9. Katie 2,000", "10. Ava 1,000"};

/*
initialise high scores state
*/
bool HighScores::init()
{
    // add Flashing text
    flashingTextObjs.push_back(new FlashText("Return To Main Menu", {100, 635}, HEADING));    // option 1. return to main menu
    flashingTextObjs.push_back(new FlashText("Clear High Scores List", {100, 635}, HEADING)); // option 2. clear high scores
    flashingTextObjs.push_back(new FlashText(scores[0], {50, 65}, HEADING, false));           // Flash top score (needs to be added after buttons, so flashing info text at bottom works)

    // add buttons
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.75f - BUTTON_OFFSET, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT}, "Back")));  // Back to menu option - center on 3/4s of screen width
    selectableObjects.push_back((GameObject *)(new Button({SCREEN_WIDTH * 0.25f - BUTTON_OFFSET, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT}, "Clear"))); // Clear scores option - center on 1/4 of screen width

    GameState::init(); // initialise objects in object list

    // add plain text placeholder for non-top scores
    for (unsigned int i = 1; i < 10; i++) // for 9 place holder scores
    {
        objects.push_back((GameObject *)new Text(scores[i], {50, (float)(SCORE_START_POSITION + (40 * i))}, SUB_HEADING, true, WHITE)); // new line of scores text every 40 pixels
    }

    return true; // successfully initialised -- to do -- check this, or make void function
}

/*
 handle high scores state user input
*/
void HighScores::handleInput()
{
    GameState::handleInput(); // navigate menu items

    // action button
    if (Input::Instance()->select(DELAY)) // if action button pressed
    {
        switch (m_menuOption) // switch on current menu option
        {
        case SCORES_BACK:                                    // if option 1. return to menu option selected
            FSM::Instance()->change(new Menu());             // change to a new menu state
            break;                                           // exit switch
        case SCORES_CLEAR:                                   // if option 2. clear scores selected
            std::cout << "high scores cleared" << std::endl; // todo - actually clear scores
            break;                                           // exit switch
        }
    }
}

/*
update high scores state
*/
void HighScores::update(float deltaTime)
{
    // std::cout << "menu update" << std::endl;

    GameState::update(deltaTime); // update the menu objects
}

/*
render high scores state
*/
void HighScores::draw()
{
    ClearBackground(RED); // clear the screen before rendering the next frame
    GameState::draw();    // render the menu objects
}

/*
exit high scores state
*/
bool HighScores::close()
{
    GameState::close(); // clear menu objects from memory

    return true; // successfully exited -- to do -- check this, or make void function
}