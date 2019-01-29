#include "raylib.h"
#include <entt/entt.hpp>
#include <cmath>
#include <sstream>
#include <string>

const int screenWidth = 800;
const int screenHeight = 450;
const Vector3 cameraOffset{-10.f, 5.0f, -10.0f};
const float cubeSpeed = 35.f;
const float rotationSpeed = 68.f;

Vector3 getCameraPos(const Vector3 &pos, const float &angle)
{

    return {pos.x + std::cos(PI * angle / 180.f) * cameraOffset.x,
            pos.y + cameraOffset.y,
            pos.z + std::sin(PI * angle / 180.f) * cameraOffset.z};
}

Vector3 getHorizontalMovement(const float &length, const float &angle)
{
    return {std::cos(PI * angle / 180.f) * length, 0.f, std::sin(PI * angle / 180.f) * length};
}

int main()
{

    InitWindow(screenWidth, screenHeight, "Raylib tests");

    Camera camera = {0};
    camera.target = (Vector3){0.0f, 0.5f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;
    Vector3 cubePosition = {0.0f, 0.50f, 0.0f};
    float angle = 0.f;
    camera.position = getCameraPos(cubePosition, angle);

    SetTargetFPS(60);
    SetCameraMode(camera, 0);
    while (!WindowShouldClose())
    {
        const bool isLeft = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
        const bool isRight = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
        const bool isUp = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
        const bool isDown = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);

        angle -= static_cast<int>(isLeft) * rotationSpeed * GetFrameTime();
        angle += static_cast<int>(isRight) * rotationSpeed * GetFrameTime();
        const Vector3 movement = getHorizontalMovement((isUp || isDown ? (isUp ? cubeSpeed : -cubeSpeed) : 0.f) * GetFrameTime(), angle);
        cubePosition.x += movement.x;
        cubePosition.z += movement.z;

        camera.position = getCameraPos(cubePosition, angle);
        camera.target = cubePosition;
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        BeginMode3D(camera);
        DrawCylinder(cubePosition, 0.3f, 0.4f, 1.f, 16, RED);
        DrawGrid(10, 1.0f);
        DrawGizmo({0.f, 0.f, 0.f});
        EndMode3D();
        DrawText("Leinnan", 10, 10, 14, CLITERAL{230, 102, 1, 255});
        EndDrawing();
    }

    CloseWindow();

    return 0;
}