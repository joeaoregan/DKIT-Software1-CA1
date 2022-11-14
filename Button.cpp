/*
    Button.cpp
    08/11/2022

    Button class
    GUI buttons
*/

#include "Button.hpp"
#include "Game.hpp"
#include "Text.hpp"

const float BTN_X = SCREEN_WIDTH * 0.2f; // constant for setting button x position
const float BTN_W = SCREEN_WIDTH * 0.6f; // constant for setting button y position

/*
    initialise the button object
*/
void Button::init()
{
    float fontSize = getHeight() * 0.75f;                                                             // height of text if 3/4s of button height
    labelX = getCenterX() - (MeasureTextEx(Game::Instance()->getFont(), m_label, fontSize, 1).x / 2); // new centered on x position
    text = new Text(m_label, {labelX, getY() + (getHeight() * 0.125f)}, fontSize, false, m_labelColour);
}

/*
    render the button object
*/
void Button::draw()
{
    DrawRectangleRounded((*getRect()), m_roundness, m_segments, m_bgColour);                                                                           // draw background rectangle
    DrawRectangleRoundedLines((*getRect()), m_roundness, m_segments, m_lineThickness, (isSelected()) ? m_selectedLineColour : m_unselectedLineColour); // draw a line around rectangle edge, used to highlight the button
    text->setSelected(isSelected());                                                                                                                   // text highlighted when button selected
    text->draw();                                                                                                                                      // render button label
    // drawCollisionRect(DEBUG_BUTTON);                                                                                                                   // show the collision rectangle for each button -- commented out, debug all flag is overriding
}

/*
    todo -- make slider class based on button, or add a rectangle before the text that can be set externally to show the volume up and down better in pause menu
*/