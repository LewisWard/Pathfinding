// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "Actor.h"
#include "Player.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief  NPC/Bots characters
//----------------------------------------------------------------------------------------------------------------------
class NPC : public Actor
{
public:
	/// \brief Constr
	NPC();

	/// \brief Constr
	NPC(vec2 StartPosition, AStar* APathfinder, Player* ThePlayer);

	/// \brief Destr
	~NPC();

	/// \brief update the NPC
	/// \prama float delta time
	/// \prama vec2 new position to move to
	void Update(float dt) override;

	//void MoveTo(float& dt, std::vector<vec2>& Path) override;

	/// \brief load a new texture
	/// \prama char* texture file name
	void loadNewTexture(const char* texture);

	/// \brief set is the NPC is moving or not
	/// \prama bool
	inline void isMoving(bool M) { Moving = M; }

	/// \brief get is the NPC is moving or not
	/// \prama bool
	inline bool getIsMoving() { return Moving; }

	inline void SetPlayerInSight(bool S) { SeePlayer = S; }

	inline bool IsPlayerInSight() { return SeePlayer; }

	inline const std::vector<vec2>& GetPath() { return Path; }

	inline vec2 GetPlayerSightRay() { return PlayerInSightRay; }

	inline vec2 GetMoveAwayDirection() { return MoveAwayDirection; }

private:
	std::vector<vec2> Path;
	AStar* Pathfinder = nullptr;
	Player* APlayer = nullptr;
	vec2 MoveAwayDirection;
	vec2 PlayerInSightRay;
	bool Moving; ///< is the NPC moving
	bool SeePlayer = false;

	bool ProcessLineOfSight()
	{
		rayCast RaySight;

		// Generate direction vectors between origin and target (i.e Bot to Player)
		vec2 DirectionToPlayer(Location.x - APlayer->GetLocation().x, Location.y - APlayer->GetLocation().y);
		PlayerInSightRay = RaySight.cast(APlayer->GetLocation(), DirectionToPlayer, length(Location - APlayer->GetLocation()));

		bool HitTarget = RaySight.Intersect(Pathfinder->GetCollisions(), APlayer->GetLocation(), Location);

		// Is within line of sight and needs a new path to move away
		if (HitTarget)
		{
			MoveAwayDirection = RaySight.cast(APlayer->GetLocation(), DirectionToPlayer, length(APlayer->GetLocation() - Location) + 3.0f);
			SeePlayer = true;
			return true;
		}
		else
		{
			SeePlayer = false;
			return false;
		}
	}
	
};
