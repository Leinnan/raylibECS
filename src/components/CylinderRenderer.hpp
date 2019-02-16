#ifndef CYLINDER_RENDERER_HPP
#define CYLINDER_RENDERER_HPP
#include "raylib.h"
namespace Components {
struct CylinderRenderer final {
    float radiusTop;
    float radiusBottom;
    float height;
    int sides;
    Color color;
};

} // namespace Components
  // Components

#endif