// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "PathfindingAStar.h"
#include <time.h>

class World
{
public:

	/// \brief Constr
	World(int WorldMaxPosX, int WorldMaxPosY);

	/// \brief Destr
	~World();

	/// \brief draw the world
	/// \prama SDL_Renderer* renderer
	void Draw(SDL_Renderer* Renderer, bool UseBackgroundTexture);

	/// \breif Loads a map from a text file
	/// \prama char* Filename
	void LoadMap(const char* Filename);

	/// \brief create the texture
	/// \prama SDL_Renderer* renderer
	inline void CreateTexture(SDL_Renderer* r) { WorldTexture->CreateTexture(r); }

	inline Vec2 GetWorldMax() { return WorldMax; }

	inline void SetPathfinder(AStar* APathfinder) { Pathfinder = APathfinder; }

private:
	Texture* WorldTexture = nullptr;
	AStar* Pathfinder = nullptr;
	Vec2 WorldMin;
	Vec2 WorldMax;
	int WorldWidth;
	int WorldHeight;
};