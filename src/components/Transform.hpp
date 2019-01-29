#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include "raylib.h"

namespace Components
{
struct Transform final
{
    Vector3 pos;
    float angle;
};
} // namespace Components

#endif