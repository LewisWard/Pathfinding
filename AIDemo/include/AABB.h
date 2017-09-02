// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "Window.h"

struct AABB
{
	AABB() : Min(0, 0), Max(1.0f, 1.0f) {};
	AABB(Vec2 MinPoint, Vec2 MaxPoint) : Min(MinPoint), Max(MaxPoint), Extents((MaxPoint - MinPoint) / 2.0f) {};

	/// \brief Check if point has intersected the AABB
	/// \prama Vec2 point
	/// \bool true if intersected
	inline bool intersection(Vec2 Point)
	{
		if (Point.X >= Min.X && Point.Y >= Min.Y && Point.X <= Max.X && Point.Y <= Max.Y)
		{
			return true;
		}
		return false;
	}

	/// \brief Check if a AABB has intersected the AABB
	/// \prama AABB
	/// \bool true if intersected
	inline bool intersection(AABB Box)
	{
		if (Box.Min.X >= Min.X && Box.Min.Y >= Min.Y && Box.Max.X <= Max.X && Box.Max.Y <= Max.Y)
		{
			return true;
		}
		return false;
	}

	Vec2 Min;
	Vec2 Max;
	Vec2 Extents;

	inline bool operator == (const AABB& b) 
	{ 
		return (Min == b.Min && 
					  Max == b.Max && 
						Extents == b.Extents); 
	}
};


