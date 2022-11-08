/*
    Joe O'Regan
    01/10/2022

    Main program entry point
*/

#include "Game.hpp"
#include "Audio.hpp"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Score - Joe O'Regan"); // initialise the game window
    InitAudioDevice();                                              // initialise the audio device
    Image icon = LoadImage("resources/joe.png");                    // load the window icon image
    SetWindowIcon(icon);                                            // set the window icon image
    SetExitKey(KEY_NULL);                                           // esc no longer exits game

    Game::Instance()->init(); // initialise game objects (starts in menu state) -- to do -- add splash screen

    Audio::Instance()->init(); // initialise audio device and objects

    SetRandomSeed(GetTime()); // seed for random numbers

    SetTargetFPS(60); // frame rate - 60 frames per second

    // while(Game::Instance->isRunning())

    while (!WindowShouldClose())
    {
        const float deltaTime{GetFrameTime()};
        Audio::Instance()->handleEvents(); // handle input events etc.
        Audio::Instance()->update();       // update music buffer with new stream data

        Game::Instance()->handleEvents();    // handle input events etc.
                                             // if (!Game::Instance()->isPaused())
        Game::Instance()->update(deltaTime); // update game objects

        BeginDrawing(); // start rendering
        // ClearBackground(WHITE);   // clear the screen before rendering the next frame
        Game::Instance()->draw(); // render game objects
        EndDrawing();             // finish rendering
    }

    Game::Instance()->close();  // clear game objects from memory
    Audio::Instance()->close(); // close audio device & clear music stream buffers from RAM

    CloseAudioDevice(); // close the audio device
    CloseWindow();      // close the game window

    return 0;
}