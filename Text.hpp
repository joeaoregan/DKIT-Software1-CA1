/*
    Text.hpp
    08/11/2022

    Text class
    Draw Text on screen
*/

#ifndef TEXT_HPP
#define TEXT_HPP

#include "GameObject.hpp"

enum default_font_sizes
{
    HEADING = 36,
    SUB_HEADING = 24
};

class Text : public GameObject
{
public:
    // constructor
    Text(const char *text, Vector2 pos = {0, 0}, int fontSize = 0, bool centered = true, Colour unselectedColour = BLACK, Colour selectedColour = WHITE) : GameObject(TEXT)
    {
        m_text = text; // text to display
        if (fontSize == 0)
            m_fontSize = GetFontDefault().baseSize; // use default font size
        else
            m_fontSize = fontSize;             // use specified font size
        m_centered = centered;                 // center the text on screen width
        setPosition(pos);                      // position of text (overridden by centered)
        m_unselectedColour = unselectedColour; // colour of text when not selected
        m_selectedColour = selectedColour;     // colour of text when selected
        m_spacing = 1.0f;                      // spacing 1 by default

        m_flashing = false;  // text flashes
        m_framesCounter = 0; // frame count for flashing text

        init();
    }

    Text(const char *text, int fontSize) : Text(text)
    {
        m_fontSize = (float)fontSize;
    }
    ~Text(){}; // deconstructor

    void init();         // initialise objects
    void move();         // update objects
    void collisions() {} // check object collisions (no need here)
    void draw();         // render objects
    void destroy(){};    // clear objects from memory

    bool getFlashing() { return m_flashing; }            // is the text flashing
    void setFlashing(bool flash) { m_flashing = flash; } // flash the text

private:
    const char *m_text;        // text to display
    float m_fontSize;          // font size to use
    bool m_centered;           // is the text centered
    Colour m_unselectedColour; // colour when text is not selected
    Colour m_selectedColour;   // colour when text is selected
    float m_spacing;           // character spacing

    bool m_flashing;     // text is flashing
    int m_framesCounter; // time between flashes
};
#endif
