#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP
#include "raylib.h"
#include <vector>

namespace Components {

struct Collision final {
    Vector3 offset;
    Vector3 size;

    Collision(Vector3 offset, Vector3 size) : offset(offset), size(size) {}
};

struct Collisions final {
    std::vector<BoundingBox> boxes;
    std::vector<Collision> collisions;
    Collisions(std::vector<Collision> collisions) : collisions(collisions) {}
    Collisions(){}
};
} // namespace Components
  // Components

#endif