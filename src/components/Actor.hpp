#ifndef ACTOR_TAG_HPP
#define ACTOR_TAG_HPP

namespace Components
{
    
    enum class Activity
    {
        Idle,
        Walking
    };

    struct Actor final
    {
        Activity curAction = Activity::Idle;
        float speed = 20.f;
    };
}

#endif