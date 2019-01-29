#include "components/CameraTarget.hpp"
#include "components/CylinderRenderer.hpp"
#include "components/Transform.hpp"
#include "systems/RenderSystem.hpp"
#include "raylib.h"
#include <entt/entt.hpp>
#include <cmath>
#include <sstream>
#include <string>

const int screenWidth = 800;
const int screenHeight = 450;
const float cubeSpeed = 35.f;
const float rotationSpeed = 68.f;

Vector3 getHorizontalMovement(const float &length, const float &angle)
{
    return {std::cos(PI * angle / 180.f) * length, 0.f, std::sin(PI * angle / 180.f) * length};
}

void createEmptyPlayer(entt::registry<>& reg)
{
    auto entity = reg.create();
    reg.assign<Components::CameraTarget>(entity,Vector3{-10.f,5.f,-10.f});
    reg.assign<Components::Transform>(entity,Vector3{0.f,0.f,0.f},0.f);
    reg.assign<Components::CylinderRenderer>(entity,Components::CylinderRenderer{ 0.3f,0.4f,1.f,10,RED });
}

int main()
{
    entt::registry registry;
    InitWindow(screenWidth, screenHeight, "Raylib tests");
    Systems::RenderSystem renderSystem(registry);

    createEmptyPlayer(registry);
    Camera camera = {0};
    camera.target = (Vector3){0.0f, 0.5f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;
    Vector3 cubePosition = {0.0f, 0.50f, 0.0f};
    float angle = 0.f;
    camera.position = {0.0f, 0.f, 0.0f};

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

        renderSystem.Update(registry,camera);
    }

    CloseWindow();

    return 0;
}