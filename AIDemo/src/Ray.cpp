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

vec2 rayCast::Cast(vec2 direction, float length)
{
	// make sure the ray has a length
	if (length == 0)
	{
		vec2 returnVector(0.0f, 0.0f);
		// cannot do anything to exit method
		return returnVector;
	}

	vec2 secondPoint = m_origin + (normalize(direction) * length);

	//return points;
	return secondPoint;
}

void rayCast::Swap(vec2& a, vec2& b)
{
	vec2 c = a;
	a = b;
	b = c;
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
