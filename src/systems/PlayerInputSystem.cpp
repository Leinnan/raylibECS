#include "PlayerInputSystem.hpp"

#include "components/PlayerInput.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"

#include <cmath>

namespace Systems
{

void PlayerInputSystem::Update(entt::registry<> &registry)
{
    registry.view<Components::Velocity, Components::PlayerInput, Components::Transform>().each(
        [&](const auto, auto &vel, const auto &playerInput, auto &transform) {
            vel.movement.x = 0.f;
            vel.movement.z = 0.f;

            const bool isLeft = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
            const bool isRight = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
            const bool isUp = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
            const bool isDown = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);

            transform.angle -= static_cast<int>(isLeft) * PLAYER_SPEED * 1.5f * GetFrameTime();
            transform.angle += static_cast<int>(isRight) * PLAYER_SPEED * 1.5f * GetFrameTime();
            vel.movement = getHorizontalMovement((isUp || isDown ? (isUp ? PLAYER_SPEED : -0.5f * PLAYER_SPEED) : 0.f) * GetFrameTime(), transform.angle);

            transform.pos.x += vel.movement.x;
            transform.pos.z += vel.movement.z;
        });
}

Vector3 PlayerInputSystem::getHorizontalMovement(const float &length, const float &angle)
{
    return {std::cos(PI * angle / 180.f) * length, 0.f, std::sin(PI * angle / 180.f) * length};
}
} // namespace Systems
