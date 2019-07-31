#pragma once

#include <vector>
#include "./raypathsegment2d.h"

class RayPath2D
{
public:
    void addSegment(const Plane2D& path, const Plane2D& target, const float angleOfIncidence);

private:
    std::vector<RayPathSegment2D> pathSegments_;
};