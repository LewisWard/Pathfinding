// Author : Lewis Ward
// Date: 29/08/2017
#include "Ray.h"

Ray::Ray()
{
	Origin.X = 0; 
	Origin.Y = 0;
}

Ray::Ray(Vec2 RayOrigin)
{
	Origin = RayOrigin;
}

Ray::~Ray()
{

}

Vec2 Ray::Cast(Vec2 Direction, float Length)
{
	// Make sure the ray has a length
	if (Length == 0)
	{
		// cannot do anything to exit method
		Vec2 ReturnVector(0.0f, 0.0f);
		return ReturnVector;
	}

	// Return the new location of where the ray ends
	Vec2 SecondPoint = Origin + (Normalize(Direction) * Length);	
	return SecondPoint;
}

bool Ray::Intersect(Wall AWall)
{
	// Method is based upon the fast, branchless method here: https://tavianator.com/fast-branchless-raybounding-box-intersections/
	float LineMin = -INFINITY, LineMax = INFINITY; // INFINITY is meant to create an overflow in constant arithmetic by design

	Vec2 Invert(1.f / Direction);

	float Point1X = (AWall.GetGrid().Min.X - Origin.X) * Invert.X;
	float Point2X = (AWall.GetGrid().Max.X - Origin.X) * Invert.X;

	LineMin = std::max(LineMin, std::min(Point1X, Point2X));
	LineMax = std::min(LineMax, std::max(Point1X, Point2X));

	float Point1Y = (AWall.GetGrid().Min.Y - Origin.Y) * Invert.Y;
	float Point2Y = (AWall.GetGrid().Max.Y - Origin.Y) * Invert.Y;

	LineMin = std::max(LineMin, std::min(Point1Y, Point2Y));
	LineMax = std::min(LineMax, std::max(Point1Y, Point2Y));

	return (LineMax >= 0) && (LineMax >= LineMin);
}
