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

	Actor(vec2 SpawnLocation) : Location(SpawnLocation), TargetLocation(SpawnLocation) { }

	virtual ~Actor() 
	{ 
		if (ActorTexture)
			delete ActorTexture;
	}

	void Draw(SDL_Renderer* r)
	{
		SDL_Rect destRect;
		destRect.w = 20;
		destRect.h = 20;
		destRect.x = Location.x * 20;
		destRect.y = Location.y * 20;
		SDL_RenderCopy(r, ActorTexture->texture(), NULL, &destRect);
	}

	virtual void Update(float dt)
	{
		Location.x += (TargetLocation.x - Location.x) * MovementSpeed * dt;
		Location.y += (TargetLocation.y - Location.y) * MovementSpeed * dt;
	}

	virtual void MoveTo(float& dt, std::vector<vec2>& Path)
	{
		TargetLocation = Path.back();

		if (withinRange(Location, TargetLocation))
		{
			Location = TargetLocation;
			Path.pop_back();
		}
	}

	/// \brief create the texture
	/// \prama SDL_Renderer* renderer
	inline void CreateTexture(SDL_Renderer* r) { ActorTexture->createTexture(r); }

	/// \brief set current position
	/// \prama vec2 position
	inline void SetLocation(vec2 NewLocation) { Location = NewLocation; }

	/// \brief get current position
	/// \return vec2 position
	inline vec2 GetLocation() { return Location; }

	inline void SetPathTarget(vec2 p) { TargetLocation = p; }

	inline vec2 GetPathTarget() { return TargetLocation; }

	inline void SetAtPathEnd(bool b) { AtPathEnd = b; }

	inline bool IsAtPathEnd() { return AtPathEnd; }

protected:
	Texture* ActorTexture = nullptr;
	vec2 Location;
	vec2 TargetLocation;
	float MovementSpeed = 5.f;
	bool AtPathEnd = true;
};

