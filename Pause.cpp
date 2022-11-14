/*
    Pause.cpp
    02/11/2022

    Pause state class
    Handle the Pause state
    display buttons to resume or exit game
    displays sliders for adjusting audio volumes
    displays status bar with current song track length
    can enter Exit state or resume Play state from here
*/

#include "Pause.hpp"        // this class header file
#include "Game.hpp"         // access pause, game state machine
#include "StatusBar.hpp"    // song time status bar
#include "Audio.hpp"        // audio volumes
#include "InputHandler.hpp" // handle user input
#include "Button.hpp"       // ui buttons
#include "Exit.hpp"         // exit state

const game_state Pause::s_pauseID = PAUSE; // state id

enum menu_options // ui menu options
{
    RESUME = 0,    // resume the game
    MUSIC_VOLUME,  // adjust music volume
    FX_VOLUME,     // adjust fx volume
    MASTER_VOLUME, // adjust master volume
    EXIT           // exit the game
};

const Rectangle menuButton = {50, 50, 350, 40}; // button dimensions
const Color volumeColour = {190, 33, 55, 100};  // colour for adjustable volume bar

/*
    Initialise the current state
*/
bool Pause::init()
{
    setNoBackground(); // No background used for this state

    objects.push_back((GameObject *)(new Text("Paused!!", {0, SCREEN_HEIGHT / 2}, 80, true, BLACK))); // game paused text

    audioBar = new StatusBar({40, SCREEN_HEIGHT - 100, 1200, 40}, RED, MAROON, BLACK); // create status bar to show song current play time
    objects.push_back(audioBar);                                                       // add to list of game objects

    txtSongTitle = Audio::Instance()->currentTrackName();                                                // get the title of the current playing song -- todo - update the title of current song
    objects.push_back((GameObject *)(new Text(txtSongTitle, {0, SCREEN_HEIGHT - 90}, 20, true, WHITE))); // game paused text

    selectableObjects.push_back((GameObject *)(new Button({menuButton.x, 50, menuButton.width, menuButton.height}, "Resume Game")));                 // Option 1. Resume game
    selectableObjects.push_back((GameObject *)(new Button({menuButton.x, 100, menuButton.width, menuButton.height}, "Music Volume", LIGHTGRAY)));    // Option 2. Music volume slider
    selectableObjects.push_back((GameObject *)(new Button({menuButton.x, 150, menuButton.width, menuButton.height}, "Sound FX Volume", LIGHTGRAY))); // Option 3. FX volume slider
    selectableObjects.push_back((GameObject *)(new Button({menuButton.x, 200, menuButton.width, menuButton.height}, "Master Audio", LIGHTGRAY)));    // Option 4. Master Audio slider
    selectableObjects.push_back((GameObject *)(new Button({menuButton.x, 250, menuButton.width, menuButton.height}, "Exit Game")));                  // Option 5. Exit game

    GameState::init(); // initialise the state
    return true;       // todo -- add confirmation of objects loaded etc.
}

/*
    Handle user input
*/
void Pause::handleInput()
{
    GameState::handleInput(); // Base class input handling

    if (Input::Instance()->select()) // If enter key is pressed
    {
        switch (m_menuOption) // switch on the current selected menu option
        {
        case RESUME:                                      // if resume option selected
            Game::Instance()->setPaused(false);           // unpause
            Game::Instance()->getFSM()->pop();            // resume the game
            break;                                        // exit switch
        case EXIT:                                        // if exit optoin selected
            Game::Instance()->getFSM()->push(new Exit()); // show confirm exit
            break;                                        // exit switch -- todo - check if this missing was the reason for input carrying over
        }
    }

    if (Input::Instance()->left(DELAY)) // left pressed on keyboard, gamepad or whatever is setup to control the game
    {
        std::cout << "left key pressed - option: " << m_menuOption << std::endl; // todo -- sort debug comments

        switch (m_menuOption) // action depends on current highlighted button
        {
        case MUSIC_VOLUME:                                   // if music volume slider is selected
            Audio::Instance()->setMusicVolume(VOLUME_DOWN);  // music volume down
            break;                                           // exit switch statement
        case FX_VOLUME:                                      // if fx volume slider is selected
            Audio::Instance()->setFXVolume(VOLUME_DOWN);     // fx volume down
            break;                                           // exit switch statement
        case MASTER_VOLUME:                                  // if master volume slider is selected
            Audio::Instance()->setMasterVolume(VOLUME_DOWN); // master volume down
            break;                                           // exit switch statement
        }
    }
    else if (Input::Instance()->right(DELAY)) // right pressed on keyboard, gamepad or whatever is setup to control the game
    {
        std::cout << "right key pressed - option: " << m_menuOption << std::endl;

        switch (m_menuOption) // action depends on current highlighted button
        {
        case MUSIC_VOLUME:                                 // if music volume slider is selected
            Audio::Instance()->setMusicVolume(VOLUME_UP);  // music volume down
            break;                                         // exit switch statement
        case FX_VOLUME:                                    // if fx volume slider is selected
            Audio::Instance()->setFXVolume(VOLUME_UP);     // fx volume down
            break;                                         // exit switch statement
        case MASTER_VOLUME:                                // if master volume slider is selected
            Audio::Instance()->setMasterVolume(VOLUME_UP); // master volume down
            break;                                         // exit switch statement
        }
    }
}

/*
    Update the current state
*/
void Pause::update(float deltaTime)
{
    // std::cout << "menu update" << std::endl;
    GameState::update(deltaTime); // update the menu objects in base games state class

    StatusBar *sb = static_cast<StatusBar *>(audioBar); // cast audiobar from GameObject to set percentage
    sb->setPercent(Audio::Instance()->timePlayed());    // show current song time
}

/*
    Render the current state
*/
void Pause::draw()
{
    DrawRectangle(0, SCREEN_HEIGHT - 160, 1280, 160, LIGHTGRAY); // clear bottom hud background before drawing other objects
    GameState::draw();                                           // render the menu objects

    musicWidth = menuButton.width * Audio::Instance()->getMusicVolume();   // get music volume
    fxWidth = menuButton.width * Audio::Instance()->getFXVolume();         // get fx volume
    masterWidth = menuButton.width * Audio::Instance()->getMasterVolume(); // get master volume

    DrawRectangleRec({menuButton.x, 100, musicWidth, menuButton.height}, volumeColour);  // draw adjustable music volume bar
    DrawRectangleRec({menuButton.x, 150, fxWidth, menuButton.height}, volumeColour);     // draw adjustable fx volume bar
    DrawRectangleRec({menuButton.x, 200, masterWidth, menuButton.height}, volumeColour); // draw adjustable master volume bar
}

/*
    Exit the current state
*/
bool Pause::close()
{
    std::cout << "pause state - close" << std::endl;
    GameState::close(); // clear game objects for this state in game state base class lists

    return true; // todo -- no checks performed this is redundants
}
