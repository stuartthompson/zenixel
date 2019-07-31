#pragma once

#include <vector>
#include "./line2d.h"

/**
 * Represents a path as a series of line segments.
 */
class Path2D
{
public:
    /**
     * Adds a segment to this path.
     */
    void addSegment(const Line2D& line);

    /**
     * Gets the current list of segments that represent the path.
     */
    std::vector<Line2D> getPath() const;

private:
    std::vector<Line2D> segments_;
};
