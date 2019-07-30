#include <string>
#include <iostream>
#include <zen-math.h>
#include "point2d.h"
#include "renderer.h"
#include "scene.h"

int lastTime = 0;

void Scene::load(const std::string &sceneName, int currentTime)
{
    // TODO: Load scene from file

    // TODO: Load from JSON scene description
    /* Points */

    this->points_.push_back(Point2D({Vector2D(100, 100), COLOR_RED}));

    /* Lines */

    // Line from coord pair (straight line)
    this->lines_.push_back(Line2D({Plane2D({400, 100}, {600, 100}), COLOR_RED}));

    // Line at zero degrees
    float angle1 = degreesToRadians(0);
    Vector2D start1 = Vector2D(400, 150);
    Vector2D end1 = Vector2D::fromPolar(angle1, 200) + start1;
    this->lines_.push_back(Line2D({Plane2D(start1, end1), COLOR_YELLOW}));

    // Line at a slight downward slope
    float angle2 = degreesToRadians(20);
    Vector2D start2 = Vector2D(400, 200);
    Vector2D end2 = Vector2D::fromPolar(angle2, 200) + start2;
    this->lines_.push_back(Line2D({Plane2D(start2, end2), COLOR_GREEN, true}));

    // Line at 45 degrees
    float angle3 = degreesToRadians(45);
    Vector2D start3 = Vector2D(400, 250);
    Vector2D end3 = Vector2D::fromPolar(angle3, 200) + start3;
    this->lines_.push_back(Line2D({Plane2D(start3, end3), COLOR_BLUE, true}));

    // Line at a sharp downward slope
    float angle4 = degreesToRadians(70);
    Vector2D start4 = Vector2D(400, 300);
    Vector2D end4 = Vector2D::fromPolar(angle4, 200) + start4;
    this->lines_.push_back(Line2D({Plane2D(start4, end4), COLOR_BLUE, true}));

    // Vertical line
    float angle5 = degreesToRadians(85);
    Vector2D start5 = Vector2D(400, 350);
    Vector2D end5 = Vector2D::fromPolar(angle5, 200) + start5;
    this->lines_.push_back(Line2D({Plane2D(start5, end5), COLOR_BLUE, true}));

    // Lines in various directions (starburst)
    Vector2D starburstOrigin = Vector2D({800, 200});
    for (int i = 0; i <= 360; i += 30)
    {
        this->lines_.push_back(Line2D({Plane2D(starburstOrigin, degreesToRadians(i), 120), COLOR_YELLOW}));
    }

    /* Circles */

    // Draw a circle
    this->circles_.push_back(Circle(Vector2D({300, 100}), 50, Color({255, 255, 128, 255}), true));

    /* Clock */
    Vector2D origin = Vector2D(100, 600);
    float radius = 75;
    int hourMarkerLength = 8;
    int hourHandLength = 40;
    int minuteHandLength = 55;
    int hours = currentTime / 12;
    int minutes = currentTime - hours * 60;
    Color borderColor = COLOR_YELLOW;
    Color markerColor = COLOR_GRAY;
    Color hourHandColor = COLOR_WHITE;
    Color minuteHandColor = COLOR_GREEN;

    this->circles_.push_back(Circle({origin, radius, borderColor, false}));
    // Draw hour markers
    for (float hour = 0; hour < 12; hour++)
    {
        float angle = 180 - ((360 / 12) * hour); // Add 360/12 degrees each increment (1 marker per hour)
        Vector2D hourMarkerStart = Vector2D::fromPolar(degreesToRadians(angle), radius - hourMarkerLength) + origin;
        Vector2D hourMarkerEnd = Vector2D::fromPolar(degreesToRadians(angle), hourMarkerLength) + hourMarkerStart;
        this->lines_.push_back(Line2D({Plane2D(hourMarkerStart, hourMarkerEnd), markerColor}));
    }
    // Draw hands
    float hourHandAngle = (hours * (360 / 12)) - 90;
    // Adjust hour handle angle for partial hour
    float percentThroughHour = (float)minutes / (float)60;
    hourHandAngle = hourHandAngle + ((360 / 12) * percentThroughHour);
    this->lines_.push_back(Line2D({Plane2D(origin, Vector2D::fromPolar(degreesToRadians(hourHandAngle), hourHandLength) + origin), hourHandColor}));
    float minuteHandAngle = (minutes * (360 / 60)) - 90;
    Line2D mhl = Line2D({Plane2D(origin, Vector2D::fromPolar(degreesToRadians(minuteHandAngle), minuteHandLength) + origin), minuteHandColor, true});
    this->lines_.push_back(mhl);
    Vector2D mhlv = mhl.plane.end() - mhl.plane.start();
    float angle = atan(mhlv.y / mhlv.x);

    if (currentTime != lastTime)
    {
        std::cout << "(" << mhlv.x << ", " << mhlv.y << ")  r: " << angle << " d:" << radiansToDegrees(angle) << std::endl;
        lastTime = currentTime;
    }
}

void Scene::render(const Renderer &renderer) const
{
    // Draw points
    for (std::vector<Point2D>::const_iterator point = this->points_.begin(); point != this->points_.end(); ++point)
    {
        renderer.drawPoint2D(*point);
    }

    // Draw Lines
    for (std::vector<Line2D>::const_iterator line = this->lines_.begin(); line != this->lines_.end(); ++line)
    {
        renderer.drawLine2D(*line);
    }

    // Draw Circles
    for (std::vector<Circle>::const_iterator circle = this->circles_.begin(); circle != this->circles_.end(); ++circle)
    {
        renderer.drawCircle(*circle);
    }

    // Draw Text
    renderer.drawText("DejaVu 14pt", Vector2D(20, 20), Renderer::DejaVu, COLOR_CYAN);
    renderer.drawText("FreeSans 18pt", Vector2D(20, 40), Renderer::FreeSans, COLOR_YELLOW);
}
