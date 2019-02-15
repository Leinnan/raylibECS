#ifndef AI_SYSTEM_HPP
#define AI_SYSTEM_HPP
#include <entt/entt.hpp>

namespace Systems
{
class AiSystem
{
  public:
    AiSystem(entt::registry<> &registry);
    void Update(entt::registry<> &registry, const float& delta);
    void Shutdown(){};
    void PreparePatrolEntity(entt::registry<> &registry, std::uint32_t entity);
};
} // namespace Systems

#endif