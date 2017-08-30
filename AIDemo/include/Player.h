// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "Window.h"
#include <vector>
#include "Texture.h"
#include "PathfindingAStar.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief  player
//----------------------------------------------------------------------------------------------------------------------
class Player
{
public:
	/// \brief Constr
	Player();

	/// \brief Destr
	~Player();

	/// \brief draw the player
	/// \prama SDL_Renderer* renderer
	void draw(SDL_Renderer* r);

	/// \brief update the player
	/// \prama float delta time
	/// \prama vec2 new position to move to
	void update(float dt, vec2 newPosition);

	/// \brief create the texture
	/// \prama SDL_Renderer* renderer
	inline void createTexture(SDL_Renderer* r)
	{ m_texture->createTexture(r); }

	/// \brief set current position
	/// \prama vec2 position
	inline void Position(vec2 p)
	{ m_position = p; }

	/// \brief get current position
	/// \return vec2 position
	inline vec2 getPosition()
	{ return m_position; }

private:
	vec2 m_position; ///< current position
	Texture* m_texture = nullptr; ///< texture

public:
	bool AtPathEnd = true;
	vec2 PathTarget;
};
