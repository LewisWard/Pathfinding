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

	BotTwo->LoadNewTexture("images/botB.bmp");
	FloorTexture = new Texture("images/point.bmp");
	WallTexture = new Texture("images/wall.bmp");

	Pathfinder->SetWorldSize(30, 30);
	BotOne->CreateTexture(Renderer);
	BotTwo->CreateTexture(Renderer);
	FloorTexture->CreateTexture(Renderer);
	WallTexture->CreateTexture(Renderer);
	TheWorld->CreateTexture(Renderer);
	TheWorld->SetPathfinder(Pathfinder);
	TheWorld->LoadMap("Map.txt");

	Mouse = ThePlayer->GetLocation() * 20;
	ThePlayer->CreateTexture(Renderer);
}

Demo::~Demo()
{
	delete WallTexture;
	delete FloorTexture;
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
		case 4: DrawPaths = (DrawPaths == true) ? false : true; break;
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
	SDL_SetRenderDrawColor(Renderer, 0.0f, 0.0f, 0.0f, 0.0f);
	SDL_RenderClear(Renderer);

	TheWorld->draw(Renderer);

	// --------------------------- Debug Drawing --------------------------- //
	if (DrawPaths)
	{
		SDL_Rect destRect;
		destRect.w = 20.f;
		destRect.h = 20.f;

		for (int i = 0; i < ThePlayer->GetPath().size(); ++i)
		{
			destRect.x = ThePlayer->GetPath()[i].X * 20.f;
			destRect.y = ThePlayer->GetPath()[i].Y * 20.f;
			SDL_RenderCopy(Renderer, FloorTexture->GetTexture(), NULL, &destRect);
		}

		for (int i = 0; i < BotOne->GetPath().size(); ++i)
		{
			destRect.x = BotOne->GetPath()[i].X * 20.f;
			destRect.y = BotOne->GetPath()[i].Y * 20.f;
			SDL_RenderCopy(Renderer, FloorTexture->GetTexture(), NULL, &destRect);
		}

		for (int i = 0; i < BotTwo->GetPath().size(); ++i)
		{
			destRect.x = BotTwo->GetPath()[i].X * 20.f;
			destRect.y = BotTwo->GetPath()[i].Y * 20.f;
			SDL_RenderCopy(Renderer, FloorTexture->GetTexture(), NULL, &destRect);
		}

		for (int x = 0; x < 30 * 20; x += 20)
		{
			SDL_RenderDrawLine(Renderer, 0, x, 600, x);
			SDL_RenderDrawLine(Renderer, x, 0, x, 600);
		}
	}
	// --------------------------------------------------------------------- //


	// draw walls
	std::vector<Vec2> Walls = Pathfinder->GetCollisions();
	SDL_Rect destRect;
	destRect.w = 20;
	destRect.h = 20;
	for (int i = 0; i < Walls.size(); ++i)
	{
		destRect.x = Walls[i].X * 20;
		destRect.y = Walls[i].Y * 20;
		SDL_RenderCopy(Renderer, WallTexture->GetTexture(), NULL, &destRect);
	}

	ThePlayer->Draw(Renderer);
	BotOne->Draw(Renderer);
	BotTwo->Draw(Renderer);

	// --------------------------- Debug Drawing --------------------------- //
	SDL_RenderDrawLine(Renderer, (BotOne->GetLocation().X * 20) + 10, (BotOne->GetLocation().Y * 20) + 10,
		(ThePlayer->GetLocation().X * 20) + 10, (ThePlayer->GetLocation().Y * 20) + 10);
	SDL_RenderDrawLine(Renderer, (BotTwo->GetLocation().X * 20) + 10, (BotTwo->GetLocation().Y * 20) + 10,
		(ThePlayer->GetLocation().X * 20) + 10, (ThePlayer->GetLocation().Y * 20) + 10);

	SDL_RenderDrawLine(Renderer, (BotOne->GetLocation().X * 20) + 10, (BotOne->GetLocation().Y * 20) + 10,
		(BotOne->GetMoveAwayDirection().X * 20) + 10, (BotOne->GetMoveAwayDirection().Y * 20) + 10);
	SDL_RenderDrawLine(Renderer, (BotTwo->GetLocation().X * 20) + 10, (BotTwo->GetLocation().Y * 20) + 10,
		(BotTwo->GetMoveAwayDirection().X * 20) + 10, (BotTwo->GetMoveAwayDirection().Y * 20) + 10);
	// --------------------------------------------------------------------- //

	SDL_RenderPresent(Renderer);
}
