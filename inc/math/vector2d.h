#pragma once

/**
 * Represents a vector in 2D space.
 * 
 * A vector is stored as a point, which has an implicit direction and magnitude from the 2D origin.
 */
class Vector2D
{
public:
    /**
     * Initializes a vector with no magnitude.
     */
    Vector2D();
    
    /**
     * Initializes a vector from another vector.
     * 
     * @param vector The vector to initialize from.
     */
    Vector2D(const Vector2D& vector);

    /**
     * Initializes a vector from coordinates.
     * 
     * @param point The x and y coordinates of the vector.
     */
    Vector2D(const float x, const float y);

    /** 
     * Initializes a vector using direction and magnitude (polar). 
     *
     * @param direction The angle of the vector.
     * @param magnitude The length of the vector. 
     */
    static Vector2D fromPolar(const float direction, const float magnitude);

    /**
     * Sets the value of this vector.
     * 
     * @param vector The new vector value.
     * @return The updated vector.
     */
    Vector2D& operator=(const Vector2D& vector);

    // Arithmetic modifying operators
    Vector2D& operator+=(const Vector2D& vector);
    Vector2D& operator-=(const Vector2D& vector);
    Vector2D& operator*=(const Vector2D& vector);
    Vector2D& operator/=(const Vector2D& vector);

    // Arithmetic operators
    Vector2D operator+(const Vector2D& vector) const;
    Vector2D operator-(const Vector2D& vector) const;
    Vector2D operator*(const Vector2D& vector) const;
    Vector2D operator/(const Vector2D& vector) const;

    /**
     * Returns the direction of the vector.
     * This is the angle that describes the vector from the origin.
     */
	float direction() const;

    /**
     * Returns the magnitude (length) of the vector.
     */
	float magnitude() const;

    /**
     * Calculates the distance from another vector.
     * 
     * @param vector The vector to calculate the distance from.
     */
    float distanceFrom(const Vector2D& vector) const;

    /**
     * Enumeration representing the possible orientations of a vector triplet.
     */
    enum Orientation {
        Colinear,
        Clockwise,
        AntiClockwise
    };

    /**
     * Gets the orientation of three vectors.
     */
    static Vector2D::Orientation orientation(const Vector2D& p, const Vector2D& q, const Vector2D& r);

    // x and y coordinate of the vector
    float x, y; 
};
