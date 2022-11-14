/*
    StatusBar.hpp
    Joe O'Regan
    01/11/2022
*/

#ifndef STATUS_BAR_HPP // if status bar class not defined
#define STATUS_BAR_HPP // ok to define

#include "GameObject.hpp" // base class header file

const bool DEBUG_STATUSBAR = true; // debug messages for status bar displayed

class StatusBar : public GameObject // StatusBar inherits directly from the GameObject base class
{
public:                                                                                                    // public members
    StatusBar(Rectangle rect, Colour bg = RED, Colour fg = GREEN, Colour o = BLACK, float percent = 1.0f); // constructor
    ~StatusBar(){};                                                                                        // destructor

    void init(){};       // heavy lifting done in constructor
    void move(){};       // update the object -- updated where called
    void collisions(){}; // not needed here
    void draw();         // render the object
    void destroy();      // clear the object

    inline float getPercent() const { return m_percent; }          // getter: percent of foreground rect to draw -- todo - use getter and setter in game object - maybe for health
    inline void setPercent(float percent) { m_percent = percent; } // setter: percent of foreground rect to draw

private:                                            // private members
    Rectangle bgRect, fgRect;                       // background and foreground rectangles
    float m_percent;                                // percentage to display of foreground rectangle
    Colour m_colourBG, m_colourFG, m_colourOutline; // foreground, background, and line colours
};                                                  // end of class
#endif                                              // end of definition