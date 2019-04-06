#include "components/Actor.hpp"
#include "components/BillboardRenderer.hpp"
#include "components/CameraTarget.hpp"
#include "components/Collisions.hpp"
#include "components/CylinderRenderer.hpp"
#include "components/DestroyAfterTime.hpp"
#include "components/MeshRenderer.hpp"
#include "components/Missile.hpp"
#include "components/Patrol.hpp"
#include "components/PlayerInput.hpp"
#include "components/RotatingObject.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"
#include "raylib.h"
#include "systems/AiSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/DestroySystem.hpp"
#include "systems/MissileSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/PlayerInputSystem.hpp"
#include "systems/RenderSystem.hpp"
#include "utils/JsonParser.hpp"
#include <cmath>
#include <entt/entt.hpp>
#include <json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using nlohmann::json;

const int screenWidth = 1024;
const int screenHeight = 600;
const float rotationSpeed = 68.f;

void createEmptyPlayer(entt::registry<> &reg) {
    auto entity = reg.create();
    reg.assign<Components::CameraTarget>(entity, Vector3{-10.f, 8.f, -10.f});
    reg.assign<Components::PlayerInput>(entity);
    reg.assign<Components::Velocity>(entity);
    reg.assign<Components::Transform>(entity, Vector3{70.f, 0.f, 0.f}, 0.f);
    reg.assign<Components::MeshRenderer>(entity,
                                         Components::MeshRenderer("data/gfx/knight.obj", "data/gfx/knight.png", 2.0f));
    reg.assign<Components::Collisions>(
        entity, Components::Collisions({Components::Collision(Vector3{0.f, 1.f, 0.f}, Vector3{0.8f, 2.0f, 0.8f})}));
}

void createPatrolBox(entt::registry<> &reg) {
    auto entity = reg.create();
    reg.assign<Components::Transform>(entity, Vector3{70.f, 0.f, -4.f}, 0.f);
    reg.assign<Components::Velocity>(entity);
    reg.assign<Components::Actor>(entity);
    reg.assign<Components::MeshRenderer>(entity,
                                         Components::MeshRenderer("data/gfx/knight.obj", "data/gfx/knight.png", 2.0f));

    std::vector<Vector3> points = {Vector3{30.f, 0.f, 0.f},  Vector3{40.f, 0.f, -2.f}, Vector3{50.f, 0.f, 1.0f},
                                   Vector3{75.f, 0.f, 0.f}, Vector3{77.f, 0.f, 4.f},  Vector3{75.f, 0.f, 0.f}};
    reg.assign<Components::Patrol>(entity, points, 3.f);
}

void createPart(entt::registry<> &reg, Vector3 pos) {
    auto entity = reg.create();
    reg.assign<Components::Transform>(entity, pos, 0.f);
    reg.assign<Components::MeshRenderer>(entity,
                                         Components::MeshRenderer("data/gfx/part.obj", "data/gfx/tilemap.png", 2.0f));
    reg.assign<Components::Collisions>(
        entity, Components::Collisions({Components::Collision(Vector3{0.f, 3.f, -4.2f}, Vector3{8.0f, 6.0f, 1.0f}),
                                        Components::Collision(Vector3{0.f, 3.f, 4.2f}, Vector3{8.0f, 6.0f, 1.0f})}));
}

void createCornerPart(entt::registry<> &reg, Vector3 pos) {
    auto entity = reg.create();
    reg.assign<Components::Transform>(entity, pos, 0.f);
    reg.assign<Components::MeshRenderer>(
        entity, Components::MeshRenderer("data/gfx/part_corner.obj", "data/gfx/tilemap.png", 2.0f));
    reg.assign<Components::Collisions>(
        entity, Components::Collisions({Components::Collision(Vector3{4.2f, 3.f, 4.0f}, Vector3{1.0f, 6.0f, 16.0f}),
                                        Components::Collision(Vector3{-8.0f, 3.f, -4.2f}, Vector3{24.0f, 6.0f, 1.0f}),
                                        Components::Collision(Vector3{-8.0f, 3.f, 8.2f}, Vector3{8.0f, 6.0f, 9.0f})}));
}

void createMissile(entt::registry<> &reg, float angle, Vector3 pos) {
    auto entity = reg.create();
    reg.assign<Components::Transform>(entity, pos, angle);
    reg.assign<Components::Velocity>(entity);
    reg.assign<Components::Missile>(entity, angle, 1.0f);
    reg.assign<Components::MeshRenderer>(entity,
                                         Components::MeshRenderer("data/gfx/star.obj", "data/gfx/knight.png", 2.0f));
    reg.assign<Components::DestroyAfterTime>(entity, 15.0f);
}

void createRotatingStar(entt::registry<> &reg, float angle, Vector3 pos) {
    auto entity = reg.create();
    reg.assign<Components::Transform>(entity, pos, angle);
    reg.assign<Components::Velocity>(entity);
    reg.assign<Components::RotatingObject>(entity, 40.0f);
    reg.assign<Components::MeshRenderer>(entity,
                                         Components::MeshRenderer("data/gfx/star.obj", "data/gfx/knight.png", 2.0f));
}

int main() {
    entt::registry registry;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Raylib tests");
    Systems::RenderSystem renderSystem(registry);
    Systems::PlayerInputSystem playerInputSystem;
    Systems::CollisionSystem collisionSystem(registry);
    Systems::MovementSystem movementSystem;
    Systems::DestroySystem destroySystem;
    Systems::AiSystem aiSystem(registry);
    Systems::MissileSystem missileSystem;

    createEmptyPlayer(registry);
    createPatrolBox(registry);

    for (int i = 0; i < 10; i++)
        createPart(registry, {-10.f + 8.0f * i, 0.f, 0.f});

    createCornerPart(registry, {78.0f, 0.f, 0.f});
    createMissile(registry, 20, {72.0f, 0.f, 0.f});
    createMissile(registry, 120, {72.0f, 0.f, 0.f});
    createMissile(registry, 220, {72.0f, 0.f, 0.f});
    createMissile(registry, 90, {72.0f, 0.f, 0.f});
    createMissile(registry, 160, {72.0f, 0.f, 0.f});
    createRotatingStar(registry, 5, {72.0f, 0.f, 0.f});

    Components::parseToFile(registry,"data/world.json");

    Camera camera = {0};
    camera.target = (Vector3){0.0f, 0.5f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;
    camera.position = {0.0f, 0.f, 0.0f};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        destroySystem.Update(registry);
        playerInputSystem.Update(registry);
        missileSystem.Update(registry);
        aiSystem.Update(registry, GetFrameTime());
        movementSystem.Update(registry);
        collisionSystem.Update(registry);
        renderSystem.Update(registry, camera);
    }

    CloseWindow();

    return 0;
}
