/*
    Joe O'Regan
    02/10/2022
*/

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "GameObject.hpp"

class Background : public GameObject
{
public:
    Background();
    ~Background();

    void init();
    void move();
    void collisions();
    void draw();
    void destroy();

    Font fontRetro = LoadFont("resources/fonts/Retro.ttf");

    const char *txtHeading;
    const char *txtSubheading1;
    const char *txtSubheading2;
    const char *instructionMove;

    int txtHeadingWidthCenter;
    int txtSubHeading1WidthCenter;
    int txtSubHeading2WidthCenter;
    int txtInstructionMove;
};

#endif