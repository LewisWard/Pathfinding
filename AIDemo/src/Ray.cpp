// Author : Lewis Ward
// Date: 29/08/2017
#include "Ray.h"

rayCast::rayCast()
{
	m_origin.x = 0; 
	m_origin.y = 0;
}

rayCast::rayCast(vec2 origin)
{
	m_origin = origin;
}

rayCast::~rayCast()
{

}

vec2 rayCast::cast(vec2 position, vec2 direction, float length)
{
	m_direction = direction; 

	// make sure the ray has a length
	if (length == 0)
	{
		vec2 returnVector(0.0f, 0.0f);
		// cannot do anything to exit method
		return returnVector;
	}

	vec2 secondPoint = position + (normalize(m_direction) * length);

	//return points;
	return secondPoint;
}

void rayCast::swap(vec2& a, vec2& b)
{
	vec2 c = a;
	a = b;
	b = c;
}

bool rayCast::Intersect(std::vector<vec2>& Walls, vec2 Origin, vec2 Target)
{
	vec2 DirectionI = SafeDivideZero(1.0f, Target - Origin);

	// Cycle all objects, check to see if target is in line of sight
	for (size_t i = 0; i < Walls.size(); i++)
	{
		vec2 AWall = Walls[i];

		vec2 LocationMin(AWall.x - 0.5f, AWall.y - 0.5f);
		vec2 LocationMax(AWall.x + 0.5f, AWall.y + 0.5f);

		float LocMinX = (LocationMin.x - Origin.x) * DirectionI.x;
		float LocMaxX = (LocationMax.x - Origin.x) * DirectionI.x;
		float LocMinY = (LocationMin.y - Origin.y) * DirectionI.y;
		float LocMaxY = (LocationMax.y - Origin.y) * DirectionI.y;

		if (LocMinX > LocMaxX)
			std::swap(LocMinX, LocMaxX);

		if (LocMinY > LocMaxY)
			std::swap(LocMinY, LocMaxY);

		// Did the ray miss the AABB around the location
		if ((LocMinX > LocMaxY) || (LocMinY > LocMaxX))
			continue;
		else
			return false;
	}

	return true;
}

bool rayCast::Intersect(Wall AWall)
{
	float tmin = -INFINITY, tmax = INFINITY;

	vec2 Invert(1.f / m_direction);

	float tx1 = (AWall.getGrid().m_min.x - m_origin.x) * Invert.x;
	float tx2 = (AWall.getGrid().m_max.x - m_origin.x) * Invert.x;

	tmin = std::max(tmin, std::min(tx1, tx2));
	tmax = std::min(tmax, std::max(tx1, tx2));

	float ty1 = (AWall.getGrid().m_min.y - m_origin.y) * Invert.y;
	float ty2 = (AWall.getGrid().m_max.y - m_origin.y) * Invert.y;

	tmin = std::max(tmin, std::min(ty1, ty2));
	tmax = std::min(tmax, std::max(ty1, ty2));

	return (tmax >= 0) && (tmax >= tmin);
}
