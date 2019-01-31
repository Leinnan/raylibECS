#include "components/BillboardRenderer.hpp"
#include "components/CameraTarget.hpp"
#include "components/CylinderRenderer.hpp"
#include "components/MeshRenderer.hpp"
#include "components/PlayerInput.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"
#include "systems/PlayerInputSystem.hpp"
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
    reg.assign<Components::PlayerInput>(entity);
    reg.assign<Components::Velocity>(entity);
    reg.assign<Components::Transform>(entity,Vector3{0.f,0.f,0.f},0.f);
    reg.assign<Components::MeshRenderer>(entity,Components::MeshRenderer("knight.obj","knight.png", 2.0f));
    //reg.assign<Components::BillboardRenderer>(entity,Components::BillboardRenderer("knight.png",3.f,WHITE));
    //reg.assign<Components::CylinderRenderer>(entity,Components::CylinderRenderer{ 0.3f,0.4f,1.f,10,RED });
}

void createPart(entt::registry<>& reg, Vector3 pos)
{
    auto entity = reg.create();
    reg.assign<Components::Transform>(entity,pos,0.f);
    reg.assign<Components::MeshRenderer>(entity,Components::MeshRenderer("part.obj","tilemap.png", 2.0f));
}

int main()
{
    entt::registry registry;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Raylib tests");
    Systems::RenderSystem renderSystem(registry);
    Systems::PlayerInputSystem playerInputSystem;

    createEmptyPlayer(registry);
    for(int i = 0; i < 10; i++)
        createPart(registry,{-10.f + 8.0f * i,0.f,0.f});

    Camera camera = {0};
    camera.target = (Vector3){0.0f, 0.5f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;
    camera.position = {0.0f, 0.f, 0.0f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        playerInputSystem.Update(registry);
        renderSystem.Update(registry,camera);
    }

    CloseWindow();

    return 0;
}