// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "Window.h"
#include <vector>
#include "Texture.h"
#include "PathfindingAStar.h"
#include "Ray.h"

class Actor
{
public:
	Actor() {} 

	Actor(Vec2 SpawnLocation) : Location(SpawnLocation), TargetLocation(SpawnLocation) { }

	virtual ~Actor();

	void Draw(SDL_Renderer* Renderer);

	virtual void Update(float dt);

	/// \brief Move towards the next location in the path
	/// \prama float Delta Time
	/// \prama std::vector<vec2> Path
	virtual void MoveTo(float& dt, std::vector<Vec2>& Path);

	/// \brief Create the texture
	/// \prama SDL_Renderer* renderer
	inline void CreateTexture(SDL_Renderer* r) { ActorTexture->CreateTexture(r); }

	inline void SetLocation(Vec2 NewLocation) { Location = NewLocation; }

	inline Vec2 GetLocation() { return Location; }

	inline void SetPathTarget(Vec2 p) { TargetLocation = p; }

	inline Vec2 GetPathTarget() { return TargetLocation; }

	inline void SetAtPathEnd(bool b) { AtPathEnd = b; }

	inline bool IsAtPathEnd() { return AtPathEnd; }

protected:
	Texture* ActorTexture = nullptr;
	Vec2 Location;
	Vec2 TargetLocation;
	float MovementSpeed = 5.f;
	bool AtPathEnd = true;
};

