/*
    Button.hpp
    08/11/2022

    Button class
    GUI buttons
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "GameObject.hpp"
#include "Text.hpp"

class Button : public GameObject
{
public:
    // constructor
    Button(Rectangle rect, const char *label = "btnLabel", Colour colour = MAROON) : GameObject(rect)
    {
        m_label = label;
        m_roundness = 0.15f;
        m_segments = 12;
        m_lineThickness = 1.5f;
        m_bgColour = colour;
        m_lineColour = WHITE;
        m_labelColour = WHITE;
    }

    ~Button(){}; // deconstructor

    void init();         // initialise objects
    void move(){};       // update objects
    void collisions() {} // check object collisions (no need here)
    void draw();         // render objects
    void destroy(){};    // clear objects from memory

    void initMenu()
    {
        setX(SCREEN_WIDTH * 0.2f);
        setWidth(SCREEN_WIDTH * 0.6f);
        setHeight(40);
    }

    void setLineColour(Colour colour)
    {
        m_lineColour = colour; // change line colour (button highlighted / selected etc.)
    }

private:
    const char *m_label;   // text label
    float m_roundness;     // rectangle roundness
    int m_segments;        // rectangle segments
    float m_lineThickness; // line thickness
    Colour m_bgColour;     // bag
    Colour m_lineColour;   // line colour
    Colour m_labelColour;  // label colour
    Text *text;            // Text label

    // bool isSelected{false};
};

#endif
