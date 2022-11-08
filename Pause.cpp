/*
    Pause.cpp
    02/11/2022

    Pause state class
    Handle the Pause state
*/

#include "Pause.hpp"
#include "Game.hpp"
#include "StatusBar.hpp"
#include "Audio.hpp"
#include "inputHandler.hpp"

const int Pause::s_pauseID = PAUSE;
const int PAUSE_FONT_SIZE = 80;

const int MENU_ITEM_HEIGHT_DISTANCE = 50;
const int BUTTON_WIDTH = 350;
const int BUTTON_HEIGHT = 40;

GameObject *audioBar;
float timePlayed = 0.0f; // normalized time played

int txtSongTitleCenter;
const char *txtSongTitle;
// float volumeMusic = 1.0f;
// float volumeFX = 1.0f;
// float volumeMaster = 1.0f;
int menuOption = 0;
int menuOptionsTotal = 5; // number of enum values

const char *lbl1Resume = "Resume Game";
const char *lbl2MusicVol = "Music Volume";
const char *lbl3FXVol = "Sound FX Volume";
const char *lbl4MasterVol = "Master Audio";
const char *lbl5Exit = "Exit Game";
int lblCenter1{0};
int lblCenter2{0};
int lblCenter3{0};
int lblCenter4{0};
int lblCenter5{0};
int btnFontSize{0};

bool Pause::init()
{
    GameState::init();
    // std::cout << "Init pause state" << std::endl;
    btnFontSize = BUTTON_HEIGHT * 0.75f;

    lblCenter1 = (BUTTON_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), lbl1Resume, btnFontSize, 1).x / 2);
    lblCenter2 = (BUTTON_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), lbl2MusicVol, btnFontSize, 1).x / 2);
    lblCenter3 = (BUTTON_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), lbl3FXVol, btnFontSize, 1).x / 2);
    lblCenter4 = (BUTTON_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), lbl4MasterVol, btnFontSize, 1).x / 2);
    lblCenter5 = (BUTTON_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), lbl5Exit, btnFontSize, 1).x / 2);

    txtPause = "Paused!!";
    txtPauseCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), txtPause, PAUSE_FONT_SIZE, 1).x / 2);

    txtSongTitle = Audio::Instance()->currentTrackName();
    txtSongTitleCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), txtSongTitle, 20, 1).x / 2);

    // audioBar = new StatusBar({40, SCREEN_HEIGHT - 100, 1200, 20}, DARKGRAY, GRAY, WHITE);
    // audioBar = new StatusBar({40, SCREEN_HEIGHT - 100, 1200, 20});
    audioBar = new StatusBar({40, SCREEN_HEIGHT - 100, 1200, 40}, RED, MAROON, BLACK);
    objects.push_back(audioBar);

    return true;
}

void Pause::update(float deltaTime)
{
    // std::cout << "pause - update" << std::endl;
    GameState::update(deltaTime);
    // audioBar->setPercent(0.5f);
    handleInput();

    StatusBar *sb = static_cast<StatusBar *>(audioBar);
    sb->setPercent(Audio::Instance()->timePlayed());

    // std::cout << "pause update - time played: " << Audio::Instance()->timePlayed() << std::endl;
    // std::cout << "pause delta time: " << deltaTime << std::endl;
}

void Pause::handleInput()
{
    if (InputHandler::Instance()->isKeyDown(KEY_ENTER))
    {
        switch (menuOption)
        {
        case RESUME:
            Game::Instance()->changePauseState(); // resume the game
            break;
        }
    }

    // move up and down menu items
    if (InputHandler::Instance()->isKeyDownDelay(KEY_W) || InputHandler::Instance()->isKeyDownDelay(KEY_UP))
    {
        menuOption--;
        if (menuOption < 0)
        {
            menuOption = menuOptionsTotal - 1;
        }
        std::cout << "menu option down: " << menuOption << std::endl;
    }
    else if (InputHandler::Instance()->isKeyDownDelay(KEY_S) || InputHandler::Instance()->isKeyDownDelay(KEY_DOWN))
    {
        menuOption++;
        if (menuOption >= menuOptionsTotal)
        {
            menuOption = 0;
        }
        std::cout << "menu option up: " << menuOption << std::endl;
    }

    // adjust volumes
    if (InputHandler::Instance()->isKeyDownDelay(KEY_A) || InputHandler::Instance()->isKeyDownDelay(KEY_LEFT))
    {
        switch (menuOption)
        {
        case MUSIC_VOLUME:
            Audio::Instance()->setMusicVolume(VOLUME_DOWN);
            break;
        case FX_VOLUME:
            Audio::Instance()->setFXVolume(VOLUME_DOWN);
            break;
        case MASTER_VOLUME:
            Audio::Instance()->setMasterVolume(VOLUME_DOWN);
            break;
        }
    }
    else if (InputHandler::Instance()->isKeyDownDelay(KEY_D) || InputHandler::Instance()->isKeyDownDelay(KEY_RIGHT))
    {
        switch (menuOption)
        {
        case MUSIC_VOLUME:
            Audio::Instance()->setMusicVolume(VOLUME_UP);
            break;
        case FX_VOLUME:
            Audio::Instance()->setFXVolume(VOLUME_UP);
            break;
        case MASTER_VOLUME:
            Audio::Instance()->setMasterVolume(VOLUME_UP);
            break;
        }
    }
}

void Pause::draw()
{
    Rectangle menuButton = {50, 50, BUTTON_WIDTH, BUTTON_HEIGHT};

    for (int i = 0; i < menuOptionsTotal; i++)
    {
        // draw background for menu items
        menuButton.y += MENU_ITEM_HEIGHT_DISTANCE; // space 50 pixels apart
        DrawRectangleRec(menuButton, LIGHTGRAY);

        // draw status bars for volume levels, and label buttons
        if (i == RESUME)
        {
            DrawTextEx(Game::Instance()->getFont(), lbl1Resume, {menuButton.x + (float)lblCenter1, menuButton.y + ((menuButton.height - btnFontSize) / 2)}, btnFontSize, 1, (i == menuOption) ? BLACK : WHITE);
        }
        if (i == MUSIC_VOLUME)
        {
            float musicWidth = BUTTON_WIDTH * Audio::Instance()->getMusicVolume();
            DrawRectangleRec({menuButton.x, menuButton.y, musicWidth, menuButton.height}, MAROON);
            DrawTextEx(Game::Instance()->getFont(), lbl2MusicVol, {menuButton.x + (float)lblCenter2, menuButton.y + ((menuButton.height - btnFontSize) / 2)}, btnFontSize, 1, (i == menuOption) ? BLACK : WHITE);
        }
        if (i == FX_VOLUME)
        {
            float fxWidth = BUTTON_WIDTH * Audio::Instance()->getFXVolume();
            DrawRectangleRec({menuButton.x, menuButton.y, fxWidth, menuButton.height}, MAROON);
            DrawTextEx(Game::Instance()->getFont(), lbl3FXVol, {menuButton.x + (float)lblCenter3, menuButton.y + ((menuButton.height - btnFontSize) / 2)}, btnFontSize, 1, (i == menuOption) ? BLACK : WHITE);
        }
        if (i == MASTER_VOLUME)
        {
            float masterWidth = BUTTON_WIDTH * Audio::Instance()->getMasterVolume();
            DrawRectangleRec({menuButton.x, menuButton.y, masterWidth, menuButton.height}, MAROON);
            DrawTextEx(Game::Instance()->getFont(), lbl4MasterVol, {menuButton.x + (float)lblCenter4, menuButton.y + ((menuButton.height - btnFontSize) / 2)}, btnFontSize, 1, (i == menuOption) ? BLACK : WHITE);
        }
        if (i == EXIT)
        {
            DrawTextEx(Game::Instance()->getFont(), lbl5Exit, {menuButton.x + (float)lblCenter5, menuButton.y + ((menuButton.height - btnFontSize) / 2)}, btnFontSize, 1, (i == menuOption) ? BLACK : WHITE);
        }

        // highlight selected menu option
        if (i == menuOption) // only highlight selected option
        {
            DrawRectangleLinesEx(menuButton, 1.5f, BLACK);
        }
    }

    DrawRectangle(0, SCREEN_HEIGHT - 160, 1280, 160, LIGHTGRAY); // bottom hud background

    GameState::draw();

    // DrawText("Paused!!!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 40, WHITE);
    // DrawText(txtPause, txtPauseCenter, SCREEN_HEIGHT / 2 - (PAUSE_FONT_SIZE / 2), PAUSE_FONT_SIZE, BLACK);
    DrawTextEx(Game::Instance()->getFont(), txtPause, {(float)txtPauseCenter, SCREEN_HEIGHT / 2 - (PAUSE_FONT_SIZE / 2)}, PAUSE_FONT_SIZE, 1, BLACK); // game paused text
    DrawTextEx(Game::Instance()->getFont(), txtSongTitle, {(float)txtSongTitleCenter, SCREEN_HEIGHT - 90}, 20, 1, WHITE);                             // song title text
}

bool Pause::close()
{
    GameState::close();
    std::cout << "Close pause state" << std::endl;

    return true;
}