#include "MovementSystem.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"

namespace Systems
{
    void MovementSystem::Update(entt::registry<> &registry)
    {
        registry.view<Components::Velocity,  Components::Transform>().each(
            [&](const auto, auto &vel, auto &transform) {
                vel.oldPos = transform.pos;
                transform.pos.x += vel.movement.x;
                transform.pos.z += vel.movement.z;
                transform.angle += vel.angleChange;
                
                vel.movement.x = 0.f;
                vel.movement.z = 0.f;
            });
    }
}
