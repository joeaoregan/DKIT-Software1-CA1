/*
    Joe O'Regan
    02/10/2022
*/

#include "Background.hpp"

Background::Background()
{
    setPosition({0.0f, 0.0f});
    setHeight(SCREEN_HEIGHT);
    setWidth(SCREEN_WIDTH);

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

void Background::move()
{
}

void Background::collisions()
{
}

void Background::draw()
{
    DrawTextEx(fontRetro, txtHeading, {(float)txtHeadingWidthCenter, 200.0F}, fontSizeHeading, 1, BLACK);
    DrawTextEx(fontRetro, txtSubheading1, {(float)txtSubHeading1WidthCenter, 250.0F}, fontSizeSubheading, 1, BLACK);
    DrawTextEx(fontRetro, txtSubheading2, {(float)txtSubHeading2WidthCenter, 300.0F}, fontSizeSubheading, 1, BLACK);
    DrawTextEx(fontRetro, instructionMove, {(float)txtInstructionMove, 700.0F}, fontSizeSubheading, 1, BLACK);
}