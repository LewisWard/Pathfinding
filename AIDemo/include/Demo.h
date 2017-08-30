// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "Texture.h"
#include "Player.h"
#include "Wall.h"
#include "NPC.h"
#include "Window.h"

class Demo
{
public:

	Demo();

	~Demo();

	void MoveTo(float& dt, Player& player, std::vector<vec2>& path);
	void MoveTo(float& dt, NPC& ANPC, std::vector<vec2>& Path);

	void Update(float dt);

	void Draw();

	inline bool IsPlaying() { return GameLoop; }

private:

	void ProcessLoS();

	std::vector<vec2> Path;
	std::vector<vec2> PathB1;
	std::vector<vec2> PathB2;
	Window* DemoWindow = nullptr;
	Texture* FloorTexture = nullptr;
	Texture* WallTexture = nullptr;
	NPC* BotOne = nullptr;
	NPC* BotTwo = nullptr;
	SDL_Renderer* Renderer = nullptr;
	TheNewWorld* NewWorld = nullptr;
	AStar* Pathfinder = nullptr;
	Player* ThePlayer;
	Events* IOEvents;
	vec2 Mouse;
	vec2 PlayerInSightA, MoveAwayA;
	vec2 PlayerInSightB, MoveAwayB;
	bool GameLoop = true;
	bool LineOfSight = true;
	bool DrawPaths = true;
	bool DrawGrids = true;
	bool MoveDirectionVector = true;
};
