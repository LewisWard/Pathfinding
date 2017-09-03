// Author : Lewis Ward
// Date: 29/08/2017
#include "World.h"
#include <fstream>
#include <string>

World::World(int WorldMaxPosX, int WorldMaxPosY)
{
	WorldMin = Vec2(0.f, 0.f);
	WorldMax = Vec2((float)(WorldMaxPosX * 25), (float)(WorldMaxPosY * 25));
	WorldWidth = WorldMaxPosX * 25;
	WorldHeight = WorldMaxPosY * 25;
	WorldTexture = new Texture(ASSET_DIR"floor.bmp");
}

World::~World()
{
	delete WorldTexture;
	Pathfinder = nullptr;
}

void World::Draw(SDL_Renderer* Renderer, bool UseBackgroundTexture)
{
	SDL_Rect DestRect;
	DestRect.w = 20;
	DestRect.h = 20;

	// Draw the world texture or just leave it blank (i.e. the colour the screen is cleared to)
	if (UseBackgroundTexture)
	{
		for (int x = 0; x < WorldWidth; ++x)
		{
			for (int y = 0; y < WorldHeight; ++y)
			{
				DestRect.x = x * 20;
				DestRect.y = y * 20;
				SDL_RenderCopy(Renderer, WorldTexture->GetTexture(), NULL, &DestRect);
			}
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
					Pathfinder->AddCollision(Vec2((float)i, (float)LineIndex));
				}
			}

			LineIndex++;
		}
	}

	InputFileStream.close();
}
