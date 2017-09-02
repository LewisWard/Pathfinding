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
	NPC(Vec2 StartPosition, AStar* APathfinder, Player* ThePlayer);

	/// \brief Destr
	~NPC();

	/// \brief update the NPC
	/// \prama float delta time
	void Update(float dt) override;

	/// \brief load a new texture
	/// \prama char* texture file name
	void LoadNewTexture(const char* texture);

	/// \brief set is the NPC is moving or not
	/// \prama bool
	inline void IsMoving(bool M) { Moving = M; }

	/// \brief get is the NPC is moving or not
	/// \prama bool
	inline bool getIsMoving() { return Moving; }

	inline void SetPlayerInSight(bool S) { SeePlayer = S; }

	inline bool IsPlayerInSight() { return SeePlayer; }

	inline const std::vector<Vec2>& GetPath() { return Path; }

	inline Vec2 GetMoveAwayDirection() { return MoveAwayDirection; }

private:
	std::vector<Vec2> Path;
	AStar* Pathfinder = nullptr;
	Player* APlayer = nullptr;
	Vec2 MoveAwayDirection;
	bool Moving; ///< is the NPC moving
	bool SeePlayer = false;

	/// \brief  Returns if the player is in line of sight of the NPC
	/// \return bool, true if in LoS
	bool ProcessLineOfSight();
	
	/// \brief Sets MoveAwayDirection to a valid location, searches for a valid location within range
	/// \prama Ray
	/// \prama vec3 search direction
	/// \prama float start range
	/// \prama float the maximum range
	void FindValidLocation(Ray& ARay, Vec2 SearchDirection, float StartRange, float EndRange);

};
