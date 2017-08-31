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

	void Update(float dt);

	void Draw();

	inline bool IsPlaying() { return GameLoop; }

private:
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
	bool GameLoop = true;
	bool DrawPaths = true;
};
