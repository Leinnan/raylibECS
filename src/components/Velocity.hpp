#ifndef VELOCITY_HPP
#define VELOCITY_HPP
#include "raylib.h"

namespace Components
{
struct Velocity final
{
    Vector3 movement{0.f,0.f,0.f};
    Vector3 oldPos{0.f,0.f,0.f};
};
} // namespace Components

#endif