#pragma once

#include "../zmath.h"
#include "./color.h"

struct Line2D
{
    Plane2D plane;
    Color color;
    bool showProps = false;
};
