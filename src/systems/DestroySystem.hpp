#ifndef DESTROY_SYSTEM_HPP
#define DESTROY_SYSTEM_HPP
#include <entt/entt.hpp>

namespace Systems {
class DestroySystem {
  public:
    DestroySystem(){};
    void Update(entt::registry<> &registry);
    void Shutdown(){};
};
} // namespace Systems
  // Systems

#endif