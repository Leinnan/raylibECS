#include "CollisionSystem.hpp"
#include "components/Collisions.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

namespace Systems
{
    CollisionSystem::CollisionSystem(entt::registry<>& registry)
    {}

    void CollisionSystem::Update(entt::registry<> &registry)
    {
        auto colliders = registry.view<Components::Transform, Components::Collisions>();
        
        registry.view<Components::Transform, Components::Velocity, Components::Collisions>().each(
        [&](auto& ent, auto &transform, const auto &vel, const auto& collider) {
            const auto& box = collider.box;
            bool isColliding = false;
            
            for(auto& other : colliders)
            {
                if(other == ent)
                    continue;
                auto& otherBox = registry.get<Components::Collisions>(other);
                isColliding = CheckCollisionBoxes(box,otherBox.box);               
                if(isColliding)
                    break;
            }
            
            if(isColliding)
                transform.pos = vel.oldPos;
        });
    }
}