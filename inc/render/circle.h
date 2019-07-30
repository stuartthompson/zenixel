#pragma once

#include <zen-math.h>
#include "color.h"

struct Circle
{
    Circle(const Vector2D& center, const float radius, const Color color, const bool fill) : center(center), radius(radius), color(color), fill(fill) {}

    Vector2D center;
    float radius;
    Color color;
    bool fill;
};
