/*
    Joe O'Regan
    01/10/2022
*/

#include "Background.hpp"
#include "Player.hpp"
#include "BloodCell.hpp"

std::vector<GameObject *> objects;

const int NUM_BLOOD_CELLS = 15;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Basic Movement - Joe O'Regan");
    InitAudioDevice();

    SetRandomSeed(GetTime());

    SetTargetFPS(60);

    GameObject *player = new Player();
    GameObject *bg = new Background();
    objects.push_back(bg);
    objects.push_back(player);
    for (int i = 0; i < NUM_BLOOD_CELLS; i++)
    {
        GameObject *bc1 = new BloodCell();
        objects.push_back(bc1);
    }

    for (GameObject *obj : objects)
    {
        (*obj).init();
    }

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);

        for (GameObject *obj : objects)
        {
            (*obj).move();
            (*obj).collisions();
            (*obj).draw();
        }

        EndDrawing();
    }

    for (GameObject *obj : objects)
    {
        (*obj).destroy();
    }

    CloseAudioDevice();

    CloseWindow();

    return 0;
}