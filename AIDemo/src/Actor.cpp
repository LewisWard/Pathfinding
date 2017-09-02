// Author : Lewis Ward
// Date: 02/08/2017
#pragma once
#include "Actor.h"

Actor::~Actor()
{
	if (ActorTexture)
		delete ActorTexture;
}

void Actor::Draw(SDL_Renderer* Renderer)
{
	SDL_Rect DestRect;
	DestRect.w = 20;
	DestRect.h = 20;
	DestRect.x = (int)(Location.X * 20.0f);
	DestRect.y = (int)(Location.Y * 20.0f);
	SDL_RenderCopy(Renderer, ActorTexture->GetTexture(), NULL, &DestRect);
}

void Actor::Update(float dt)
{
	Location.X += (TargetLocation.X - Location.X) * MovementSpeed * dt;
	Location.Y += (TargetLocation.Y - Location.Y) * MovementSpeed * dt;
}

void Actor::MoveTo(float& dt, std::vector<Vec2>& Path)
{
	TargetLocation = Path.back();

	if (WithinRange(Location, TargetLocation))
	{
		Location = TargetLocation;
		Path.pop_back();
	}
}
