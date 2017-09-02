// Author : Lewis Ward
// Date: 29/08/2017
#include "Wall.h"

Wall::Wall(Vec2 GridCenter, float GridExtents)
{
	WallBounds = AABB(GridCenter - (float)GridExtents, GridCenter + (float)GridExtents);
	Center = GridCenter;
}

Wall::~Wall()
{

}

bool Wall::Collision(Vec2 Position)
{
	return WallBounds.intersection(Position);
}
