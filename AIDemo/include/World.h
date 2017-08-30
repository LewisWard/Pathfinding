// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "Window.h"
#include <vector>
#include "Texture.h"
#include "AABB.h"

/// \brief get a grid index 
/// \prama vec2 grid position
/// \return grid index
int getIndex(vec2 position);

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
	World();

	/// \brief Destr
	~World();
	
	/// \brief draw the world
	/// \prama SDL_Renderer* renderer
	void draw(SDL_Renderer* r);

	/// \brief create the texture
	/// \prama SDL_Renderer* renderer
	inline void createTexture(SDL_Renderer* r)
	{ m_texture->createTexture(r); }

	/// \brief get all the grids that make up the world
	/// \return std::vector<Grid> grids
	inline std::vector<Grid> getGrids()
	{ return m_grids; }

private:
	std::vector<Grid> m_grids; ///< grids within the world
	std::vector<int> m_indices; ///< grid indices
	Texture* m_texture; ///< texture
};

/// \brief setup delta time
void initTimerDT();

/// \brief update delta time
/// \return delta time
float updateTimerDT();


class TheNewWorld
{
public:
	/// \brief Constr
	TheNewWorld(int WorldMaxPosX, int WorldMaxPosY)
	{
		WorldMin = vec2(0.f, 0.f);
		WorldMax = vec2(WorldMaxPosX * 25, WorldMaxPosY * 25);
		WorldWidth = WorldMaxPosX * 25;
		WorldHeight = WorldMaxPosY * 25;
		m_texture = new Texture("images/floor.bmp");
	}

	/// \brief Destr
	~TheNewWorld()
	{
		delete m_texture;
	}

	/// \brief draw the world
	/// \prama SDL_Renderer* renderer
	void draw(SDL_Renderer* r)
	{
		SDL_Rect destRect;
		destRect.w = 1 + 25;
		destRect.h = 1 + 25;

		for (int x = 0; x < WorldWidth; ++x)
		{
			for (int y = 0; y < WorldHeight; ++y)
			{
				destRect.x = x * 25;
				destRect.y = y * 25;
				SDL_RenderCopy(r, m_texture->texture(), NULL, &destRect);
			}
		}
	}

	/// \brief create the texture
	/// \prama SDL_Renderer* renderer
	inline void createTexture(SDL_Renderer* r)
	{
		m_texture->createTexture(r);
	}

	inline vec2 GetWorldMax() { return WorldMax; }

private:
	vec2 WorldMin;
	vec2 WorldMax;
	int WorldWidth;
	int WorldHeight;
	Texture* m_texture; ///< texture
};