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
	vec2 Direction = 1.f / (Target - Origin);

	// Cycle all objects, check to see if target is in line of sight
	for (size_t i = 0; i < Walls.size(); i++)
	{
		vec2 AWall = Walls[i];

		vec2 LocationMin(AWall.x - 0.5f, AWall.y - 0.5f);
		vec2 LocationMax(AWall.x + 0.5f, AWall.y + 0.5f);

		float LocMinX = (LocationMin.x - Origin.x) * Direction.x;
		float LocMaxX = (LocationMax.x - Origin.x) * Direction.x;
		float LocMinY = (LocationMin.y - Origin.y) * Direction.y;
		float LocMaxY = (LocationMax.y - Origin.y) * Direction.y;

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
