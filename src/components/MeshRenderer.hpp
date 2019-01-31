#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP
#include "raylib.h"

namespace Components
{
struct MeshRenderer final
{
    const char *modelPath;
    Model model;
    const char *diffusePath;
    Texture2D diffuse;
    float scale;
    MeshRenderer(const char *modelPath, const char *diffusePath, const float& scale) : modelPath(modelPath), diffusePath(diffusePath), scale(scale) {};
};
} // namespace Components

#endif