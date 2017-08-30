// Author : Lewis Ward
// Date: 29/08/2017
#include "World.h"

World::World()
{
	float width = 10;

	m_grids.resize(width * width);

	for (size_t y = 0; y < width; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			size_t index = y * width + x;

			m_grids[index].gridBounds.m_min.x = x * 50.0f;
			m_grids[index].gridBounds.m_min.y = y * 50.0f;
			m_grids[index].gridBounds.m_max.x = x * 50.0f + 50.0f;
			m_grids[index].gridBounds.m_max.y = y * 50.0f + 50.0f;

			m_grids[index].gridIndex = index;

			m_grids[index].walkable = true;
			m_grids[index].visited = false;
			m_grids[index].cost = 0.0f;
		}
	}

	for (int y = 0; y < width - 1; ++y)
	{
		for (int x = 0; x < width - 1; ++x)
		{
			m_indices.push_back((width * y) + x);
			m_indices.push_back((width * y) + x + 1);
			m_indices.push_back((width * y) + x + width);
			m_indices.push_back((width * y) + x + 1);
			m_indices.push_back((width * y) + x + width + 1);
			m_indices.push_back((width * y) + x + width);
		}
	}

	m_texture = new Texture("images/floor.bmp");
}

World::~World()
{
	delete m_texture;
}

void World::draw(SDL_Renderer* r)
{
	SDL_Rect destRect;
	destRect.w = 50;
	destRect.h = 50;

	for (size_t i = 0; i < m_grids.size(); ++i)
	{
		destRect.x = m_grids[i].gridBounds.m_min.x;
		destRect.y = m_grids[i].gridBounds.m_min.y;
		SDL_RenderCopy(r, m_texture->texture(), NULL, &destRect);
	}
}

int getIndex(vec2 position)
{
	// find the grid we are in
	for (size_t y = 0; y < 10; ++y)
	{
		for (size_t x = 0; x < 10; ++x)
		{
			size_t index = y * 10 + x;

			// test to see what grid we are in
			if (position.x >= (x * 50.0f) && position.y >= (y * 50.0f) &&
				position.x <= (x * 50.0f) + 50.0f && position.y <= (y * 50.0f + 50.0f))
			{
				return (int)index;
			}
		}
	}
}
