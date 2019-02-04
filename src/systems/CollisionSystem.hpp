#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP
#include <entt/entity/registry.hpp>

namespace Systems
{
    class CollisionSystem
    {
        public:
            CollisionSystem(entt::registry<> &registry);
            void Update(entt::registry<> &registry);
            void Shutdown(){};
    };
} // Systems


#endif