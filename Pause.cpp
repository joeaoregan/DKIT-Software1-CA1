/*
    Pause.cpp
    02/11/2022

    Pause state class
    Handle the Pause state
*/

#include "Pause.hpp"
#include "Game.hpp"

const int Pause::s_pauseID = PAUSE;
const int PAUSE_FONT_SIZE = 80;

bool Pause::init()
{
    GameState::init();
    std::cout << "Init pause state" << std::endl;

    txtPause = "Paused!!";

    txtPauseCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), txtPause, PAUSE_FONT_SIZE, 1).x / 2);

    return true;
}

void Pause::update()
{
    GameState::update();
}

void Pause::draw()
{
    GameState::draw();

    // DrawText("Paused!!!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 40, WHITE);
    // DrawText(txtPause, txtPauseCenter, SCREEN_HEIGHT / 2 - (PAUSE_FONT_SIZE / 2), PAUSE_FONT_SIZE, BLACK);
    DrawTextEx(Game::Instance()->getFont(), txtPause, {(float)txtPauseCenter, SCREEN_HEIGHT / 2 - (PAUSE_FONT_SIZE / 2)}, PAUSE_FONT_SIZE, 1, BLACK);
}

bool Pause::close()
{
    GameState::close();
    std::cout << "Close pause state" << std::endl;

    return true;
}