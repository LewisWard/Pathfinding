// Author : Lewis Ward
// Date: 29/08/2017
#include "NPC.h"

NPC::NPC()
{
	// set seed
	srand(time(0));

	// load texture
	ActorTexture = new Texture("images/bot.bmp");

	Moving = false;
	MovementSpeed = 1.25f;
	MoveAwayDirection = Location;
}

NPC::NPC(vec2 StartPosition, AStar* APathfinder, Player* ThePlayer)
{
	// set seed
	srand(time(0));

	Moving = false;
	Location = StartPosition;
	ActorTexture = new Texture("images/bot.bmp");
	MovementSpeed = 1.25f;
	MoveAwayDirection = Location;
	TargetLocation = Location;
	Pathfinder = APathfinder;
	APlayer = ThePlayer;
}

NPC::~NPC()
{

}

void NPC::loadNewTexture(const char* texture)
{
	// delete old texture and load the new one
	delete ActorTexture;
	ActorTexture = new Texture(texture);
}

void NPC::Update(float dt)
{
	// update player to move closer to the next waypoint
	Location.x += (TargetLocation.x - Location.x) * MovementSpeed * dt;
	Location.y += (TargetLocation.y - Location.y) * MovementSpeed * dt;

	ProcessLineOfSight();

	// If the Bot is in LoS of the Player and is not moving, create a path to move away
	if (SeePlayer && !Moving)
	{
		// Turn into a useable position for the pathfinder
		vec2 ValidLocation((int)MoveAwayDirection.x, (int)MoveAwayDirection.y);
	
		Path = Pathfinder->FindPath(Location, ValidLocation);
		Path.pop_back(); // This will be the current position the AI is in
	}
	
	// Move away from the player
	if (Path.size() > 0)
	{
		MoveTo(dt, Path);
	}
	else
	{
		isMoving(false);
	}

}
