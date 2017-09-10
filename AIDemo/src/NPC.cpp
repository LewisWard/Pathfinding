// Author : Lewis Ward
// Date: 29/08/2017
#include "NPC.h"

NPC::NPC()
{
	ActorTexture = new Texture(ASSET_DIR"bot.bmp");

	Moving = false;
	MovementSpeed = 3.5f;
	TimeToGeneratePath = 2.5f;
	MoveAwayDirection = Location;
}

NPC::NPC(Vec2 StartPosition, AStar* APathfinder, Player* ThePlayer)
{
	Moving = false;
	Location = StartPosition;
	ActorTexture = new Texture(ASSET_DIR"bot.bmp");
	MovementSpeed = 3.5f;
	TimeToGeneratePath = 2.5f;
	MoveAwayDirection = Location;
	TargetLocation = Location;
	Pathfinder = APathfinder;
	APlayer = ThePlayer;
}

NPC::~NPC()
{

}

void NPC::LoadNewTexture(const char* texture)
{
	// delete old texture and load the new one
	delete ActorTexture;
	ActorTexture = new Texture(texture);
}

void NPC::Update(float dt)
{
	// update player to move closer to the next waypoint
	Location.X += (TargetLocation.X - Location.X) * MovementSpeed * dt;
	Location.Y += (TargetLocation.Y - Location.Y) * MovementSpeed * dt;

	ProcessLineOfSight();

	// If the Bot is in LoS of the Player and is not moving, create a path to move away
	if (SeePlayer && !Moving)
	{
		GeneratePath();
	}
	else if (SeePlayer && MovingRandomPath)
	{
		// Stop moving if using a random path, on the next update will generate a new path
		MovingRandomPath = false;
		Path.clear();
	}
	else if (TimeNotMoving >= TimeToGeneratePath)
	{
		GenerateRandomPath();
		TimeNotMoving = 0.0f;
		MovingRandomPath = true;
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
		TimeNotMoving += dt;
	}
}

bool NPC::ProcessLineOfSight()
{
	Vec2 PlayerLocation = APlayer->GetLocation();
	Vec2 SelfLocation = Location;

	std::vector<Wall> RayHitWalls;
	Ray ARay(Location, Normalize(PlayerLocation - SelfLocation));

	// Generate direction vectors between origin and target (i.e Bot to Player)
	Vec2 DirectionToPlayer(SelfLocation.X - PlayerLocation.X, SelfLocation.Y - PlayerLocation.Y);

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

	float DistanceToPlayer = Length(PlayerLocation - SelfLocation);

	for (size_t i = 0; i < RayHitWalls.size(); i++)
	{
		// If the distance between the NPC and Wall is shorter then the distance between the NPC and Player, then a wall is in the way
		if (Length(RayHitWalls[i].GetCenter() - SelfLocation) < DistanceToPlayer)
		{
			HitTarget = true;
			break; // Quick exit as there is at least 1 Wall between the NPC and Player
		}
	}

	float Range = 3.0f;
	MoveAwayDirection = ARay.Cast(DirectionToPlayer, Range);
	FindValidLocation(ARay, DirectionToPlayer, Range, 5.0f);
	
	// Is within line of sight and needs a new path to move away
	SeePlayer = !HitTarget;
	return !HitTarget;
}

void NPC::FindValidLocation(Ray& ARay, Vec2 SearchDirection, float StartRange, float EndRange)
{
	float Start = StartRange;
	MoveAwayDirection.X = (int)MoveAwayDirection.X;
	MoveAwayDirection.Y = (int)MoveAwayDirection.Y;

	// Check that the selected MoveAwayDirection location is valid to move to, otherwise, try to find another valid location to move to
	if (Pathfinder->DetectCollision(MoveAwayDirection))
	{
		// Increase the search range
		while (Start < EndRange)
		{
			Start++;
			MoveAwayDirection = ARay.Cast(SearchDirection, Start);

			// If a valid location is found, quick exit
			if (Pathfinder->DetectCollision(MoveAwayDirection))
			{
				// If we are still selecting an invalid location, NPC is selecting a location off of the world
				// So select the first valid location to the left/right/up/down direction. A direction that is valid must
				// also be a direction that takes teh NPC away from the player
				Vec2 MoveTop(0.f, -1.0f);
				Vec2 MoveRight(1.f, 0.0f);
				Vec2 MoveBottom(0.f, 1.0f);
				Vec2 MoveLeft(-1.f, 0.0f);

				Vec2 PlayerLocation = APlayer->GetLocation();

				MoveAwayDirection = ARay.Cast(MoveTop, StartRange);
				float L1 = Length(MoveAwayDirection - PlayerLocation);
				float L2 = Length(Location - PlayerLocation);
				if (!Pathfinder->DetectCollision(MoveAwayDirection) && L1 > L2)
					break;

				MoveAwayDirection = ARay.Cast(MoveRight, StartRange);
				L1 = Length(MoveAwayDirection - PlayerLocation);
				L2 = Length(Location - PlayerLocation);
				if (!Pathfinder->DetectCollision(MoveAwayDirection) && L1 > L2)
					break;

				MoveAwayDirection = ARay.Cast(MoveBottom, StartRange);
				L1 = Length(MoveAwayDirection - PlayerLocation);
				L2 = Length(Location - PlayerLocation);
				if (!Pathfinder->DetectCollision(MoveAwayDirection) && L1 > L2)
					break;

				MoveAwayDirection = ARay.Cast(MoveLeft, StartRange);
				L1 = Length(MoveAwayDirection - PlayerLocation);
				L2 = Length(Location - PlayerLocation);
				if (!Pathfinder->DetectCollision(MoveAwayDirection) && L1 > L2)
					break;

			}
			else
			{
				// Is a valid location
				break;
			}
		}
	}
}

void NPC::GeneratePath()
{
	Vec2 ValidLocation((int)MoveAwayDirection.X, (int)MoveAwayDirection.Y);

	// Make sure the location stays within the world bounds
	if (ValidLocation.X > Pathfinder->GetWorldSize().X - 1)
		ValidLocation.X = Pathfinder->GetWorldSize().X - 1;
	if (ValidLocation.Y > Pathfinder->GetWorldSize().Y - 1)
		ValidLocation.Y = Pathfinder->GetWorldSize().Y - 1;

	Path = Pathfinder->FindPath(Location, ValidLocation);
	Path.pop_back(); // This will be the current position the AI is in
}

void NPC::GenerateRandomPath()
{
	Vec2 ValidLocation = Pathfinder->RandomValidPosition();

	Path = Pathfinder->FindPath(Location, ValidLocation);
	Path.pop_back(); // This will be the current position the AI is in
}

