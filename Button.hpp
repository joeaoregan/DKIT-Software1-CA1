/*
    Button.hpp
    08/11/2022

    Button class
    GUI buttons
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "GameObject.hpp"

class Button : public GameObject
{
public:
    // constructor
    Button(Rectangle rect, const char *label = "btnLabel", bool centered = true, Colour colour = MAROON) : GameObject(rect)
    {
        m_label = label;
        m_roundness = 0.15f;
        m_segments = 12;
        m_lineThickness = 1.5f;
        m_bgColour = colour;
        m_unselectedLineColour = BLACK;
        m_selectedLineColour = WHITE;
        m_labelColour = m_unselectedLineColour;
        m_centered = centered;

        // init();
    }

    ~Button(){}; // deconstructor

    void init();         // initialise objects
    void move(){};       // update objects
    void collisions() {} // check object collisions (no need here)
    void draw();         // render objects
    void destroy(){};    // clear objects from memory

private:
    const char *m_label;           // text label
    float m_roundness;             // rectangle roundness
    int m_segments;                // rectangle segments
    float m_lineThickness;         // line thickness
    Colour m_bgColour;             // bag
    Colour m_unselectedLineColour; // line colour when button is not selected
    Colour m_selectedLineColour;   // line colour when button is selected
    Colour m_labelColour;          // label colour
    GameObject *text;              // Text label
    bool m_centered;               // center button on position.x

    float labelX; // label x position
};

#endif
