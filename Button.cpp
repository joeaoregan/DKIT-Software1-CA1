/*
    Button.cpp
    08/11/2022

    Button class
    GUI buttons
*/

#include "Button.hpp"
#include "Game.hpp"

const float BTN_X = SCREEN_WIDTH * 0.2f;
const float BTN_W = SCREEN_WIDTH * 0.6f;

void Button::init()
{
    float fontSize = getHeight() * 0.75f; // height of text if 3/4s of button height
    float labelXPos = (SCREEN_WIDTH / 2.0f) - (MeasureTextEx(Game::Instance()->getFont(), m_label, fontSize, 1).x / 2);
    text = new Text(m_label, {labelXPos, getY() + (getHeight() * 0.125f)}, fontSize, true, m_labelColour);
}

void Button::draw()
{
    DrawRectangleRounded({getX(), getY(), (float)getWidth(), (float)getHeight()}, m_roundness, m_segments, m_bgColour);
    DrawRectangleRoundedLines({getX(), getY(), (float)getWidth(), (float)getHeight()}, m_roundness, m_segments, m_lineThickness, m_lineColour);
    text->draw();
}