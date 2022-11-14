/*
    Constants.hpp
    Joe O'Regan
    01/10/2022

    Game constants
*/
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Debug
const bool DEBUG_MODE = true;       // game is being debugged
const bool DEBUG_ALL = true;        // debug everything
const bool DEBUG_COLLISIONS = true; // test object collisions
const bool DEBUG_MESSAGE = true;    // debug messages
const bool DEBUG_WEAPONS = true;    // test weaposn are working

// Dimensions
const int SCREEN_WIDTH{1280}; // window width
const int SCREEN_HEIGHT{720}; // window height

// Text
const int fontSizeHeading{28};    // font size for headings
const int fontSizeSubheading{24}; // font size for sub headings

// level
const int NUM_BLOOD_CELLS = 15; // number of blood cells to appear on screen for level 1

#endif