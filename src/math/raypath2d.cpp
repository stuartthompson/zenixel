#include "raypath2d.h"
#include "raypathsegment2d.h"

void RayPath2D::addSegment(const Plane2D& path, const Plane2D& target, const float angleOfIncidence)
{
    this->pathSegments_.push_back(RayPathSegment2D({path, target, angleOfIncidence}));
}