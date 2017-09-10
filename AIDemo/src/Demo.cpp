// Author : Lewis Ward
// Date: 29/08/2017
#include "Demo.h"
#include <math.h>

Demo::Demo()
{
	DemoWindow = new Window();
	Renderer = SDL_CreateRenderer(DemoWindow->GetWindow(), -1, 0);
	TheWorld = new World(30, 30);
	Pathfinder = new AStar();
	ThePlayer = new Player(Vec2(5, 5), Pathfinder, &Mouse);
	IOEvents = new Events();
	BotOne = new NPC(Vec2(8, 5), Pathfinder, ThePlayer);
	BotTwo = new NPC(Vec2(5, 19), Pathfinder, ThePlayer);

	BotTwo->LoadNewTexture(ASSET_DIR"botB.bmp");
	PathTexture = new Texture(ASSET_DIR"point.bmp");
	BotPathTexture = new Texture(ASSET_DIR"pointBot.bmp");
	WallTexture = new Texture(ASSET_DIR"wall.bmp");

	Pathfinder->SetWorldSize(30, 30);
	BotOne->CreateTexture(Renderer);
	BotTwo->CreateTexture(Renderer);
	PathTexture->CreateTexture(Renderer);
	BotPathTexture->CreateTexture(Renderer);
	WallTexture->CreateTexture(Renderer);
	TheWorld->CreateTexture(Renderer);
	TheWorld->SetPathfinder(Pathfinder);
	TheWorld->LoadMap(ASSET_DIR"Map.txt");

	Mouse = ThePlayer->GetLocation() * 20;
	ThePlayer->CreateTexture(Renderer);
}

Demo::~Demo()
{
	delete WallTexture;
	delete BotPathTexture;
	delete PathTexture;
	delete BotTwo;
	delete BotOne;
	delete IOEvents;
	delete ThePlayer;
	delete Pathfinder;
	delete TheWorld;
	SDL_DestroyRenderer(Renderer);
	Renderer = nullptr;
	delete DemoWindow;
}

void Demo::Update(float dt)
{
	// Handle input, Esc key to quit and D key to draw paths (On/Off)
	switch (IOEvents->EventQueue())
	{
		case 100: GameLoop = false; break;
		case 4: DebugDraw = !DebugDraw; break;
	}

	// If the user has left clicked with the left mouse button on a grid, recompute path
	if (0 == IOEvents->MouseQueue())
	{
		Mouse = IOEvents->GetMouseLocation();
		ThePlayer->RecomputePath();
	}

	ThePlayer->Update(dt);
	BotOne->Update(dt);
	BotTwo->Update(dt);
}

void Demo::Draw()
{
	SDL_SetRenderDrawColor(Renderer, 0, 128, 0, 0);
	SDL_RenderClear(Renderer);

	TheWorld->Draw(Renderer, true);

	// --------------------------- Debug Drawing --------------------------- //
	if (DebugDraw)
	{
		SDL_Rect DestRect;
		DestRect.w = 20;
		DestRect.h = 20;

		for (size_t i = 0; i < ThePlayer->GetPath().size(); ++i)
		{
			DestRect.x = (int)(ThePlayer->GetPath()[i].X * 20.f);
			DestRect.y = (int)(ThePlayer->GetPath()[i].Y * 20.f);
			SDL_RenderCopy(Renderer, PathTexture->GetTexture(), NULL, &DestRect);
		}

		for (size_t i = 0; i < BotOne->GetPath().size(); ++i)
		{
			DestRect.x = (int)(BotOne->GetPath()[i].X * 20.f);
			DestRect.y = (int)(BotOne->GetPath()[i].Y * 20.f);
			SDL_RenderCopy(Renderer, BotPathTexture->GetTexture(), NULL, &DestRect);
		}

		for (size_t i = 0; i < BotTwo->GetPath().size(); ++i)
		{
			DestRect.x = (int)(BotTwo->GetPath()[i].X * 20.f);
			DestRect.y = (int)(BotTwo->GetPath()[i].Y * 20.f);
			SDL_RenderCopy(Renderer, BotPathTexture->GetTexture(), NULL, &DestRect);
		}
	}
	// --------------------------------------------------------------------- //


	// Draw walls
	std::vector<Vec2> Walls = Pathfinder->GetCollisions();
	SDL_Rect DestRect;
	DestRect.w = 20;
	DestRect.h = 20;
	for (size_t i = 0; i < Walls.size(); ++i)
	{
		DestRect.x = (int)(Walls[i].X * 20);
		DestRect.y = (int)(Walls[i].Y * 20);
		SDL_RenderCopy(Renderer, WallTexture->GetTexture(), NULL, &DestRect);
	}

	ThePlayer->Draw(Renderer);
	BotOne->Draw(Renderer);
	BotTwo->Draw(Renderer);

	// --------------------------- Debug Drawing --------------------------- //
	if (DebugDraw)
	{
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
		SDL_RenderDrawLine(Renderer, (int)((BotOne->GetLocation().X * 20) + 10), (int)((BotOne->GetLocation().Y * 20) + 10),
			(int)((ThePlayer->GetLocation().X * 20) + 10), (int)((ThePlayer->GetLocation().Y * 20) + 10));
		SDL_RenderDrawLine(Renderer, (int)((BotTwo->GetLocation().X * 20) + 10), (int)((BotTwo->GetLocation().Y * 20) + 10),
			(int)((ThePlayer->GetLocation().X * 20) + 10), (int)((ThePlayer->GetLocation().Y * 20) + 10));

		SDL_RenderDrawLine(Renderer, (int)((BotOne->GetLocation().X * 20) + 10), (int)((BotOne->GetLocation().Y * 20) + 10),
			(int)((BotOne->GetMoveAwayDirection().X * 20) + 10), (int)((BotOne->GetMoveAwayDirection().Y * 20) + 10));
		SDL_RenderDrawLine(Renderer, (int)((BotTwo->GetLocation().X * 20) + 10), (int)((BotTwo->GetLocation().Y * 20) + 10),
			(int)((BotTwo->GetMoveAwayDirection().X * 20) + 10), (int)((BotTwo->GetMoveAwayDirection().Y * 20) + 10));

		for (int x = 0; x < 30 * 20; x += 20)
		{
			SDL_RenderDrawLine(Renderer, 0, x, 600, x);
			SDL_RenderDrawLine(Renderer, x, 0, x, 600);
		}
	}
	// --------------------------------------------------------------------- //

	SDL_RenderPresent(Renderer);
}
