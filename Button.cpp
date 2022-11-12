/*
    Button.cpp
    08/11/2022

    Button class
    GUI buttons
*/

#include "Button.hpp"
#include "Game.hpp"
#include "Text.hpp"

const float BTN_X = SCREEN_WIDTH * 0.2f;
const float BTN_W = SCREEN_WIDTH * 0.6f;

void Button::init()
{
    float fontSize = getHeight() * 0.75f;                                                             // height of text if 3/4s of button height
    labelX = getCenterX() - (MeasureTextEx(Game::Instance()->getFont(), m_label, fontSize, 1).x / 2); // new centered on x position
    text = new Text(m_label, {labelX, getY() + (getHeight() * 0.125f)}, fontSize, false, m_labelColour);
}

void Button::draw()
{
    DrawRectangleRounded((*getRect()), m_roundness, m_segments, m_bgColour);
    DrawRectangleRoundedLines((*getRect()), m_roundness, m_segments, m_lineThickness, (isSelected()) ? m_selectedLineColour : m_unselectedLineColour);
    DrawRectangleLines((*getCollisionRect()).x, (*getCollisionRect()).y, (*getCollisionRect()).width, (*getCollisionRect()).height, YELLOW);
    drawCollisionRect(DEBUG_BUTTON);

    text->setSelected(isSelected()); // text highlighted when button selected
    text->draw();
}