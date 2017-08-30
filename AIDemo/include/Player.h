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
	void Draw(SDL_Renderer* r);

	/// \brief update the player
	/// \prama float delta time
	/// \prama vec2 new position to move to
	void Update(float dt, vec2 newPosition);

	/// \brief create the texture
	/// \prama SDL_Renderer* renderer
	inline void CreateTexture(SDL_Renderer* r) { PlayerTexture->createTexture(r); }

	/// \brief set current position
	/// \prama vec2 position
	inline void SetPosition(vec2 p) { Position = p; }

	/// \brief get current position
	/// \return vec2 position
	inline vec2 GetPosition() { return Position; }

	inline void SetPathTarget(vec2 p) { PathTarget = p; }

	inline vec2 GetPathTarget() { return PathTarget; }

	inline void SetAtPathEnd(bool b) { AtPathEnd = b; }

	inline bool IsAtPathEnd() { return AtPathEnd; }

private:
	Texture* PlayerTexture = nullptr;
	vec2 Position; ///< current position
	vec2 PathTarget;
	bool AtPathEnd = true;
};
