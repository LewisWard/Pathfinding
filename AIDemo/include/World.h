// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "PathfindingAStar.h"
#include <time.h>

struct Grid
{
	AABB gridBounds;
	int gridIndex;
	bool walkable;
	bool visited;
	float cost;
};

class World
{
public:

	/// \brief Constr
	World(int WorldMaxPosX, int WorldMaxPosY);

	/// \brief Destr
	~World();

	/// \brief draw the world
	/// \prama SDL_Renderer* renderer
	void draw(SDL_Renderer* r);

	/// \brief create the texture
	/// \prama SDL_Renderer* renderer
	inline void createTexture(SDL_Renderer* r) { m_texture->createTexture(r); }

	inline vec2 GetWorldMax() { return WorldMax; }

	void LoadMap(const char* Filename);

	inline void  SetPathfinder(AStar* APathfinder) { Pathfinder = APathfinder; }

private:
	vec2 WorldMin;
	vec2 WorldMax;
	int WorldWidth;
	int WorldHeight;
	Texture* m_texture = nullptr;
	AStar* Pathfinder = nullptr;
};