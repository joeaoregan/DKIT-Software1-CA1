/*
    Joe O'Regan
    01/10/2022
*/

#include "Background.hpp"
#include "Player.hpp"

std::vector<GameObject *> objects;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Basic Movement - Joe O'Regan");
    InitAudioDevice();

    SetTargetFPS(60);

    GameObject *player = new Player();
    GameObject *bg = new Background();
    objects.push_back(bg);
    objects.push_back(player);

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