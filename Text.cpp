/*
    Text.cpp
    08/11/2022

    Text class
    Draw Text on screen
*/
#include "Text.hpp" // this class header file
#include "Game.hpp" // get font stored in game class -- todo - maybe move font here

/*
    initialise text
*/
void Text::init()
{
    if (m_centered)                                                                                           // if text is centered on screen width
        setX((SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), m_text, m_fontSize, 1).x / 2)); // get width of screen, and move x of text over half the width of text to center
}

/*
    update text
*/
void Text::move()
{
    if (m_flashing) // if text is flashing
    {
        m_framesCounter++; // update the frame counter for flashing animation
    }
}

/*
    render text
*/
void Text::draw()
{
    if (getActive()) // if the text is active
    {
        if (m_flashing) // if it is flashing
        {
            if ((m_framesCounter / 30) % 2 == 0) // every 2nd frame
            {
                DrawTextEx(Game::Instance()->getFont(), m_text, getPosition(), m_fontSize, m_spacing, m_unselectedColour); // render text using default font, font size, spacing, and colour
            }
        }
        else
        {
            DrawTextEx(Game::Instance()->getFont(), m_text, getPosition(), m_fontSize, m_spacing, (isSelected()) ? m_selectedColour : m_unselectedColour); // render text using highlighted colour if selected, or normal colour if unselected for menu buttons
        }
    }
}