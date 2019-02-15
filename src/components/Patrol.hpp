#ifndef PATROL_HPP
#define PATROL_HPP
#include "raylib.h"
#include <vector>

namespace Components
{
enum class PatrolPart
{
    Waiting,
    Walking
};

struct Patrol final
{
    std::vector<Vector3> points;
    float waitTime = 1.0f;
    float waitedTime = 0.0f;
    PatrolPart curPart = PatrolPart::Waiting;
    int curTarget = 0;
};
} // namespace Components

#endif