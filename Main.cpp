/*
    Joe O'Regan
    01/10/2022

    Main program entry point
*/

#include "Game.hpp"

// Game *g_game = 0;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Score - Joe O'Regan"); // initialise the game window
    InitAudioDevice();                                              // initialise the audio device
    Image icon = LoadImage("resources/joe.png");                    // load the window icon image
    SetWindowIcon(icon);                                            // set the window icon image

    Game::Instance()->init(); // initialise game objects (starts in menu state) -- to do -- add splash screen

    SetRandomSeed(GetTime()); // seed for random numbers

    SetTargetFPS(60); // frame rate - 60 frames per second

    // while(Game::Instance->isRunning())

    while (!WindowShouldClose())
    {
        BeginDrawing(); // start rendering

        ClearBackground(WHITE); // clear the screen before rendering the next frame

        Game::Instance()->handleEvents(); // handle input events etc.
        Game::Instance()->update();       // update game objects
        Game::Instance()->draw();         // render game objects

        EndDrawing(); // finish rendering
    }

    Game::Instance()->close(); // clear game objects from memory

    CloseAudioDevice(); // close the audio device
    CloseWindow();      // close the game window

    return 0;
}