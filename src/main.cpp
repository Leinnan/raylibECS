#include "components/Actor.hpp"
#include "components/BillboardRenderer.hpp"
#include "components/CameraTarget.hpp"
#include "components/Collisions.hpp"
#include "components/CylinderRenderer.hpp"
#include "components/DestroyAfterTime.hpp"
#include "components/MeshRenderer.hpp"
#include "components/PlayerInput.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/DestroySystem.hpp"
#include "systems/MovementSystem.hpp"
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

void createEmptyPlayer(entt::registry<> &reg)
{
    auto entity = reg.create();
    reg.assign<Components::CameraTarget>(entity, Vector3{-10.f, 8.f, -10.f});
    reg.assign<Components::PlayerInput>(entity);
    reg.assign<Components::Velocity>(entity);
    reg.assign<Components::Transform>(entity, Vector3{70.f, 0.f, 0.f}, 0.f);
    reg.assign<Components::MeshRenderer>(entity, Components::MeshRenderer("data/gfx/knight.obj", "data/gfx/knight.png", 2.0f));
    reg.assign<Components::Collisions>(entity, Components::Collisions({Components::Collision(Vector3{0.f, 1.f, 0.f}, Vector3{0.8f, 2.0f, 0.8f})}));
}

void createPart(entt::registry<> &reg, Vector3 pos)
{
    auto entity = reg.create();
    reg.assign<Components::Transform>(entity, pos, 0.f);
    reg.assign<Components::MeshRenderer>(entity, Components::MeshRenderer("data/gfx/part.obj", "data/gfx/tilemap.png", 2.0f));
    reg.assign<Components::Collisions>(entity, Components::Collisions({Components::Collision(Vector3{0.f, 3.f, -4.2f}, Vector3{8.0f, 6.0f, 1.0f}),
                                                                       Components::Collision(Vector3{0.f, 3.f, 4.2f}, Vector3{8.0f, 6.0f, 1.0f})}));
}

void createCornerPart(entt::registry<> &reg, Vector3 pos)
{
    auto entity = reg.create();
    reg.assign<Components::Transform>(entity, pos, 0.f);
    reg.assign<Components::MeshRenderer>(entity, Components::MeshRenderer("data/gfx/part_corner.obj", "data/gfx/tilemap.png", 2.0f));
    reg.assign<Components::Collisions>(entity, Components::Collisions({Components::Collision(Vector3{4.2f, 3.f, 4.0f}, Vector3{1.0f, 6.0f, 16.0f}),
                                                                       Components::Collision(Vector3{-8.0f, 3.f, -4.2f}, Vector3{24.0f, 6.0f, 1.0f}),
                                                                       Components::Collision(Vector3{-8.0f, 3.f, 8.2f}, Vector3{8.0f, 6.0f, 9.0f})}));
}

int main()
{
    entt::registry registry;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Raylib tests");
    Systems::RenderSystem renderSystem(registry);
    Systems::PlayerInputSystem playerInputSystem;
    Systems::CollisionSystem collisionSystem(registry);
    Systems::MovementSystem movementSystem;
    Systems::DestroySystem destroySystem;

    createEmptyPlayer(registry);
    for (int i = 0; i < 10; i++)
        createPart(registry, {-10.f + 8.0f * i, 0.f, 0.f});
    
    createCornerPart(registry, {78.0f,0.f,0.f});

    Camera camera = {0};
    camera.target = (Vector3){0.0f, 0.5f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;
    camera.position = {0.0f, 0.f, 0.0f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        destroySystem.Update(registry);
        playerInputSystem.Update(registry);
        movementSystem.Update(registry);
        collisionSystem.Update(registry);
        renderSystem.Update(registry, camera);
    }

    CloseWindow();

    return 0;
}
