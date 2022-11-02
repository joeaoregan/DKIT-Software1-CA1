/*
    StatusBar.cpp
    Joe O'Regan
    01/11/2022

    StatusBar game object
*/
#include "StatusBar.hpp"

StatusBar::StatusBar(Rectangle rect, float percent) : GameObject("ExplosionBlood", {rect.x, rect.y, rect.width, rect.height}, false)
{
    percent = (percent > 1.f) ? 1.f : (percent < 0.f) ? 0.f
                                                      : percent; // make sure percent is between 0 and 1
    bgRect = rect;
    float newWidth = ((float)rect.width * percent);
    // float newX = rect.x + (rect.width - newWidth);
    fgRect = {
        rect.x,
        rect.y,
        newWidth,
        rect.height};
    setCollidable(false);
    m_percent = 1.0f;
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
    DrawRectangle(bgRect.x, bgRect.y, bgRect.width, bgRect.height, RED);
    DrawRectangle(fgRect.x, fgRect.y, fgRect.width * m_percent, fgRect.height, GREEN);
    DrawRectangleLines(bgRect.x, bgRect.y, bgRect.width, bgRect.height, BLACK);
}
void StatusBar::destroy() {}
