// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "Window.h"

struct AABB
{
	AABB() : m_min(0, 0), m_max(1.0f, 1.0f) {};
	AABB(vec2 min, vec2 max) : m_min(min), m_max(max) {};

	/// \brief check if point has intersected the AABB
	/// \prama vec2 point
	/// \bool true if intersected
	bool intersection(vec2 point)
	{
		if (point.x >= m_min.x && point.y >= m_min.y && point.x <= m_max.x && point.y <= m_max.y)
		{
			return true;
		}
		return false;
	}

	/// \brief check if a AABB has intersected the AABB
	/// \prama AABB
	/// \bool true if intersected
	bool intersection(AABB aabb)
	{
		if (aabb.m_min.x >= m_min.x && aabb.m_min.y >= m_min.y && aabb.m_max.x <= m_max.x && aabb.m_max.y <= m_max.y)
		{
			return true;
		}
		return false;
	}

	vec2 m_min; ///< min 
	vec2 m_max; ///< max

	inline bool operator == (const AABB& b) { return (m_min == b.m_min && m_max == b.m_max); }
};


