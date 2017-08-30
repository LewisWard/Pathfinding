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

	void Update(float dt);

	void Draw();

	inline bool IsPlaying() { return GameLoop; }

private:

	void ProcessLoS();

	Window* DemoWindow = nullptr;
	Texture* FloorTexture = nullptr;
	Texture* WallTexture = nullptr;
	std::vector<vec2> Path;
	std::vector<vec2> PathB1;
	std::vector<vec2> PathB2;
	SDL_Renderer* Renderer = nullptr;
	TheNewWorld* NewWorld = nullptr;
	AStarFast* Pathfinder = nullptr;
	Player* ThePlayer;
	Events* IOEvents;
	vec2 Mouse;
	vec2 InSight;


	NPC* BotOne = nullptr;
	NPC* BotTwo = nullptr;

	bool GameLoop = true;
	bool LineOfSight = true;
	bool DrawPaths = true;
	bool DrawGrids = true;
	bool MoveDirectionVector = false;
};
