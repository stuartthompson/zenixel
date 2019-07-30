#pragma once

#include <math.h>

// PI / 180 is used to convert degrees to radians
const double M_PI_OVER_180 = M_PI / 180;
// 180 / PI is used to convert radians to degrees
const double M_180_OVER_PI = 180 / M_PI;

/**
 * Converts degrees to radians.
 */
template <typename T>
const float degreesToRadians(const T degrees) { return degrees * M_PI_OVER_180; }

/**
 * Converts radians to degrees.
 */
template <typename T>
const float radiansToDegrees(const T radians) { return radians * M_180_OVER_PI; }