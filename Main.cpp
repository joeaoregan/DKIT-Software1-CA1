/*
    Joe O'Regan
    01/10/2022

    Main program entry point
    initialises window, audio and game class
    game loop
    close window, game, and audio
*/

#include "Game.hpp"  // game class header, singleton
#include "Audio.hpp" // audio class header, singleton

/*
main game entry point and game loop
*/
int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Antibody - Joe O'Regan"); // initialise the game window
    InitAudioDevice();                                                 // initialise the audio device
    Image icon = LoadImage("resources/joe.png");                       // load the window icon image
    SetWindowIcon(icon);                                               // set the window icon image
    SetExitKey(KEY_NULL);                                              // esc no longer exits game

    Audio::Instance()->init(); // initialise audio device and objects
    Game::Instance()->init();  // initialise game objects (starts in menu state) -- to do -- add splash screen

    SetRandomSeed(GetTime()); // seed for random numbers

    SetTargetFPS(60); // frame rate - 60 frames per second

    while (!Game::Instance()->exitWindowRequested)
    {
        const float deltaTime{GetFrameTime()};
        Audio::Instance()->handleEvents(); // handle input events etc.
        Audio::Instance()->update();       // update music buffer with new stream data

        Game::Instance()->handleEvents();    // handle input events etc.
        Game::Instance()->update(deltaTime); // update game objects

        BeginDrawing();           // start rendering -- ClearBackground(WHITE);   // clear the screen before rendering the next frame (not needed for transparent state overlay stuff)
        Game::Instance()->draw(); // render game objects
        EndDrawing();             // finish rendering
    }

    Game::Instance()->close();  // clear game objects from memory
    Audio::Instance()->close(); // close audio device & clear music stream buffers from RAM

    CloseAudioDevice(); // close the audio device
    CloseWindow();      // close the game window

    return 0; // function returns nothing
}