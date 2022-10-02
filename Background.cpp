/*
    Joe O'Regan
    02/10/2022
*/

#include "Background.hpp"

const int SCROLL_SPEED = 2;

Background::Background()
{
    Image image = LoadImage("resources/Background720.png");
    setTexture(image);
    UnloadImage(image);

    setPosition({0.0f, 0.0f});
    setHeight(SCREEN_HEIGHT);
    setWidth(SCREEN_WIDTH);
    setX(0);
    bg2X = getX() + SCREEN_WIDTH;

    txtHeading = "CA1 Raylib Application";
    txtSubheading1 = "By Joe O'Regan";
    txtSubheading2 = "D00262717";
    instructionMove = "Move with arrows and ASDW keys";

    txtHeadingWidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(fontRetro, txtHeading, fontSizeHeading, 1).x / 2);
    txtSubHeading1WidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(fontRetro, txtSubheading1, fontSizeSubheading, 1).x / 2);
    txtSubHeading2WidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(fontRetro, txtSubheading2, fontSizeSubheading, 1).x / 2);
    txtInstructionMove = (SCREEN_WIDTH / 2) - (MeasureTextEx(fontRetro, instructionMove, fontSizeSubheading, 1).x / 2);
}

Background::~Background()
{
}

void Background::init()
{
}

void Background::move()
{
    setX(getX() - SCROLL_SPEED);
    bg2X -= SCROLL_SPEED;

    if (getX() <= -(SCREEN_WIDTH))
    {
        setX(SCREEN_WIDTH);
    }
    if (bg2X <= -(SCREEN_WIDTH))
    {
        bg2X = SCREEN_WIDTH;
    }
}

void Background::collisions()
{
}

void Background::draw()
{
    DrawTexture(getTexture(), getX(), 0, WHITE);
    DrawTexture(getTexture(), bg2X, 0, WHITE);

    DrawTextEx(fontRetro, txtHeading, {(float)txtHeadingWidthCenter, 200.0F}, fontSizeHeading, 1, BLACK);
    DrawTextEx(fontRetro, txtSubheading1, {(float)txtSubHeading1WidthCenter, 250.0F}, fontSizeSubheading, 1, BLACK);
    DrawTextEx(fontRetro, txtSubheading2, {(float)txtSubHeading2WidthCenter, 300.0F}, fontSizeSubheading, 1, BLACK);
    DrawTextEx(fontRetro, instructionMove, {(float)txtInstructionMove, 700.0F}, fontSizeSubheading, 1, BLACK);
}

void Background::destroy() {}