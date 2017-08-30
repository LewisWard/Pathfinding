// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "Player.h"
#include "Ray.h"
#include <time.h>

//----------------------------------------------------------------------------------------------------------------------
/// \brief  NPC/Bots characters
//----------------------------------------------------------------------------------------------------------------------
class NPC
{
public:
	/// \brief Constr
	NPC();

	/// \brief Constr
	/// \prama vec2 starting position
	NPC(vec2 startPosition);

	/// \brief Destr
	~NPC();

	/// \brief draw the NPC
	/// \prama SDL_Renderer* renderer
	void draw(SDL_Renderer* r);

	/// \brief update the NPC
	/// \prama float delta time
	/// \prama vec2 new position to move to
	void update(float dt, vec2 newPosition);

	/// \brief generate to new position
	/// \return vec2 position
	vec2 genMoveTo();

	/// \brief load a new texture
	/// \prama char* texture file name
	void loadNewTexture(const char* texture);

	/// \brief create the texture
	/// \prama SDL_Renderer* renderer
	inline void createTexture(SDL_Renderer* r) { m_texture->createTexture(r); }

	/// \brief set current position
	/// \prama vec2 position
	inline void Position(vec2 p) { m_position = p; }

	/// \brief get current position
	/// \return vec2 position
	inline vec2 getPosition()	{ return m_position; }

	/// \brief set current destination position
	/// \prama vec2 position
	inline void moveToPosition(vec2 p) { m_moveToPosition = p; }

	/// \brief get current destination position
	/// \prama vec2 position
	inline vec2 getMoveToPosition() { return m_moveToPosition; }

	/// \brief set is the NPC is moving or not
	/// \prama bool
	inline void isMoving(bool m) { m_moving = m; }

	/// \brief get is the NPC is moving or not
	/// \prama bool
	inline bool getIsMoving() { return m_moving; }


	inline void SetPlayerInSight(bool s) { SeePlayer = s; }

	inline bool IsPlayerInSight() { return SeePlayer; }

private:
	vec2 m_position; ///< current position
	vec2 m_moveToPosition; ///< current destination
	Texture* m_texture; ///< texture
	bool m_moving; ///< is the NPC moving
	bool SeePlayer = false;
};
