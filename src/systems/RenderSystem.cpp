#include "RenderSystem.hpp"
#include "components/CameraTarget.hpp"
#include "components/CylinderRenderer.hpp"
#include "components/Transform.hpp"
#include <iostream>
#include <cmath>

namespace Systems
{
RenderSystem::RenderSystem(entt::registry<> &registry)
{
}

void RenderSystem::Update(entt::registry<> &registry, Camera& camera)
{
    registry.view<Components::Transform, Components::CameraTarget>().each([&](const auto,const auto transform, const auto& target)
    {
        camera.position = getCameraPos(transform.pos,transform.angle,target.offset);
        camera.target = transform.pos;
    });

    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    BeginMode3D(camera);
    registry.view<Components::CylinderRenderer, Components::Transform>().each([&](const auto, const auto& cylinder, const auto &transform) {
        DrawCylinder(transform.pos, cylinder.radiusTop, cylinder.radiusBottom, cylinder.height,cylinder.sides, cylinder.color);
    });
    DrawGrid(10, 1.0f);
    DrawGizmo({0.f, 0.f, 0.f});
    EndMode3D();
    DrawText("Leinnan", 10, 10, 14, CLITERAL{230, 102, 1, 255});
    EndDrawing();
}

Vector3 RenderSystem::getCameraPos(const Vector3 &pos, const float &angle, const Vector3& cameraOffset)
{
     return {pos.x + std::cos(PI * angle / 180.f) * cameraOffset.x,
             pos.y + cameraOffset.y,
             pos.z + std::sin(PI * angle / 180.f) * cameraOffset.z};
}
} // namespace Systems
