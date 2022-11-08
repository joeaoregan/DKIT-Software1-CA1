/*
    StatusBar.cpp
    Joe O'Regan
    01/11/2022

    StatusBar game object
*/
#include "StatusBar.hpp"

StatusBar::StatusBar(Rectangle rect)
{
    bgRect = rect;

    setPosition({rect.x, rect.y});

    fgRect = {
        rect.x,
        rect.y,
        rect.width,
        rect.height};

    setCollidable(false);

    m_percent = 1.0f; // starting percent of foreground bar

    m_colourBG = RED;        // default background colour
    m_colourFG = GREEN;      // default foreground colour
    m_colourOutline = BLACK; // default outline colour
}

StatusBar::StatusBar(Rectangle rect, Colour bg, Colour fg, Colour o) : StatusBar(rect)
{
    m_colourBG = bg;
    m_colourFG = fg;
    m_colourOutline = o;
}

StatusBar::StatusBar(Rectangle rect, float percent) : StatusBar(rect)
{
    percent = (percent > 1.f) ? 1.f : (percent < 0.f) ? 0.f
                                                      : percent; // ensure percent between 0 and 1

    float newWidth = ((float)rect.width * percent);

    fgRect = {rect.x, rect.y, newWidth, rect.height};
}

void StatusBar::init() {}
void StatusBar::move()
{
    bgRect.x = getX();
    bgRect.y = getY();
    fgRect.x = getX();
    fgRect.y = getY();

    // float newWidth = ((float)fgRect.width * m_percent); // recursive
    // fgRect.width = newWidth;
}
void StatusBar::collisions() {}
void StatusBar::draw()
{
    DrawRectangle(bgRect.x, bgRect.y, bgRect.width, bgRect.height, m_colourBG);             // background
    DrawRectangle(fgRect.x, fgRect.y, fgRect.width * m_percent, fgRect.height, m_colourFG); // foreground
    DrawRectangleLines(bgRect.x, bgRect.y, bgRect.width, bgRect.height, m_colourOutline);   // outline
}
void StatusBar::destroy() {}
