#ifndef BILBOARD_RENDERER_HPP
#define BILBOARD_RENDERER_HPP
#include "raylib.h"
#include <string>

namespace Components
{
struct BillboardRenderer final
{
    const char *texturePath;
    float size = 1.0f;
    Color color = WHITE;
    Texture2D texture;

    BillboardRenderer(const char *path) : texturePath(path), size(1.0f), color(WHITE) {}
    BillboardRenderer(const char *path, const float& newSize, const Color& newColor) : texturePath(path), size(newSize), color(newColor) {}
};

} // namespace Components

#endif