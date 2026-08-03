#pragma once
#include "Vector2.h"

namespace gl
{
    struct Transform
    {
        Vector2 position;
        float rotation;
        float scale;
    };
}