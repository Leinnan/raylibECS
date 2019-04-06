#include "systems/AiSystem.hpp"
#include "components/Actor.hpp"
#include "components/Patrol.hpp"
#include "components/RotatingObject.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"
#include "raylib.h"
#include "raymath.h"
#include "utils/Arkona.hpp"

#include <iostream>

namespace Systems {
AiSystem::AiSystem(entt::registry<> &registry) {
    registry.construction<Components::Patrol>().connect<&Systems::AiSystem::PreparePatrolEntity>(this);
}

void AiSystem::Update(entt::registry<> &registry, const float &delta) {
    registry.view<Components::Velocity, Components::RotatingObject>().each(
        [&](const auto, auto &vel, const auto &rotObject) { vel.angleChange = rotObject.rotationSpeed * delta; });

    registry.view<Components::Transform, Components::Velocity, Components::Patrol, Components::Actor>().each(
        [&](const auto, auto &transform, auto &vel, auto &patrol, auto &actor) {
            vel.movement.x = 0.f;
            vel.movement.z = 0.f;
            vel.movement.y = 0.f;
            vel.angleChange = 0.f;
            if (patrol.curPart == Components::PatrolPart::Waiting) {
                patrol.waitedTime += delta;
                if (patrol.waitedTime > patrol.waitTime) {
                    actor.curAction = Components::Activity::Walking;
                    patrol.curPart = Components::PatrolPart::Walking;
                    patrol.curTarget++;
                    if (patrol.curTarget > patrol.points.size() - 1)
                        patrol.curTarget = 0;
                }
            } else if (patrol.curPart == Components::PatrolPart::Walking) {
                const auto &destPoint = patrol.points[patrol.curTarget];
                const auto &distance = Vector2Distance({transform.pos.x, transform.pos.z}, {destPoint.x, destPoint.z});
                const auto &finished = distance < 0.2f;
                if (finished) {
                    patrol.waitedTime = 0.0f;
                    patrol.curPart = Components::PatrolPart::Waiting;
                    actor.curAction = Components::Activity::Idle;
                }
                const auto &angle = Vector2Angle({transform.pos.x, transform.pos.z}, {destPoint.x, destPoint.z});
                const auto &length = actor.speed * GetFrameTime();

                const Vector3 movement{std::cos(PI * angle / 180.f) * length, 0.f,
                                       std::sin(PI * angle / 180.f) * length};

                vel.angleChange = angle - transform.angle;
                vel.movement = movement;
            }
        });
}

void AiSystem::PreparePatrolEntity(entt::registry<> &registry, std::uint32_t entity) {
    auto &transform = registry.get<Components::Transform>(entity);
    const Components::Patrol &patrol = registry.get<Components::Patrol>(entity);

    if(patrol.points.size() <= 0)
        return;
    transform.pos.x = patrol.points[0].x;
    transform.pos.z = patrol.points[0].z;
    transform.pos.y = patrol.points[0].y;
}
} // namespace Systems
  // Systems
