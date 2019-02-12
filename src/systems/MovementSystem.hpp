#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP
#include <entt/entt.hpp>

namespace Systems
{
    class MovementSystem
    {
        public:
            MovementSystem(){};
            void Update(entt::registry<> &registry);
            void Shutdown(){};
    };
}

#endif