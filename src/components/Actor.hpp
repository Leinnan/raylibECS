#ifndef ACTOR_TAG_HPP
#define ACTOR_TAG_HPP

namespace Components {

enum class Activity { Idle, Walking };

struct Actor final {
    float speed = 15.f;
    Activity curAction = Activity::Idle;
};
} // namespace Components
  // Components

#endif