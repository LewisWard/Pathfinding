// Author : Lewis Ward
// Date: 29/08/2017
#include "Ray.h"

rayCast::rayCast()
{
	m_origin.x = 0; 
	m_origin.y = 0;
	m_collide = false;
}

rayCast::rayCast(vec2 origin)
{
	m_origin = origin;
	m_collide = false;
}

rayCast::~rayCast()
{

}

vec2 rayCast::cast(vec2 position, vec2 direction, float length)
{
	// make sure the ray has a length
	if (length == 0)
	{
		vec2 returnVector(0.0f, 0.0f);
		// cannot do anything to exit method
		return returnVector;
	}

	vec2 secondPoint = position + (normalize(direction) * length);

	//return points;
	return secondPoint;
}

std::vector<vec2> rayCast::bresenhamLine(vec2 a, vec2 b)
{
	std::vector<vec2> collisionPoints;

	bool step = abs(b.y - a.y) > abs(b.x - a.x);
	
	// if true need to swap vectors around
	if (step)
	{
		swap(a, b);
	}
	
	if (a.x > b.x)
	{
		swap(a, b);
	}
	
	float deltaX = b.x - a.x;
	float deltaY = abs(b.y - a.y);
	int error = 0;
	int yStep = 2.0f;
	float y = a.y;
	
	if (a.y < b.y)
		yStep = 2.0f;
	else
		yStep = -2.0f;
	
	// if not on the same X axis
	if (a.x != b.x)
	{
		for (float x = a.x; x <= b.x; x += 2.0f)
		{
			// make sure vec2 has the x and y the correct way round
			if (step)
				collisionPoints.push_back(vec2(x, y));
			else
				collisionPoints.push_back(vec2(x, y));

			// increase
			error += deltaY;

			if (2 * error >= deltaX)
			{
				y += yStep;
				error -= deltaX;
			}
		}
	}
	else
	{
		// are we above or below the target?
		if (b.y < a.y)
			for (float x = b.y; x <= a.y; x += 2.0f)
				collisionPoints.push_back(vec2(y, x));
		else
			for (float x = b.y; x >= a.y; x -= 2.0f)
				collisionPoints.push_back(vec2(y, x));
	}

	// return the vector
	return collisionPoints;
}

void rayCast::swap(vec2& a, vec2& b)
{
	// swap two vectors with each other
	vec2 c = a;
	a = b;
	b = c;
}
