#include <iomanip>
#include <iostream>
#include <sstream>
#include "zmath.h"
#include "renderer.h"

Renderer::Renderer(SDL_Renderer *renderer, int canvasWidth, int canvasHeight) : 
	renderer_(renderer), canvasWidth_(canvasWidth), canvasHeight_(canvasHeight)
{
	TTF_Init();

	// Initialize fonts
	#ifdef __APPLE__
	this->fontFreeSans_ = TTF_OpenFont("/Library/Fonts/Tahoma.ttf", 18); // FreeSans 18
	this->fontDejavu_ = TTF_OpenFont("/Library/Fonts/Tahoma.ttf", 14);   // DejaVu 18
	#else
	// Linux fonts
	this->fontFreeSans_ = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf", 18); // FreeSans 18
	this->fontDejavu_ = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuMathTeXGyre.ttf", 14);   // DejaVu 18
	#endif
}

Renderer::~Renderer()
{
	// Close fonts
	TTF_CloseFont(this->fontFreeSans_);
	TTF_CloseFont(this->fontDejavu_);

	// Quit TTF
	TTF_Quit();
}

void Renderer::clearScreen(const Color &color) const
{
	this->setDrawColor(color);		  // Set screen clear color
	SDL_RenderClear(this->renderer_); // Clear screen
}

void Renderer::setDrawColor(const Color &color) const
{
	SDL_SetRenderDrawColor(this->renderer_, color.r, color.g, color.b, color.a);
}

void Renderer::drawPoint2D(const Point2D &point) const
{
	Point2D zPoint = Point2D({toZenCoords(point.location), point.color});
	this->setDrawColor(zPoint.color);
	SDL_RenderDrawPoint(this->renderer_, zPoint.location.x, zPoint.location.y);
}

void Renderer::drawLine2D(const Line2D &line) const
{
	this->setDrawColor(line.color);

	Vector2D from = line.plane.start();
	Vector2D to = line.plane.end();

	// Figure out whether x or y is covering more distance (i.e is the slope more horizontal or vertical)
	float dx = from.x - to.x;
	float dy = from.y - to.y;

	float slope = line.plane.slope();

	// Determine the slope of the line (i.e. vector 3,9 has slope 1/3 (or y/x == 9/3))
	float x, y;

	// Horizontal and vertical lines are plotted differently
	if (dx == 0) // Vertical line
	{
		if (from.y <= to.y) // Line is drawn top to bottom so have to increment from to (origin is top-left in SDL)
		{
			for (y = from.y; y <= to.y; y++)
			{
				this->drawPoint2D(Point2D({{from.x, y}, line.color}));
			}
		}
		else
		// Line is drawn bottom to top so have to decrement from to (origin is top-left in SDL)
		{
			for (y = from.y; y >= to.y; y--)
			{
				this->drawPoint2D(Point2D({{from.x, y}, line.color}));
			}
		}
	}
	else if (dy == 0) // Horizontal line
	{
		if (from.x <= to.x) // Line is drawn left to right so have to increment from to (origin is top-left in SDL)
		{
			for (x = from.x; x <= to.x; x++)
			{
				this->drawPoint2D(Point2D({{x, from.y}, line.color}));
			}
		}
		else // Line is drawn right to left so have to decrement from to (origin is top-left in SDL)
		{
			for (x = from.x; x >= to.x; x--)
			{
				this->drawPoint2D(Point2D({{x, from.y}, line.color}));
			}
		}
	}
	// Sloped line
	else
	{
		// Draw more than one segment per x-pixel if slope is greater than 1 or less than -1 (fills in near-vertical lines)
		float xInc = 1;
		if (slope > 1)
		{
			xInc = 1 / slope;
		}
		if (slope < -1)
		{
			xInc = -1 / slope;
		}

		// Plot for integer values of x
		// Find quadrant
		if (slope <= 1 && slope >= -1)
		{
			// Line is more horizontal than vertical so plot using x increments
			if (from.x <= to.x)
			{
				// Line is moving to the right
				for (x = from.x; x <= to.x; x++)
				{
					y = (slope * (x - from.x)) + from.y; // Plot the point using y = mx + c
					this->drawPoint2D(Point2D({{x, y}, line.color}));
				}
			}
			else
			{
				// Line is moving to the left
				for (x = from.x; x >= to.x; x--)
				{
					y = (slope * (x - from.x)) + from.y; // Plot the point using y = mx + c
					this->drawPoint2D(Point2D({{x, y}, line.color}));
				}
			}
		}
		else
		{
			// Line is more vertical than horizontal so plot using y increments
			if (from.y <= to.y)
			{
				// Line is moving down
				for (y = from.y; y <= to.y; y++)
				{
					// x = (y-c) / m
					x = ((y - from.y) / slope) + from.x;
					this->drawPoint2D(Point2D({{x, y}, line.color}));
				}
			}
			else
			{
				// Line is moving up
				for (y = from.y; y >= to.y; y--)
				{
					// x = (y-c) / m
					x = ((y - from.y) / slope) + from.x;
					this->drawPoint2D(Point2D({{x, y}, line.color}));
				}
			}
		}
	}

	// Draw slope text (if requested)
	if (line.showProps) 
	{
		// Determine midpoint of line
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << line.plane.length() << " [" << slope << "]" << " (" << radiansToDegrees(line.plane.angle()) << ")";
		std::string text = stream.str();
		Vector2D textLocation = line.plane.start();
		this->drawText(text, textLocation, Renderer::DejaVu, COLOR_CYAN, radiansToDegrees(line.plane.angle()));
	}
}

void Renderer::drawCircle(const Circle &circle) const
{
	this->setDrawColor(circle.color);

	// Loop through 360 degrees
	for (int deg = 0; deg < 360; deg++)
	{
		// Vector describing the radius to draw
		Vector2D r = Vector2D::fromPolar(degreesToRadians(deg), circle.radius); // Next radius to draw
		Vector2D endPoint = circle.center + r;									// Endpoint is center point + vector described by the current radius being drawn
		if (circle.fill)
		{
			this->drawLine2D(Line2D({Plane2D({circle.center.x, circle.center.y}, {endPoint.x, endPoint.y}), circle.color}));
		}
		else
		{
			this->drawPoint2D(Point2D({endPoint, circle.color}));
		}
	}
}

void Renderer::drawText(const std::string &text, const Vector2D &position, const Renderer::Font &font, Color color, const double rotation) const
{
	// TODO: Null checks and exiting
	TTF_Font *fontStyle;
	if (font == FreeSans)
	{
		fontStyle = this->fontFreeSans_;
	}
	else
	{
		fontStyle = this->fontDejavu_;
	}
	SDL_Color sdlCol = {color.r, color.g, color.b, color.a};									 // Create color
	SDL_Surface *textSurface = TTF_RenderText_Blended(fontStyle, text.c_str(), sdlCol);			 // Create a surface to render onto
	SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer_, textSurface);			 // Create a texture containing the text

	// Determine rendered text size
	int width, height;
	TTF_SizeText(fontStyle, text.c_str(), &width, &height);

	Vector2D zPosition = toZenCoords(position);
	SDL_Rect textRect = {(int)zPosition.x, (int)zPosition.y, width, height};

	SDL_Point rotatePoint = {0, 0};
	SDL_RenderCopyEx(this->renderer_, texture, NULL, &textRect, -rotation, &rotatePoint, SDL_FLIP_NONE); // Render the textured rectangle

	// Free surface
	SDL_FreeSurface(textSurface);
}

void Renderer::render() const
{
	SDL_RenderPresent(this->renderer_);
}

Vector2D Renderer::toZenCoords(const Vector2D& vector) const 
{
	return Vector2D({vector.x, this->canvasHeight_ - vector.y});
}
