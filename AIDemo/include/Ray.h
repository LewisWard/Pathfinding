// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "AABB.h"
#include "World.h"
#include "Wall.h"
#include <vector>
#include <algorithm>

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Casts a ray
//----------------------------------------------------------------------------------------------------------------------
class rayCast
{
public:
	/// \brief Constr
	rayCast();

	/// \brief Constr
	/// \prama vec2 origin of the ray
	rayCast(vec2 origin);

	rayCast(vec2 origin, vec2 direction) : m_origin(origin), m_direction(direction) {}

	/// \brief Destr
	~rayCast();

	/// \brief casts a ray from a origin in a direction
	/// \prama vec2 position of the ray
	/// \prama vec2 direction of the ray
	/// \prama vec2 length of the ray
	/// \return vec2 the ray
	vec2 cast(vec2 position, vec2 direction, float length);

	/// \brief computes the position the ray intersected
	/// \prama std::vector<vec2> collsion locations
	/// \prama vec2 origin
	/// \prama vec2 destination
	/// \return bool, true if no objects are intersected between the origin and target
	bool Intersect(std::vector<vec2>& Walls, vec2 Origin, vec2 Target);

	bool Intersect(Wall AWall);

	/// \brief sets the origin
	/// \prama vec2 origin
	inline void origin(vec2 o) { m_origin = o; }

	/// \brief gets the origin
	/// \return vec2 origin
	inline vec2 getOrigin() { return m_origin; }

	/// \brief sets the direction
	/// \prama vec2 direction
	inline void SetDirection(vec2 o) { m_direction = o; }

	/// \brief gets the direction
	/// \return vec2 direction
	inline vec2 GetDirection() { return m_direction; }

private:
	vec2 m_origin; ///< the rays origin
	vec2 m_direction;

	/// \brief swap two vec2's around 
	/// \prama vec2 a
	/// \prama vec2 b
	void swap(vec2& a, vec2& b);
};
