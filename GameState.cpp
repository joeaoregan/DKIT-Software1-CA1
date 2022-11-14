/*
    GameState.cpp
    20/10/2022

    Game State class
    Base class for game state classes
*/

#include "GameState.hpp"    // header file for this class
#include "InputHandler.hpp" // handle user input
#include "Game.hpp"         // access game state machine
#include "Menu.hpp"         // Menu state
#include "Pause.hpp"        // Pause state
#include "Exit.hpp"         // confirm Exit state
#include "Background.hpp"   // Background -- common to almost all states, except transparent background states such as Pause

/*
    initialise game state
*/
bool GameState::init()
{
    // add scrolling background if not pushed state
    if (!m_noBackground) // if no background needed (such as Pause state)
    {
        GameObject *bg = new Background(); // scrolling background
        objects.push_back(bg);             // add background to state objects list
    }

    if (!(getStateID() == LEVEL_1 || getStateID() == LEVEL_2 || getStateID() == LEVEL_3)) // using this space to display the score in level
    {
        objects.push_back(new Text("CA1 Raylib Application", {0, 0}, HEADING, true, WHITE)); // Add heading
    }
    objects.push_back((GameObject *)(new Text("by Joe O'Regan (D00262717)", {0, 570}, SUB_HEADING, true, WHITE))); // Add Subheading -- todo if adding messages to game put back in if statement above

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

/*
    handle game state user input defaults
*/
void GameState::handleInput()
{
    if (WindowShouldClose()) // if the window exit button was pressed
    {
        Game::Instance()->getFSM()->push(new Exit()); // push the confirm exit state
    }

    if (IsKeyPressed(KEY_ESCAPE)) // if the escape key is pressed
    {
        switch (getStateID()) // switch on state id
        {
        case PAUSE: // if in the Pause state -- todo push back to Pause state as button pushes are moving between states
            // std::cout << "change to level state" << std::endl;
            // if (Game::Instance()->isPaused())
            // {
            //     Game::Instance()->setPaused(false);
            // Game::Instance()->getFSM()->pop(); // back to game
            // }
            break;
        case MENU:                                        // if in the Menu state
            Game::Instance()->getFSM()->push(new Exit()); // show exit screen
            break;
        case LEVEL_1:                                          // if in the level 1 state
        case LEVEL_2:                                          // if in the level 2 state
        case LEVEL_3:                                          // if in the level 3 state
            std::cout << "change to pause state" << std::endl; // todo -- figure out why button presses continuing through states
            if (!Game::Instance()->isPaused())                 // if the game is not paused
            {
                Game::Instance()->setPaused(true);             // set the game paused
                Game::Instance()->getFSM()->push(new Pause()); // push a new pause state
            }
            break;
        case HIGH_SCORES:                                   // if in the high scores state
            Game::Instance()->getFSM()->change(new Menu()); // change to menu state
            break;
        case EXIT_GAME:                                   // if in the confirm exit state
            Game::Instance()->exitWindowRequested = true; // exit the game
            break;
        default:
            break;
        }
    }

    // switch menu options
    if (Input::Instance()->up(DELAY)) // if the up key / button is pressed
    {
        menuOptionChange(m_menuOption, DECREMENT); // decrease the selected option index
        std::cout << "up key pressed - option: " << m_menuOption << std::endl;
    }
    else if (Input::Instance()->down(DELAY)) // if down key / button is pressed
    {
        menuOptionChange(m_menuOption, INCREMENT); // increase the selected option index
        std::cout << "down key pressed - option: " << m_menuOption << std::endl;
    }

    // Pause state uses left and right to change volume level
    if (getStateID() != PAUSE) // if not in the pause state
    {
        if (Input::Instance()->left(DELAY)) // if left key / button pressed
        {
            menuOptionChange(m_menuOption, DECREMENT); // change menu option down
            std::cout << "left key pressed - option: " << m_menuOption << std::endl;
        }
        else if (Input::Instance()->right(DELAY)) // if right key / button pressed
        {
            menuOptionChange(m_menuOption, INCREMENT); // change menu item up
            std::cout << "right key pressed - option: " << m_menuOption << std::endl;
        }
    }

    Input::Instance()->mouseSelect = false; // reset mouse select

    // mouse over buttons
    for (unsigned int i = 0; i < selectableObjects.size(); i++) // for each selectable object
    {
        if (Input::Instance()->mouseOver((*selectableObjects[i]).getRect(), GetMousePosition())) // if the mouse cursor is over a button
        {
            m_menuOption = i; // set this selectable object as highlighted
            // targetAcquired = true;
            // std::cout << "mouse over option: " << i << std::endl;
            Input::Instance()->mouseSelect = true; // button can be selected
            break;
        }
    }
    /*
        // mouse button pressed
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            // std::cout << "mouse right-click option: " << i << std::endl;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            std::cout << "mouse left-click option: " << m_menuOption << std::endl;
        }
        */
}

/*
    update the game state
*/
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

/*
    render the game state
*/
void GameState::draw()
{
    for (GameObject *obj : objects) // for every object in this state
    {
        (*obj).draw(); // render the objects
    }

    // selectable objects / buttons etc
    for (int i = 0; i < m_totalMenuItems; i++) // for every object in this state
    {
        if (i == m_menuOption)                          // if the button is the current menu option
            (*selectableObjects[i]).setSelected(true);  // highlight the current selected object
        else                                            // otherwise
            (*selectableObjects[i]).setSelected(false); // unselected object rendered differently
        (*selectableObjects[i]).draw();                 // render the object
    }

    // flashing text
    for (int i = 0; i < m_totalFlashingItems; i++) // for every flashing text object
    {
        if ((*flashingTextObjs[i]).canHide()) // if the flashing text object is hidden
        {
            (*flashingTextObjs[i]).setActive(i == m_menuOption); // set active if it is the current menu option
        }
        flashingTextObjs[i]->setFlashing(true); // set flashing true
        flashingTextObjs[i]->draw();            // render the flashing text object
    }
}

/*
    exit game state
*/
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

    objects.clear();           // clear the lists of regular objects
    flashingTextObjs.clear();  // clear the lists of flashing text objects
    selectableObjects.clear(); // clear the lists of menu item / selectable objects

    return true; // todo - only necessary if a check is rejected, and no checks
}

/*
    change the menu option
*/
void GameState::menuOptionChange(int &option, int amount) // the option index, and amount increments / decrements
{
    option += amount; // add the value of amount to the option

    if (option > m_totalMenuItems - 1) // if the end of the selectable objects list is reached
    {
        option = 0; // return to the first option
    }
    else if (option < 0) // if option decreases and the first option was selected
    {
        option = m_totalMenuItems - 1; // select the last button / item in the list
    }
}