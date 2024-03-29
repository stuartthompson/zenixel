#include <math.h>
#include <iostream>
#include "angle.h"
#include "vector2d.h"

// @DefaultConstructor
Vector2D::Vector2D() : x(0), y(0) {}

// @CopyConstructor
Vector2D::Vector2D(const Vector2D &vector)
{
    this->x = vector.x;
    this->y = vector.y;
}

// @Constructor
Vector2D::Vector2D(const float x, const float y)
{
    this->x = x;
    this->y = y; 
}

// @NamedConstructor
Vector2D Vector2D::fromPolar(const float direction, const float magnitude)
{
    // Since we know hypotenuse (magnitude) and angle (direction), we can use soh and cah from sohcahtoa
    //  (x): cos(a) = a/h  ==>  a = cos(a)*h
    //  (y): sin(a) = o/h  ==>  o = sin(a)*h

    float x = cos(direction) * magnitude; // x (width)
    float y = sin(direction) * magnitude; // y (height)
    return Vector2D(x, y);
}

// Assignment operators

Vector2D& Vector2D::operator=(const Vector2D& vector) {
    this->x = vector.x;
    this->y = vector.y;
    return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& vector) {
    this->x += vector.x;
    this->y += vector.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vector) {
    this->x -= vector.x;
    this->y -= vector.y;
    return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& vector) {
    this->x *= vector.x;
    this->y *= vector.y;
    return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& vector) {
    this->x /= vector.x;
    this->y /= vector.y;
    return *this;
}

// Arithmetic operators

Vector2D Vector2D::operator+(const Vector2D& vector) const {
    return Vector2D(this->x + vector.x, this->y + vector.y);
}

Vector2D Vector2D::operator-(const Vector2D& vector) const {
    return Vector2D(this->x - vector.x, this->y - vector.y);
}

Vector2D Vector2D::operator*(const Vector2D& vector) const {
    return Vector2D(this->x * vector.x, this->y * vector.y);
}

Vector2D Vector2D::operator/(const Vector2D& vector) const {
    return Vector2D(this->x / vector.x, this->y / vector.y);
}

// Query functions

float Vector2D::direction() const
{
    // When x is 0 then angle is either pi/2 (90) or 3pi/2 (270)
    if (this->x == 0)
    {
        if (this->y > 0)
        {
            return M_PI / 2; // Vector is pointing straight up (down in SDL coords) 
        }
        else
        {   
            return (3 * M_PI) / 2; // Vector is pointing straight down (up in SDL coords)
        }
    }

    // TODO: Quads matter here. Think about how the angle is affected in bottom-left.
    // Think carefully. Measuring from -y axis going left flips the o and a of the tri.

    // sohcahtoa - so tan(a) = o/a

    // Quads

    /*
                |
         Quad 2 | Quad 1
                |
        --------+--------
                |
         Quad 3 | Quad 4
                |
    
        Quad 1:   atan(y/x)
                |  /|
                | / |o(y)
                |/0 |
                +------
                 a(x)

        Quad 2:   atan(-x/y)
             o(x)
            -----
             \  |
              \0|a(y)
               \|
        --------+

        Quad 3:   atan(-y/-x)
             a(x)
        --------+
            | 0/|
        o(y)| / |
            |/  |
     
        Quad 4:   atan(x/-y)
                +--------
                |\
            a(y)|0\
                |  \
                -----
                  o(x)
     */


    // Quad 1: Top right
    if (this->x >= 0 && this->y >= 0)
    {
        return atan(this->y / this->x); // y is opposite in this quad
    }
    // Quad2 2: Top left
    if (this->x < 0 && this->y >= 0)
    {
        return atan(-this->x / this->y) + (M_PI / 2); // x is opposite in this quad (+ PI because first 90 degrees from quad 1)
    }
    // Quad 3: Bottom left
    if (this->x < 0 && this->y < 0)
    {
        return atan(-this->y / -this->x) + M_PI; // y is opposite (+ PI because first 180 from quad 1 and 2)
    }
    // Quad 4: Bottom right
    if (this-> x>= 0 && this->y < 0)
    {
        return atan(this->x / -this->y) + ((3*M_PI) / 2); // x is opposite
    }

    std::cerr << "Reached default case of vector2d.direction(). This should never happen." << std::endl;
    return 0;
}

float Vector2D::magnitude() const
{
    // Pythagorean theorem (a^2 + b^2 = c^2), therefore c = sqrt(a*a + b*b)
    return sqrt(this->x * this->x + this->y * this->y);
}

float Vector2D::distanceFrom(const Vector2D& vector) const {
    // Calculate the length of the difference of the vectors
    Vector2D diff = *this - vector;
    return diff.magnitude();
}

Vector2D::Orientation Vector2D::orientation(const Vector2D& p, const Vector2D& q, const Vector2D& r)
{
    int slopeDiff = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (slopeDiff == 0) 
    {
        // No slope difference so points line on same plane
        return Colinear;
    }
    else if (slopeDiff > 0)
    {
        // Positive slope difference implies right-turns between points so clockwise
        return Clockwise;
    }
    else 
    {
        // Negative slope difference implies left-turns between points so anti-clockwise.
        return AntiClockwise;
    }
}
