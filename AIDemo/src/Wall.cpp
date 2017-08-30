// Author : Lewis Ward
// Date: 29/08/2017
#include "Wall.h"

Wall::Wall(vec2 GridCenter, int GridExtents)
{
	m_wall.m_min.x = GridCenter.x - GridExtents;
	m_wall.m_min.y = GridCenter.y - GridExtents;
	m_wall.m_max.x = GridCenter.x + GridExtents;
	m_wall.m_max.y = GridCenter.y + GridExtents;

	m_center.x = GridCenter.x;
	m_center.y = GridCenter.y;
}

Wall::~Wall()
{

}

bool Wall::collision(vec2 position)
{
	return m_wall.intersection(position);
}
