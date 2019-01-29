#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP
#include <entt/entt.hpp>
#include "raylib.h"

namespace Systems
{
    class RenderSystem
    {
        public:
            RenderSystem(entt::registry<> &registry);
            void Update(entt::registry<> &registry, Camera& camera);
            void Shutdown(){};
            Vector3 getCameraPos(const Vector3 &pos, const float &angle, const Vector3& cameraOffset);
            Vector3 getHorizontalMovement(const float &length, const float &angle);
        private:
            Camera3D camera;
    };
}

#endif