#include "plane2d.h"

// @DefaultConstructor
Plane2D::Plane2D() : start_({0, 0}), end_({0, 0}) {}

// @CopyConstructor
Plane2D::Plane2D(const Plane2D &plane)
{
    this->start_ = plane.start();
    this->end_ = plane.end();
}

Plane2D::Plane2D(const float x1, const float y1, const float x2, const float y2)
{
    this->start_ = Vector2D(x1, y1);
    this->end_ = Vector2D(x2, y2);
}

Plane2D::Plane2D(const Vector2D& start, const Vector2D& end)
{
    this->start_ = Vector2D(start);
    this->end_ = Vector2D(end);
}

Plane2D::Plane2D(const Vector2D& start, const float angle, const float length)
{
    this->start_ = Vector2D(start);
    this->end_ = Vector2D::fromPolar(angle, length) + this->start_;
}

float Plane2D::angle() const
{
    // Return angle of end vector from start vector (i.e. angle of vector connecting the two points)
    Vector2D diff = this->end_ - this->start_;
    return diff.direction();
}

float Plane2D::length() const
{
    // Return the length of the difference of the vectors describing the plane
    Vector2D difference = this->end_ - this->start_;
    return difference.magnitude();
}

float Plane2D::slope() const
{
    Vector2D planeVector = this->end_ - this->start_; // Translate vector of plane to origin

    // Determine the slope of the line (i.e. vector 3,9 has slope 1/3 (or y/x == 9/3))
	float slope = 0;
	if (planeVector.x != 0 && planeVector.y != 0)
	{
		slope = planeVector.y / planeVector.x;
	}

    return slope;
}

Vector2D Plane2D::start() const 
{
    return this->start_;
}

Vector2D Plane2D::end() const
{
    return this->end_;
}

Vector2D Plane2D::midpoint() const
{
    float midx;
    if (this->start_.x > this->end_.x)
    {
        midx = (this->start_.x - this->end_.x) / 2;
    }
    else
    {
        midx = (this->end_.x - this->start_.x) / 2;
    }
    float midy; 
    if (this->start_.y > this->end_.y)
    {
        midy = (this->start_.y - this->end_.y) / 2;
    }
    else
    {
        midy = (this->end_.y - this->start_.y) / 2;
    }
    return Vector2D(midx, midy);
}

bool Plane2D::intersects(const Plane2D& plane) const 
{
    // Test orientation of two points of this plane with first point of target plane
    Vector2D::Orientation orientation1 = Vector2D::orientation(this->start_, this->end_, plane.start_);
    Vector2D::Orientation orientation2 = Vector2D::orientation(this->start_, this->end_, plane.end_);

    // Planes intersect if orientations are different
    if (orientation1 != orientation2)
    {
        return true;
    }

    // Planes are perfectly colinear if both orientations are colinear
    if (orientation1 == Vector2D::Orientation::Colinear && orientation2 == Vector2D::Orientation::Colinear)
    {
        // TODO: Test if the colinear planes are overlapping (colinear planes might be separated)
        return true;
    }

    return false;
}
