#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP
#include "components/Collisions.hpp"
#include <entt/entity/registry.hpp>

namespace Systems {
class CollisionSystem {
  public:
    CollisionSystem(entt::registry<> &registry);
    void Update(entt::registry<> &registry);
    void Shutdown(){};
    void PrepareCollisions(entt::registry<> &registry, std::uint32_t entity);

    BoundingBox BoundingBoxFromCollision(const Vector3 &pos, const Components::Collision &col) {
        return (BoundingBox){(Vector3){pos.x + col.offset.x - col.size.x / 2, pos.y + col.offset.y - col.size.y / 2,
                                       pos.z + col.offset.z - col.size.z / 2},
                             (Vector3){pos.x + col.offset.x + col.size.x / 2, pos.y + col.offset.y + col.size.y / 2,
                                       pos.z + col.offset.z + col.size.z / 2}};
    }
};
} // namespace Systems
  // Systems

#endif