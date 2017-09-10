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
	Texture* PathTexture = nullptr;
	Texture* BotPathTexture = nullptr;
	Texture* WallTexture = nullptr;
	NPC* BotOne = nullptr;
	NPC* BotTwo = nullptr;
	SDL_Renderer* Renderer = nullptr;
	World* TheWorld = nullptr;
	AStar* Pathfinder = nullptr;
	Player* ThePlayer;
	Events* IOEvents;
	Vec2 Mouse;
	bool GameLoop = true;
	bool DebugDraw = false;
};
