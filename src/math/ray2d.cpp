#include "ray2d.h"

RayPath2D Ray2D::tracePath(const std::vector<Plane2D>& planes, const int maxBounces, const int maxDistance) const
{
    Vector2D position = this->startPosition_;
    Vector2D lastBouncePosition = position;
    RayPath2D path = RayPath2D();

    // Trace the path of the ray and record interactions
    return path;
}