/*
    Constants.hpp
    Joe O'Regan
    01/10/2022

    Game constants
*/
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Debug
const bool DEBUG_MODE = true;
const bool DEBUG_ALL = true;        // debug everything
const bool DEBUG_COLLISIONS = true; // test object collisions
const bool DEBUG_MESSAGE = true;    // debug messages
const bool DEBUG_WEAPONS = true;    // test weaposn are working

// Dimensions
const int SCREEN_WIDTH{1280};
const int SCREEN_HEIGHT{720};

// Text
const int fontSizeHeading{28};
const int fontSizeSubheading{24};

// level
const int NUM_BLOOD_CELLS = 15; // number of blood cells to appear on screen for level 1

#endif