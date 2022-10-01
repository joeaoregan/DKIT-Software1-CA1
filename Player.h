/*
    Joe O'Regan
    01/10/2022
*/

#include "raylib.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
    Player();
    ~Player();

    void move();
    void collisions();
};