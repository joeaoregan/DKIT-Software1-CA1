/*
    BackgroundMenu.cpp
    Joe O'Regan
    20/10/2022

    inherits from Background
    seperate menu background
*/

#include "BackgroundMenu.hpp"
#include "Game.hpp"

const int SCROLL_SPEED = 1; // speed to scroll the background across the screen
int framesCounter = 0;

// GameObject is not a direct base
BackgroundMenu::BackgroundMenu()
{
    Image image = LoadImage("resources/Background720.png"); // image to use
    setTexture(image);                                      // use image to create texture
    UnloadImage(image);                                     // unload image once texture is created

    setPosition({0.0f, 0.0f});    // starting position
    setHeight(SCREEN_HEIGHT);     // image fills screen height
    setWidth(SCREEN_WIDTH);       // image fills screen width
    bg2X = getX() + SCREEN_WIDTH; // start point of 2nd image scrolling

    txtHeading = "CA1 Raylib Application";              // text heading
    txtSubheading1 = "By Joe O'Regan";                  // text sub heading 1
    txtSubheading2 = "D00262717";                       // text sub heading 2
    instructionMove = "Move with arrows and ASDW keys"; // instructions

    txtHeadingWidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), txtHeading, fontSizeHeading, 1).x / 2);            // center heading
    txtSubHeading1WidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), txtSubheading1, fontSizeSubheading, 1).x / 2); // center subheading 1
    txtSubHeading2WidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), txtSubheading2, fontSizeSubheading, 1).x / 2); // center subheading 2
    txtInstructionMove = (SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), instructionMove, fontSizeSubheading, 1).x / 2);       // center instructions

    txtPressEnter = "Press Enter To Play!";
    txtCenterPressEnter = (SCREEN_WIDTH / 2) - (MeasureTextEx(Game::Instance()->getFont(), txtPressEnter, fontSizeHeading, 1).x / 2); // center heading
}

BackgroundMenu::~BackgroundMenu() {}

void BackgroundMenu::init() {}

void BackgroundMenu::move()
{
    framesCounter++;

    setX(getX() - SCROLL_SPEED); // move first image
    bg2X -= SCROLL_SPEED;        // move 2nd image

    if (getX() <= -(SCREEN_WIDTH)) // check 1st image fully off screen to left
    {
        setX(SCREEN_WIDTH); // move 1st image off screen to right
    }
    if (bg2X <= -(SCREEN_WIDTH)) // check 2nd image fully off screen to left
    {
        bg2X = SCREEN_WIDTH; // move 2nd image off screen to right
    }
}

void BackgroundMenu::collisions() {}

void BackgroundMenu::draw()
{
    DrawTexture(getTexture(), getX(), 0, WHITE); // draw 1st background image
    DrawTexture(getTexture(), bg2X, 0, WHITE);   // draw 1st background image

    DrawTextEx(Game::Instance()->getFont(), txtHeading, {(float)txtHeadingWidthCenter, 200.0F}, fontSizeHeading, 1, BLACK);            // render heading
    DrawTextEx(Game::Instance()->getFont(), txtSubheading1, {(float)txtSubHeading1WidthCenter, 250.0F}, fontSizeSubheading, 1, BLACK); // render sub heading 1
    DrawTextEx(Game::Instance()->getFont(), txtSubheading2, {(float)txtSubHeading2WidthCenter, 300.0F}, fontSizeSubheading, 1, BLACK); // render sub heading 2
    DrawTextEx(Game::Instance()->getFont(), instructionMove, {(float)txtInstructionMove, 700.0F}, fontSizeSubheading, 1, BLACK);       // render instuctions

    if (((framesCounter / 30) % 2))
        DrawText(txtPressEnter, txtCenterPressEnter, (SCREEN_HEIGHT / 2) - (32 / 2), 32, LIGHTGRAY);
}

void BackgroundMenu::destroy() {}