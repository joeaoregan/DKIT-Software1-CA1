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
    FlashingText(const char *text, Vector2 pos = {0, 0}, int fontSize = 0, bool centered = true, Colour unselectedColour = BLACK, Colour selectedColour = WHITE) : Text(text, pos, fontSize, centered, unselectedColour, selectedColour)
    {
        setFlashing(true); // does this one thing
    }

    void draw()
    {
        Text::draw();
    }
};
#endif

typedef FlashingText FlashText; // Just can't be bothered typing FlashingText every time