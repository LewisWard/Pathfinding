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
	Wall(Vec2 GridCenter, float GridExtents);

	/// \brief Destr
	~Wall();

	/// \brief tests to see if a collision took place
	/// \prama Vec2 position of character
	/// \return bool 
	bool Collision(Vec2 Position);

	/// \brief get the index of the grid the wall is in
	/// \return AABB grid index 
	inline AABB GetGrid() { return WallBounds;}

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
