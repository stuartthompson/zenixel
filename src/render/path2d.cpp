#include "path2d.h"

void Path2D::addSegment(const Line2D& line)
{
    this->segments_.push_back(Line2D(line));
}

std::vector<Line2D> Path2D::getPath() const 
{
    return this->segments_;
}
