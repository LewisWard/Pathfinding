// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "AABB.h"
#include "World.h"
#include "Wall.h"
#include <vector>
#include <algorithm>

class Ray
{
public:
	Ray();
	Ray(Vec2 Origin);
	Ray(Vec2 Origin, Vec2 Direction) : Origin(Origin), Direction(Direction) {}

	~Ray();

	/// \brief casts a ray from the origin in a direction
	/// \prama Vec2 direction of the ray
	/// \prama float length of the ray
	/// \return Vec2 the ray
	Vec2 Cast(Vec2 direction, float length);

	/// \brief returns if a Wall have intersected with the ray
	/// \prama Wall
	/// \return bool, true if no objects are intersected between the origin and target
	bool Intersect(Wall AWall);

	/// \brief sets the origin
	/// \prama Vec2 origin
	inline void SetOrigin(Vec2 o) { Origin = o; }

	/// \brief gets the origin
	/// \return Vec2 origin
	inline Vec2 GetOrigin() { return Origin; }

	/// \brief sets the direction
	/// \prama Vec2 direction
	inline void SetDirection(Vec2 o) { Direction = o; }

	/// \brief gets the direction
	/// \return Vec2 direction
	inline Vec2 GetDirection() { return Direction; }

private:
	Vec2 Origin;
	Vec2 Direction;
};
