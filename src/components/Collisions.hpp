#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP
#include "raylib.h"

namespace Components
{
    BoundingBox boundingBoxFromPosition(const Vector3& pos, const Vector3& size, const Vector3& offset)
    {
        return (BoundingBox){(Vector3){ pos.x + offset.x - size.x/2, 
                                    pos.y + offset.y - size.y/2, 
                                    pos.z + offset.z - size.z/2 }, 
                        (Vector3){ pos.x + offset.x + size.x/2,
                                    pos.y + offset.y + size.y/2, 
                                    pos.z + offset.z + size.z/2 }};
    }

    struct Collisions final
    {
        BoundingBox box;
        Vector3 offset;
        Vector3 size;

        Collisions(Vector3 offset, Vector3 size) : offset(offset), size(size){};
    };
    
}

#endif