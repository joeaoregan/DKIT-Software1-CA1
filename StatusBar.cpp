/*
    StatusBar.cpp
    Joe O'Regan
    01/11/2022

    StatusBar game object
    draw 2 rectangle on top of each other
    with top rectangle displaying percentage e.g. player health bar
*/
#include "StatusBar.hpp" // this class header file

/*
    constructor passes rectangle to game object base class for constructor
    also takes colours for foreground, background, and line rectangles
    and the percentage of the foreground rect to draw (default 100%)
*/
StatusBar::StatusBar(Rectangle rect, Colour bg, Colour fg, Colour o, float percent) : GameObject(rect)
{
    bgRect = rect; // set background rectangle
    m_percent = (percent > 1.f) ? 1.f : (percent < 0.f) ? 0.f
                                                        : percent; // ensure percent between 0 and 1
    float newWidth = ((float)rect.width * m_percent);              // calculate foreground rectangle width
    fgRect = {rect.x, rect.y, newWidth, rect.height};              // set foredground width
    m_colourBG = bg;                                               // background colour (default red)
    m_colourFG = fg;                                               // foreground colour (default green)
    m_colourOutline = o;                                           // outline colour (default black)
}

/*
    render status bar
*/
void StatusBar::draw()
{
    DrawRectangle(getX(), getY(), getWidth(), getHeight(), m_colourBG);               // background
    DrawRectangle(getX(), getY(), fgRect.width * m_percent, getHeight(), m_colourFG); // foreground on top of background
    DrawRectangleLines(getX(), getY(), getWidth(), getHeight(), m_colourOutline);     // outline on top of both
}

/*
    destroy status bar
*/
void StatusBar::destroy()
{
    GameObject::destroy(); // call base class destroy method
}
