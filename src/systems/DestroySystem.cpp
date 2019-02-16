#include "DestroySystem.hpp"
#include "components/DestroyAfterTime.hpp"

#include "raylib.h"

namespace Systems {
void DestroySystem::Update(entt::registry<> &registry) {
    const float frameTime = GetFrameTime();
    registry.view<Components::DestroyAfterTime>().each([&](const auto entity, auto &destroyAfterTime) {
        if (destroyAfterTime.timeLeft > 0.0f)
            destroyAfterTime.timeLeft -= frameTime;
        else
            registry.destroy(entity);
    });
}
} // namespace Systems
  // Systems
