/*
    Joe O'Regan
    01/10/2022
*/

#include "Constants.h"
#include "Player.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Basic Movement - Joe O'Regan");

    Font fontRetro = LoadFont("resources/fonts/Retro.ttf");

    Player *player = new Player();

    int txtHeadingWidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(fontRetro, txtHeading, fontSizeHeading, 1).x / 2);
    int txtSubHeading1WidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(fontRetro, txtSubheading1, fontSizeSubheading, 1).x / 2);
    int txtSubHeading2WidthCenter = (SCREEN_WIDTH / 2) - (MeasureTextEx(fontRetro, txtSubheading2, fontSizeSubheading, 1).x / 2);
    int txtInstructionMove = (SCREEN_WIDTH / 2) - (MeasureTextEx(fontRetro, instructionMove, fontSizeSubheading, 1).x / 2);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        (*player).move();
        (*player).collisions();

        BeginDrawing();

        ClearBackground(WHITE);

        DrawTextEx(fontRetro, txtHeading, {(float)txtHeadingWidthCenter, 200.0F}, fontSizeHeading, 1, BLACK);
        DrawTextEx(fontRetro, txtSubheading1, {(float)txtSubHeading1WidthCenter, 250.0F}, fontSizeSubheading, 1, BLACK);
        DrawTextEx(fontRetro, txtSubheading2, {(float)txtSubHeading2WidthCenter, 300.0F}, fontSizeSubheading, 1, BLACK);
        DrawTextEx(fontRetro, instructionMove, {(float)txtInstructionMove, 700.0F}, fontSizeSubheading, 1, BLACK);

        DrawCircleV((*player).getPosition(), (*player).getHeight(), MAROON);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}