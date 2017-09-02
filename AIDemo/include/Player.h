// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	/// \brief Constr
	Player();

	Player(Vec2 SpawnLocation, AStar* APathfinder, Vec2* Mouse) : Actor(SpawnLocation), Pathfinder(APathfinder), MouseLocation(Mouse)
	{
		ActorTexture = new Texture("images/player.bmp");
	}

	/// \brief Destr
	~Player();

	void Update(float dt) override;

	inline const std::vector<Vec2>& GetPath() { return Path; }

	inline void RecomputePath() { NewPath = true; }

private:
	std::vector<Vec2> Path;
	AStar* Pathfinder = nullptr;
	Vec2* MouseLocation = nullptr;
	bool NewPath = false;
};
