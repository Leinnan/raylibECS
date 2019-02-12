#ifndef DESTROY_AFTER_TIME_HPP
#define DESTROY_AFTER_TIME_HPP

namespace Components
{
struct DestroyAfterTime final
{
    float timeLeft = 0.0f;
    DestroyAfterTime(float time) : timeLeft(time){}
};
} // namespace Components

#endif
