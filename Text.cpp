/*
    Text.cpp
    08/11/2022

    Text class
    Draw Text on screen
*/
#include "Text.hpp"
#include "Game.hpp"

void Text::init()
{
    if (m_centered)
        setX((SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), m_text, m_fontSize, 1).x / 2));
}

void Text::move()
{
    if (m_flashing)
    {
        m_framesCounter++;
    }
}

void Text::draw()
{
    if (m_flashing)
    {
        if ((m_framesCounter / 30) % 2 == 0)
            DrawTextEx(Game::Instance()->getFont(), m_text, getPosition(), m_fontSize, m_spacing, m_colour);
        else
            (DrawRectangle(0, 600, 1280, 120, BLACK));
    }
    else
    {
        DrawTextEx(Game::Instance()->getFont(), m_text, getPosition(), m_fontSize, m_spacing, m_colour);
    }
}