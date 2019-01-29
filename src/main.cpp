#include "raylib.h"
#include <entt/entt.hpp>

const int screenWidth = 800;
const int screenHeight = 450;

int main()
{
    entt::registry registry;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello world!", 400, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
