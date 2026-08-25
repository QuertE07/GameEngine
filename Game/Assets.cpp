#include "Assets.h"

using namespace gl;
namespace Assets
{
    Mesh body
    {
        { 
            Vector2{ 0, -5 },
            Vector2{ 2, -3 },
            Vector2{ 1, -2 },
            Vector2{ 2, -1 },
            Vector2{ 2, 3 },
            Vector2{ 0, 5 },
            Vector2{ -2, 3 },
            Vector2{ -2, -1 },
            Vector2{ -1, -2 },
            Vector2{ -2, -3 },
            Vector2{ 0, -5 }
        },
        Color{ 1.0f, 1.0f, 1.0f }
    };

    Mesh lWing1
    {
        {
            Vector2{ -2, -1 },
            Vector2{ -3, -4 },
            Vector2{ -6, -7 },
            Vector2{ -9, -8 },
            Vector2{ -10, -7 },
            Vector2{ -10, 0 },
            Vector2{ -9, 1 },
            Vector2{ -10, 2 },
            Vector2{ -8, 7 },
            Vector2{ -7, 8 },
            Vector2{-6, 8},
            Vector2{ -2, 3 }
        },
        Color{0.7f, 0.6f, 1.0f}
    };
    Mesh lWing2
    {
        {
            Vector2{ -2, -1 },
            Vector2{ -4, -8 },
            Vector2{ -5, -7 },
            Vector2{ -5, 0 },
            Vector2{ -4.5, 1.0f },
            Vector2{ -5, 2 },
            Vector2{ -4, 7 },
            Vector2{ -3, 8 },
            Vector2{ -2, 3 }
        },
        Color{0.7f, 0.6f, 1.0f}
    };

    Mesh rWing1
    {
        { Vector2{ 2, -1 }, Vector2{ 3, -4 }, Vector2{ 6, -7 }, Vector2{ 9, -8 }, Vector2{ 10, -7 }, Vector2{ 10, 0 },
                   Vector2{ 9, 1 }, Vector2{ 10, 2 }, Vector2{ 8, 7 }, Vector2{ 7, 8 }, Vector2{6, 8}, Vector2{ 2, 3 } }, Color{0.7f, 0.6f, 1.0f} };
    Mesh rWing2{ { Vector2{ 2, -1 }, Vector2{ 4, -8 }, Vector2{ 5, -7 }, Vector2{ 5, 0 }, Vector2{ 4.5, 1.0f }, Vector2{ 5, 2 }, Vector2{ 4, 7 }, Vector2{ 3, 8 }, Vector2{ 2, 3 } }, Color{0.7f, 0.6f, 1.0f} };

    Model frame1{ {body, lWing1, rWing1} };
    Model frame2{ {body, lWing2, rWing2} };

    AnimatedModel playerModel{ 3.0f, std::vector<Model>{ frame1, frame2 } };

    Mesh petal1
    {
        {
            Vector2{ 0, -2 },
            Vector2{ 0, -5 },
            Vector2{ 1, -6 },
            Vector2{ 4, -6 },
            Vector2{ 6, -4 },
            Vector2{ 6, -1 },
            Vector2{ 5, 0 },
            Vector2{ 2, 0 }
        },
        Color{0.7f, 0.6f, 1.0f}
    };

    Mesh petal2
    {
        {
            Vector2{ 0, -2 },
            Vector2{ 0, -5 },
            Vector2{ -1, -6 },
            Vector2{ -4, -6 },
            Vector2{ -6, -4 },
            Vector2{ -6, -1 },
            Vector2{ -5, 0 },
            Vector2{ -2, 0 }
        },
        Color{0.7f, 0.6f, 1.0f}
    };

    Mesh petal3
    {
        {
            Vector2{ 0, 2 },
            Vector2{ 0, 5 },
            Vector2{ -1, 6 },
            Vector2{ -4, 6 },
            Vector2{ -6, 4 },
            Vector2{ -6, 1 },
            Vector2{ -5, 0 },
            Vector2{ -2, 0 }
        },
        Color{0.7f, 0.6f, 1.0f}
    };

    Mesh petal4
    {
        {
            Vector2{ 0, 2 },
            Vector2{ 0, 5 },
            Vector2{ 1, 6 },
            Vector2{ 4, 6 },
            Vector2{ 6, 4 },
            Vector2{ 6, 1 },
            Vector2{ 5, 0 },
            Vector2{ 2, 0 }
        },
        Color{0.7f, 0.6f, 1.0f}
    };

    Mesh center
    {
        {
            Vector2{ -1, -2 },
            Vector2{ 1, -2 },
            Vector2{ 2, -1 },
            Vector2{ 2, 1 },
            Vector2{ 1, 2 },
            Vector2{ -1, 2 },
            Vector2{ -2, 1 },
            Vector2{ -2, -1 },
            Vector2{ -1, -2 }
        },
        Color{0.7f, 0.6f, 0.0f}
    };

    Model flower{ {petal1, petal2, petal3, petal4, center} };

    AnimatedModel flowerModel{ 0.0f, std::vector<Model>{flower} };
}