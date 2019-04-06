#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP
#include "raylib.h"
#include <string>

namespace Components {
struct MeshRenderer final {
    std::string modelPath;
    Model model;
    std::string diffusePath;
    Texture2D diffuse;
    float scale;

    MeshRenderer(const char *modelPath, const char *diffusePath, const float &scale)
        : modelPath(modelPath), diffusePath(diffusePath), scale(scale){};
    MeshRenderer(){};
};
} // namespace Components
  // Components

#endif