#pragma once

#include <zen-math.h>
#include "color.h"

struct Line2D
{
    Plane2D plane;
    Color color;
    bool showProps = false;
};
