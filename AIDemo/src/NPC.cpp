// Author : Lewis Ward
// Date: 29/08/2017
#include "NPC.h"

NPC::NPC()
{
	ActorTexture = new Texture("images/bot.bmp");

	Moving = false;
	MovementSpeed = 3.5f;
	MoveAwayDirection = Location;
}

NPC::NPC(vec2 StartPosition, AStar* APathfinder, Player* ThePlayer)
{
	Moving = false;
	Location = StartPosition;
	ActorTexture = new Texture("images/bot.bmp");
	MovementSpeed = 3.25f;
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
		vec2 ValidLocation;

		// Turn into a useable position for the pathfinder, handles rounding 
		if (APlayer->GetLocation().x < Location.x)
			ValidLocation.x = (int)MoveAwayDirection.x + 1;
		else
			ValidLocation.x = (int)MoveAwayDirection.x;

		if (APlayer->GetLocation().y < Location.y)
			ValidLocation.y = (int)MoveAwayDirection.y + 1;
		else
			ValidLocation.y = (int)MoveAwayDirection.y;
	
		Path = Pathfinder->FindPath(Location, ValidLocation);
		Path.pop_back(); // This will be the current position the AI is in
	}

	// Move away from the player
	if (Path.size() > 0)
	{
		MoveTo(dt, Path);
		Moving = true;
	}
	else
	{
		Moving = false;
	}
}

bool NPC::ProcessLineOfSight()
{
	vec2 PlayerLocation = APlayer->GetLocation();
	vec2 SelfLocation = Location;

	std::vector<Wall> RayHitWalls;
	RayCast ARay(Location, normalize(PlayerLocation - SelfLocation));

	// Generate direction vectors between origin and target (i.e Bot to Player)
	vec2 DirectionToPlayer(SelfLocation.x - PlayerLocation.x, SelfLocation.y - PlayerLocation.y);

	bool HitTarget = false;

	for (size_t i = 0; i < Pathfinder->GetCollisions().size(); i++)
	{
		Wall NewWall(Pathfinder->GetCollisions()[i], 0.5f);
		HitTarget = ARay.Intersect(NewWall);

		// If a wall has been hit, add it to the array to check if it is in front of the player or not
		if (HitTarget == true)
		{
			RayHitWalls.push_back(NewWall);
		}
	}

	float DistanceToPlayer = length(PlayerLocation - SelfLocation);

	for (size_t i = 0; i < RayHitWalls.size(); i++)
	{
		// If the distance between the NPC and Wall is shorter then the distance between the NPC and Player, then a wall is in the way
		if (length(RayHitWalls[i].getCenter() - SelfLocation) < DistanceToPlayer)
		{
			HitTarget = true;
			break; // Quick exit as there is at least 1 Wall between the NPC and Player
		}
	}

	MoveAwayDirection = ARay.Cast(DirectionToPlayer, 2.0f);
	
	// Is within line of sight and needs a new path to move away
	SeePlayer = !HitTarget;
	return !HitTarget;
}
