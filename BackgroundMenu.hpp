/*
    BackgroundMenu.hpp
    Joe O'Regan
    20/10/2022

    inherits from Background
    seperate menu background
*/

#ifndef BACKGROUND_MENU_HPP
#define BACKGROUND_MENU_HPP

#include "Background.hpp"

class BackgroundMenu : public Background // Child class of Background
{
public:
    BackgroundMenu();  // constructor
    ~BackgroundMenu(); // deconstructor

    void init();       // initialise object
    void move();       // update the object
    void collisions(); // check collisions with other objects (not needed here)
    void draw();       // render the object
    void destroy();    // remove the object from memory

    const char *txtHeading;      // heading string
    const char *txtSubheading1;  // subheading string 1
    const char *txtSubheading2;  // subheading string 2
    const char *instructionMove; // instructions string

    int txtHeadingWidthCenter;     // heading center position, x
    int txtSubHeading1WidthCenter; // sub heading 1 center position, x
    int txtSubHeading2WidthCenter; // sub heading 2 center position, x
    int txtInstructionMove;        // instructions center position, x

    int bg2X; // starting position for 2nd background image
};

#endif