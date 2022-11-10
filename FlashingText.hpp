/*
    FlashingText.hpp
    10/11/2022

    Flashing text class
    Draw flashing text on screen
*/

#ifndef FLASH_TEXT_HPP
#define FLASH_TEXT_HPP

#include "Text.hpp"

class FlashingText : public Text
{
public:
    FlashingText(const char *text, Vector2 pos = {0, 0}, int fontSize = 0, bool canHide = true, bool centered = true, Colour unselectedColour = WHITE, Colour selectedColour = BLACK) : Text(text, pos, fontSize, centered, unselectedColour, selectedColour)
    {
        setFlashing(true);   // does this one thing
        m_canHide = canHide; // ok, 2 things, need this for flashing text used outside of button descriptions
    }

    bool canHide() { return m_canHide; } // check if flashing text can be hidden

private:
    bool m_canHide; // text is used to describe a button action etc, so only displays when needed
};
#endif

typedef FlashingText FlashText; // Just can't be bothered typing FlashingText every time