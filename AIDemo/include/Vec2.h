// Author : Lewis Ward
// Date: 29/08/2017
#pragma once

struct vec2
{
	float x;
	float y;

	vec2() : x(0), y(0){};
	vec2(float x, float y) : x(x), y(y){};

	bool operator == (const vec2& b) { return (x == b.x && y == b.y); }
	void operator = (const vec2& b) { x = b.x; y = b.y; }
};

inline vec2 operator + (vec2 a, vec2 b)
{
	vec2 c; 
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

inline vec2 operator - (vec2 a, vec2 b)
{
	vec2 c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

inline vec2 operator * (vec2 a, float b)
{
	vec2 c;
	c.x = a.x * b;
	c.y = a.y * b;
	return c;
}

inline vec2 operator / (vec2 a, float b)
{
	vec2 c;
	c.x = a.x / b;
	c.y = a.y / b;
	return c;
}

inline vec2 operator / (float b, vec2 a)
{
	vec2 c;
	c.x = b / a.x;
	c.y = b / a.y;
	return c;
}

inline vec2 SafeDivide(float a, vec2 b)
{
	if (b.x == 0)
		b.x = 1;

	if (b.y == 0)
		b.y = 1;

	return a / b;
}

inline float dot(vec2 a, vec2 b)
{
	return (a.x * b.x) + (a.y * b.y);
}

inline float length(vec2 a)
{
	return std::sqrt((a.x * a.x) + (a.y * a.y));
}

inline vec2 normalize(vec2 a)
{

	float len = length(a);

	if (len > 000000.1f)
	{
		len = 1.0f / len;
	}
	else
	{
		len = 0.0f;
	}

	return vec2(len * a.x, len * a.y);
}

inline bool withinRange(vec2 a, vec2 b)
{
	if (a.x >= b.x - 000000.1f && a.x <= b.x + 000000.1f && a.y >= b.y - 000000.1f && a.y <= b.y + 000000.1f)
		return true;
	else
		return false;
}