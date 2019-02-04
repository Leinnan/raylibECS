#include "RenderSystem.hpp"
#include "components/CameraTarget.hpp"
#include "components/CylinderRenderer.hpp"
#include "components/MeshRenderer.hpp"
#include "components/BillboardRenderer.hpp"
#include "components/Transform.hpp"
#include <iostream>
#include <cmath>

namespace Systems
{
RenderSystem::RenderSystem(entt::registry<> &registry)
{
    registry.construction<Components::BillboardRenderer>()
        .connect<&RenderSystem::LoadEntityTexture>(this);
    registry.destruction<Components::BillboardRenderer>()
        .connect<&RenderSystem::UnloadEntityTexture>(this);
    registry.construction<Components::MeshRenderer>()
        .connect<&RenderSystem::LoadEntityTexture>(this);
    registry.destruction<Components::MeshRenderer>()
        .connect<&RenderSystem::UnloadEntityTexture>(this);
}

void RenderSystem::Update(entt::registry<> &registry, Camera &camera)
{
    registry.view<Components::Transform, Components::CameraTarget>().each([&](const auto, const auto transform, const auto &target) {
        camera.position = getCameraPos(transform.pos, transform.angle, target.offset);
        camera.target = transform.pos;
    });

    BeginDrawing();
    ClearBackground({5, 5, 8, 255});
    BeginMode3D(camera);
    registry.view<Components::CylinderRenderer, Components::Transform>().each([&](const auto, const auto &cylinder, const auto &transform) {
        DrawCylinder(transform.pos, cylinder.radiusTop, cylinder.radiusBottom, cylinder.height, cylinder.sides, cylinder.color);
    });
    registry.view<Components::BillboardRenderer, Components::Transform>().each([&](const auto, const auto &billboard, const auto &transform) {
        DrawBillboard(camera, billboard.texture, transform.pos, billboard.size, billboard.color);
    });
    registry.view<Components::MeshRenderer, Components::Transform>().each([&](const auto, const auto &mesh, const auto &transform) {
        std::cout << "transform.angle: " << transform.angle << '\n';
        DrawModelEx(mesh.model, transform.pos, {0.f, -1.f, 0.f}, transform.angle, {mesh.scale, mesh.scale, mesh.scale}, WHITE);
    });
    EndMode3D();
    DrawText("Debug build", 10, 10, 12, CLITERAL{230, 102, 1, 255});
    EndDrawing();
}

Vector3 RenderSystem::getCameraPos(const Vector3 &pos, const float &angle, const Vector3 &cameraOffset)
{
    return {pos.x + std::cos(PI * angle / 180.f) * cameraOffset.x,
            pos.y + cameraOffset.y,
            pos.z + std::sin(PI * angle / 180.f) * cameraOffset.z};
}

void RenderSystem::LoadEntityTexture(entt::registry<> &registry, std::uint32_t entity)
{
    if (registry.has<Components::BillboardRenderer>(entity))
    {
        auto &billboard = registry.get<Components::BillboardRenderer>(entity);

        billboard.texture = LoadTexture(billboard.texturePath);
    }
    if (registry.has<Components::MeshRenderer>(entity))
    {
        auto &mesh = registry.get<Components::MeshRenderer>(entity);

        mesh.model = LoadModel(mesh.modelPath);
        mesh.diffuse = LoadTexture(mesh.diffusePath);
        mesh.model.material.maps[MAP_DIFFUSE].texture = mesh.diffuse;
    }
}

void RenderSystem::UnloadEntityTexture(entt::registry<> &registry, std::uint32_t entity)
{
    if (registry.has<Components::BillboardRenderer>(entity))
    {
        auto &billboard = registry.get<Components::BillboardRenderer>(entity);

        UnloadTexture(billboard.texture);
    }
    if (registry.has<Components::MeshRenderer>(entity))
    {
        auto &mesh = registry.get<Components::MeshRenderer>(entity);

        UnloadTexture(mesh.diffuse);
    }
}
} // namespace Systems
