#pragma once

#include "./plane2d.h"

/**
 * Represents a segment of a path traveled by a ray.
 */
struct RayPathSegment2D
{
    Plane2D pathSegment_; // The plane representing this segment of the ray's path
    Plane2D targetPlane_; // The plane on which the ray interacted to end this segment
    float angleOfIncidence_; // The angle of incidence of the plane interaction (angle of ray to plane normal)
};