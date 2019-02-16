#include "CollisionSystem.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

namespace Systems {
CollisionSystem::CollisionSystem(entt::registry<> &registry) {
    registry.construction<Components::Collisions>().connect<&CollisionSystem::PrepareCollisions>(this);
}

void CollisionSystem::Update(entt::registry<> &registry) {
    auto colliders = registry.view<Components::Transform, Components::Collisions>();

    registry.view<Components::Transform, Components::Velocity, Components::Collisions>().each(
        [&](auto &ent, auto &transform, const auto &vel, auto &collider) {
            collider.boxes.clear();
            for (const auto &col : collider.collisions) {
                collider.boxes.push_back(BoundingBoxFromCollision(transform.pos, col));
            }

            auto &boxes = collider.boxes;
            bool isColliding = false;

            for (auto &other : colliders) {
                if (other == ent)
                    continue;
                auto &otherBoxes = registry.get<Components::Collisions>(other).boxes;
                isColliding = std::any_of(otherBoxes.begin(), otherBoxes.end(), [&boxes](const BoundingBox &otherBox) {
                    return std::any_of(boxes.begin(), boxes.end(), [&otherBox](const BoundingBox &box) {
                        return CheckCollisionBoxes(box, otherBox);
                    });
                });
                if (isColliding)
                    break;
            }

            if (isColliding)
                transform.pos = vel.oldPos;
        });
}

void CollisionSystem::PrepareCollisions(entt::registry<> &registry, std::uint32_t entity) {
    if (registry.has<Components::Transform>(entity)) {
        auto &transform = registry.get<Components::Transform>(entity);
        auto &collider = registry.get<Components::Collisions>(entity);

        collider.boxes.clear();
        for (const auto &col : collider.collisions)
            collider.boxes.push_back(BoundingBoxFromCollision(transform.pos, col));
    }
}
} // namespace Systems
  // Systems