#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
#endif

#include <zen-math.h>
#include "circle.h"
#include "line2d.h"
#include "point2d.h"

class Renderer
{
public: 
    Renderer(SDL_Renderer* renderer);
    ~Renderer();

    /**
     * Clears the screen to the specified color.
     * 
     * @param color The color to clean the screen to.
     */
    void clearScreen(const Color& color) const;

    /**
     * Sets the draw color to the specified color.
     * 
     * @param color The color to set.
     */
    void setDrawColor(const Color& color) const;

    /**
     * Draws a 2D point to the render buffer.
     * 
     * @param point The point to draw.
     */
    void drawPoint2D(const Point2D& point) const;

    /**
     * Draws a 2D line to the render buffer.
     * 
     * @param line The line to render.
     */
    void drawLine2D(const Line2D& line) const;
    
    /**
     * Draws a circle to the render buffer.
     * 
     * @param circle The circle to draw.
     */
    void drawCircle(const Circle& circle) const;

    /**
     * Fonts available for use.
     */
    enum Font
    {
        FreeSans,
        DejaVu
    };

    /**
     * Draws text.
     * 
     * @param text The text to draw.
     * @param position The position at which to draw the text.
     * @param font The name of the font.
     * @param size The font size.
     * @param color The font color.
     * @param rotation The angle at which to rotate the text.
     */
    void drawText(const std::string& text, const Vector2D& position, const Font& font, Color color, const double rotation = 0) const;

    /**
     * Renders contents of render buffer to the screen.
     */
    void render() const;

private:
    SDL_Renderer* renderer_;
    TTF_Font *fontFreeSans_;
	TTF_Font *fontDejavu_;
};
