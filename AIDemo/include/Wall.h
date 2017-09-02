// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "AABB.h"

class Wall
{
public:

	Wall(Vec2 GridCenter, float GridExtents);

	~Wall();

	/// \brief tests to see if a collision took place
	/// \prama Vec2 position of character
	/// \return bool 
	bool Collision(Vec2 Position);

	/// \brief get the AABB
	/// \return AABB
	inline AABB GetGrid() { return WallBounds;}

	/// \brief get the location at the center of the AABB
	/// \return AABB center
	inline Vec2 GetCenter() { return Center; }

private:
	AABB WallBounds;
	Vec2 Center;

public:

	inline bool operator == (const Wall& b)
	{
		return (WallBounds == b.WallBounds && Center == b.Center);
	}
};
