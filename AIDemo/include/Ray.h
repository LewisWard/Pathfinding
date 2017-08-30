// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "AABB.h"
#include "World.h"
#include "Wall.h"
#include <vector>

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

	/// \brief Destr
	~rayCast();

	/// \brief casts a ray from a origin in a direction
	/// \prama vec2 position of the ray
	/// \prama vec2 direction of the ray
	/// \prama vec2 length of the ray
	/// \return vec2 the ray
	vec2 cast(vec2 position, vec2 direction, float length);

	/// \brief computes the position the ray intersected
	/// \prama vec2 origin
	/// \prama vec2 destination
	/// \return std::vector<vec2> the position that the ray intersected
	std::vector<vec2> bresenhamLine(vec2 a, vec2 b);

	/// \brief sets the origin
	/// \prama vec2 origin
	inline void origin(vec2 o)
	{ m_origin = o; }

	/// \brief gets the origin
	/// \return vec2 origin
	inline vec2 getOrigin()
	{ return m_origin; }

	/// \brief set if the ray intersect anything
	/// \prama bool
	inline void collide(bool c)
	{ m_collide = c; }

	/// \brief get if the ray intersect anything
	/// \return bool
	inline bool getCollide()
	{ return m_collide; }

private:
	vec2 m_origin; ///< the rays origin
	bool m_collide; ///< true if collision happened

	/// \brief swap two vec2's around 
	/// \prama vec2 a
	/// \prama vec2 b
	void swap(vec2& a, vec2& b);
};

// Returns true if ray has a collsion with the target and no other object
//bool RayCollsionTarget(vec2 RayOrigin, vec2 RayTarget, std::vector<Walls> ObjectOrigins)
//{
//	vec2 RayDirection = RayTarget - RayOrigin;
//
//	float Y = 
//}
