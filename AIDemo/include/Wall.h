// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "AABB.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Wall class
//----------------------------------------------------------------------------------------------------------------------
class Wall
{
public:
	Wall(vec2 GridCenter, float GridExtents);

	/// \brief Destr
	~Wall();

	/// \brief tests to see if a collision took place
	/// \prama vec2 position of character
	/// \return bool 
	bool collision(vec2 position);

	/// \brief get the index of the grid the wall is in
	/// \return AABB grid index 
	inline AABB getGrid() { return m_wall;}

	inline vec2 getCenter() { return m_center; }

private:
	AABB m_wall;
	vec2 m_center;

public:

	inline bool operator == (const Wall& b)
	{
		return (m_wall == b.m_wall && m_center == b.m_center);
	}
};
