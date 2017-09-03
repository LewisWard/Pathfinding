// Author : Lewis Ward
// Date: 29/08/2017
#include "Player.h"

Player::Player()
{
	TargetLocation = Location;
	ActorTexture = new Texture(ASSET_DIR"player.bmp");
	MovementSpeed = 10.0f;
}

Player::~Player()
{
	// ActorTexture is deleted by ~Actor
}

void Player::Update(float dt)
{
	// update player to move closer to the next waypoint
	Location.X += (TargetLocation.X - Location.X) * MovementSpeed * dt;
	Location.Y += (TargetLocation.Y - Location.Y) * MovementSpeed * dt;

	if (IsAtPathEnd() || NewPath)
	{
		SetAtPathEnd(false);
		Path = Pathfinder->FindPath(GetLocation(), *MouseLocation / 20);
		NewPath = false;
	}
	
	// Move the player
	if (Path.size() > 0)
	{
		MoveTo(dt, Path);
	}
	else
	{
		SetAtPathEnd(true);
	}
}
