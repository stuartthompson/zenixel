#pragma once

#include "vector2d.h"

/**
 * Represents a plane in 2-dimensional space.
 * This is essentially a line.
 */
class Plane2D
{
public:
    /**
     * Initializes a 2D plane of zero length at the origin.
     */
    Plane2D();

    /**
     * Initializes a 2D plane from another plane.
     * 
     * @param plane The plane to initialize from.
     */
    Plane2D(const Plane2D& plane);

    /**
     * Initializes a 2D plane from two pairs of coordinates.
     */
    Plane2D(const float x1, const float y1, const float x2, const float y2);

    /**
     * Initializes a 2D plane from a pair of 2D vectors.
     * 
     * @param start A vector whose endpoint identifies the start of the plane.
     * @param end A vector whose endpoint identifies the end of the plane.
     */
    Plane2D(const Vector2D& start, const Vector2D& end);

    /**
     * Initializes a 2D plane from a start position, angle, and length.
     * 
     * @param start A vector whose endpoint identifies the start of the plane.
     * @param angle The angle of the plane.
     * @param length The length of the plane.
     */
    Plane2D(const Vector2D& start, const float angle, const float length);

    /**
     * Returns the angle of the vector this plane describes.
     */
    float angle() const;

    /**
     * Returns the length of this plane.
     */
    float length() const;

    /**
     * Returns the slope of this plane.
     */
    float slope() const;

    /**
     * Returns the vector describing the start of this plane.
     */
    Vector2D start() const;

    /**
     * Returns the vector describing the end of this plane.
     */
    Vector2D end() const;

    /**
     * Returns the midpoint of this plane.
     */
    Vector2D midpoint() const;

    /**
     * Tests if this plane intersects with another plane.
     * 
     * @param plane The plane to test for intersection.
     * @return True if the planes intersect.
     */
    bool intersects(const Plane2D& plane) const;

private:
    Vector2D start_;
    Vector2D end_;
};
