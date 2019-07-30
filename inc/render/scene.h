#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <string>
#include <vector>
#include <zen-math.h>

#include "circle.h"
#include "point2d.h"

class Scene
{
public:
    void load(const std::string &sceneName, int currentTime);
    void render(const Renderer &renderer) const;

private:
    std::vector<Line2D> lines_;
    std::vector<Point2D> points_;
    std::vector<Circle> circles_;
};
