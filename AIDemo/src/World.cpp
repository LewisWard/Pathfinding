// Author : Lewis Ward
// Date: 29/08/2017
#include "World.h"
#include <fstream>
#include <string>

World::World(int WorldMaxPosX, int WorldMaxPosY)
{
	WorldMin = vec2(0.f, 0.f);
	WorldMax = vec2(WorldMaxPosX * 25, WorldMaxPosY * 25);
	WorldWidth = WorldMaxPosX * 25;
	WorldHeight = WorldMaxPosY * 25;
	m_texture = new Texture("images/floor.bmp");

	// set seed
	srand(time(0));
}

World::~World()
{
	delete m_texture;
	Pathfinder = nullptr;
}

void World::draw(SDL_Renderer* r)
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

void World::LoadMap(const char* Filename)
{
	std::string FileLine;
	std::ifstream InputFileStream(Filename);

	// Open the file
	if (InputFileStream.is_open())
	{
		int LineIndex = 0;

		// Not the end of the file yet
		while (!InputFileStream.eof())
		{
			std::getline(InputFileStream, FileLine);

			// For each char in the line, check the type to work out what it is
			for (size_t i = 0; i < FileLine.length(); i++)
			{
				// Find type of position				
				if (FileLine[i] == 'w')
				{
					Pathfinder->AddCollision(vec2(i, LineIndex));
				}
			}

			LineIndex++;
		}
	}

	InputFileStream.close();
}
