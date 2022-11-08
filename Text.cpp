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

void Text::draw()
{
    DrawTextEx(Game::Instance()->getFont(), m_text, getPosition(), m_fontSize, m_spacing, m_colour);
}