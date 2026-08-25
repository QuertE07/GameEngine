#pragma once
#include "Serialization/Json.h"
#include "Vector2.h"

namespace gl
{
    struct Transform
    {
        Vector2 position{ 0.0f, 0.0f };
        float rotation{ 0.0f };
        float scale{ 0.0f };

        void Read(const json::value_t& value)
        {
            JSON_READ(value, position);
            JSON_READ(value, rotation);
            JSON_READ(value, scale);
        }
    };
}