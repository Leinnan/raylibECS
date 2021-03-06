#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP
#include "raylib.h"
#include <entt/entity/registry.hpp>

namespace Systems {
class RenderSystem {
  public:
    RenderSystem(entt::registry<> &registry);
    void Update(entt::registry<> &registry, Camera &camera);
    void Shutdown(){};
    Vector3 getCameraPos(const Vector3 &pos, const float &angle, const Vector3 &cameraOffset);
    void LoadEntityTexture(entt::registry<> &registry, std::uint32_t entity);
    void UnloadEntityTexture(entt::registry<> &registry, std::uint32_t entity);

  private:
    Camera3D camera;
};
} // namespace Systems
  // Systems

#endif