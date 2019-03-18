#ifndef MISSILESYSTEM_HPP
#define MISSILESYSTEM_HPP
#include <entt/entt.hpp>

namespace Systems {
class MissileSystem {
  public:
    MissileSystem(){};
    void Update(entt::registry<> &registry);
    void Shutdown(){};
};
} // namespace Systems
#endif // MISSILESYSTEM_HPP
