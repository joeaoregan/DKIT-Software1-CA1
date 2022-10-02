/*
    Joe O'Regan
    01/10/2022
*/

#include "Background.hpp"
#include "Player.hpp"
#include <vector>

std::vector<GameObject *> objects;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Basic Movement - Joe O'Regan");

    SetTargetFPS(60);

    GameObject *player = new Player();
    GameObject *bg = new Background();
    objects.push_back(bg);
    objects.push_back(player);

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

    CloseWindow();

    return 0;
}