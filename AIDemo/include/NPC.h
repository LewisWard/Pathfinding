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
	/// \prama Vec2 new position to move to
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

	bool ProcessLineOfSight();
	
	void FindValidLocation(Ray& ARay, Vec2 SearchDirection, float StartRange, float EndRange);

};
