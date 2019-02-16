#include "MissileSystem.hpp"
#include "components/Missile.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"
#include "raymath.h"

namespace Systems{
void MissileSystem::Update(entt::registry<> &registry)
{
    registry.view<Components::Velocity, Components::Missile, Components::Transform>().each(
        [&](const auto, auto &vel, const auto &missile, auto& transform) {
        const auto &length = missile.speed * GetFrameTime();

        vel.angleChange = missile.angle - transform.angle;
        vel.movement = {std::cos(PI * missile.angle / 180.f) * length, 0.f,
                        std::sin(PI * missile.angle / 180.f) * length};
    });
}
}
