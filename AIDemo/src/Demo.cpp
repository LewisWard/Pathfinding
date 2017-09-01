// Author : Lewis Ward
// Date: 29/08/2017
#include "Demo.h"
#include <math.h>

Demo::Demo()
{
	DemoWindow = new Window();
	Renderer = SDL_CreateRenderer(DemoWindow->window(), -1, 0);
	TheWorld = new World(30, 30);
	Pathfinder = new AStar();
	ThePlayer = new Player(vec2(5, 5), Pathfinder, &Mouse);
	IOEvents = new Events();
	BotOne = new NPC(vec2(8, 5), Pathfinder, ThePlayer);
	BotTwo = new NPC(vec2(5, 19), Pathfinder, ThePlayer);

	BotTwo->loadNewTexture("images/botB.bmp");
	FloorTexture = new Texture("images/point.bmp");
	WallTexture = new Texture("images/wall.bmp");

	Pathfinder->SetWorldSize(30, 30);
	BotOne->CreateTexture(Renderer);
	BotTwo->CreateTexture(Renderer);
	FloorTexture->createTexture(Renderer);
	WallTexture->createTexture(Renderer);
	TheWorld->createTexture(Renderer);
	TheWorld->SetPathfinder(Pathfinder);
	//TheWorld->LoadMap("Map.txt");

	Mouse = ThePlayer->GetLocation() * 20;
	ThePlayer->CreateTexture(Renderer);


	Pathfinder->AddCollision(vec2(6, 4));
	Pathfinder->AddCollision(vec2(6, 5));
	Pathfinder->AddCollision(vec2(6, 6));

	//Pathfinder->AddCollision(vec2(2, 2));
	//Pathfinder->AddCollision(vec2(2, 3));
	//Pathfinder->AddCollision(vec2(2, 4));
	//Pathfinder->AddCollision(vec2(2, 5));
	//Pathfinder->AddCollision(vec2(2, 7));
	//Pathfinder->AddCollision(vec2(5, 10));
	//Pathfinder->AddCollision(vec2(6, 10));
	//Pathfinder->AddCollision(vec2(6, 11));
	//Pathfinder->AddCollision(vec2(6, 12));
	//Pathfinder->AddCollision(vec2(7, 12));
	//Pathfinder->AddCollision(vec2(7, 13));
	//Pathfinder->AddCollision(vec2(6, 12));
	//Pathfinder->AddCollision(vec2(5, 10));
	//Pathfinder->AddCollision(vec2(5, 9));
	//Pathfinder->AddCollision(vec2(4, 10));
	//Pathfinder->AddCollision(vec2(3, 10));
	//Pathfinder->AddCollision(vec2(13, 13));
	//Pathfinder->AddCollision(vec2(13, 14));
	//Pathfinder->AddCollision(vec2(14, 14));
	//Pathfinder->AddCollision(vec2(7, 4));
	//Pathfinder->AddCollision(vec2(7, 5));
	//Pathfinder->AddCollision(vec2(7, 6));
	//Pathfinder->AddCollision(vec2(10, 10));
	//Pathfinder->AddCollision(vec2(8, 9));

	//Wall ATestWall(vec2(10, 10), 1);
	//rayCast ARay(vec2(12, 10), vec2(-1, 0));
	//bool R = ARay.NIntersect(ATestWall);
	//std::cout << R << std::endl;

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
	switch (IOEvents->eventQueue())
	{
		case 100: GameLoop = false; break;
		case 4: DrawPaths = (DrawPaths == true) ? false : true; break;
	}

	// If the user has left clicked with the left mouse button on a grid, recompute path
	if (0 == IOEvents->mouseQueue())
	{
		Mouse = IOEvents->getMouseLocation();
		ThePlayer->RecomputePath();
	}

	ThePlayer->Update(dt);
	BotOne->Update(dt);
	//BotTwo->Update(dt);
}

void Demo::Draw()
{
	SDL_SetRenderDrawColor(Renderer, 0.0f, 0.0f, 0.0f, 0.0f);
	SDL_RenderClear(Renderer);

	TheWorld->draw(Renderer);

	if (DrawPaths)
	{
		for (int i = 0; i < ThePlayer->GetPath().size(); ++i)
		{
			SDL_Rect destRect;
			destRect.w = 20.f;
			destRect.h = 20.f;
			destRect.x = ThePlayer->GetPath()[i].x * 20.f;
			destRect.y = ThePlayer->GetPath()[i].y * 20.f;
			SDL_RenderCopy(Renderer, FloorTexture->texture(), NULL, &destRect);
		}

		for (int i = 0; i < BotOne->GetPath().size(); ++i)
		{
			SDL_Rect destRect;
			destRect.w = 20.f;
			destRect.h = 20.f;
			destRect.x = BotOne->GetPath()[i].x * 20.f;
			destRect.y = BotOne->GetPath()[i].y * 20.f;
			SDL_RenderCopy(Renderer, FloorTexture->texture(), NULL, &destRect);
		}

		for (int i = 0; i < BotTwo->GetPath().size(); ++i)
		{
			SDL_Rect destRect;
			destRect.w = 20.f;
			destRect.h = 20.f;
			destRect.x = BotTwo->GetPath()[i].x * 20.f;
			destRect.y = BotTwo->GetPath()[i].y * 20.f;
			SDL_RenderCopy(Renderer, FloorTexture->texture(), NULL, &destRect);
		}

		for (int x = 0; x < 30 * 20; x += 20)
		{
			SDL_RenderDrawLine(Renderer, 0, x, 600, x);
			SDL_RenderDrawLine(Renderer, x, 0, x, 600);
		}
	}

	// draw walls
	std::vector<vec2> Walls = Pathfinder->GetCollisions();
	for (int i = 0; i < Walls.size(); ++i)
	{
		SDL_Rect destRect;
		destRect.w = 20;
		destRect.h = 20;
		destRect.x = Walls[i].x * 20;
		destRect.y = Walls[i].y * 20;
		SDL_RenderCopy(Renderer, WallTexture->texture(), NULL, &destRect);
	}

	ThePlayer->Draw(Renderer);
	BotOne->Draw(Renderer);
	BotTwo->Draw(Renderer);

	SDL_RenderDrawLine(Renderer, (BotOne->GetLocation().x * 20) + 10, (BotOne->GetLocation().y * 20) + 10,
		(ThePlayer->GetLocation().x * 20) + 10, (ThePlayer->GetLocation().y * 20) + 10);
	SDL_RenderDrawLine(Renderer, (BotTwo->GetLocation().x * 20) + 10, (BotTwo->GetLocation().y * 20) + 10,
		(ThePlayer->GetLocation().x * 20) + 10, (ThePlayer->GetLocation().y * 20) + 10);

	SDL_RenderDrawLine(Renderer, (BotOne->GetLocation().x * 20) + 10, (BotOne->GetLocation().y * 20) + 10,
		(BotOne->GetMoveAwayDirection().x * 20) + 10, (BotOne->GetMoveAwayDirection().y * 20) + 10);
	SDL_RenderDrawLine(Renderer, (BotTwo->GetLocation().x * 20) + 10, (BotTwo->GetLocation().y * 20) + 10,
		(BotTwo->GetMoveAwayDirection().x * 20) + 10, (BotTwo->GetMoveAwayDirection().y * 20) + 10);

	SDL_RenderPresent(Renderer);
}
