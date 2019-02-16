#ifndef PLAYER_INPUT_SYSTEM_HPP
#define PLAYER_INPUT_SYSTEM_HPP
#include "raylib.h"
#include <entt/entt.hpp>

const float PLAYER_SPEED = 33.f; // TODO
                                 // MOVE
                                 // TO
                                 // ACTOR
                                 // COMPONENT

namespace Systems {
class PlayerInputSystem {
  public:
    PlayerInputSystem(){};
    void Update(entt::registry<> &registry);
    void Shutdown(){};
    Vector3 getHorizontalMovement(const float &length, const float &angle);
};
} // namespace Systems
  // Systems

#endif
