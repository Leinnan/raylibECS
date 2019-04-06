#include "raylib.h"
#include "systems/AiSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/DestroySystem.hpp"
#include "systems/MissileSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/PlayerInputSystem.hpp"
#include "systems/RenderSystem.hpp"
#include "utils/JsonParser.hpp"
#include <entt/entt.hpp>

using nlohmann::json;

const int screenWidth = 1024;
const int screenHeight = 600;

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

    Components::readFromFile(registry,"data/world.json");

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
