#pragma once

#include <vector>
#include "./raypath2d.h"
#include "./vector2d.h"

class Ray2D
{
public:
    /**
     * Traces the path of this ray as it interacts with a series of planes.
     * 
     * @param planes The planes with which the ray should interact.
     * @param maxBounces The maximum number of times the ray can bounce before ending the trace.
     * @param maxDistance The maximum total distance the ray can travel before ending the trace.
     * @return A path indicating the line segments traveled by the ray and the planes with which it interacted.
     */
    RayPath2D tracePath(const std::vector<Plane2D>& planes, int maxBounces = 1, int maxDistance = 1000) const;

private:
    bool rayIntersectsWithPlane(const Plane2D& plane) const;

    Vector2D startPosition_;
};