// Author : Lewis Ward
// Date: 29/08/2017
#include "Demo.h"
#include <math.h>

Demo::Demo()
{
	DemoWindow = new Window();
	Renderer = SDL_CreateRenderer(DemoWindow->window(), -1, 0);
	NewWorld = new TheNewWorld(30, 30);
	Pathfinder = new AStar();
	ThePlayer = new Player(vec2(5, 5), Pathfinder, &Mouse);
	IOEvents = new Events();
	BotOne = new NPC(vec2(8, 8), Pathfinder, ThePlayer);
	BotTwo = new NPC(vec2(5, 16), Pathfinder, ThePlayer);

	BotTwo->loadNewTexture("images/botB.bmp");
	FloorTexture = new Texture("images/point.bmp");
	WallTexture = new Texture("images/wall.bmp");

	BotOne->CreateTexture(Renderer);
	BotTwo->CreateTexture(Renderer);
	FloorTexture->createTexture(Renderer);
	WallTexture->createTexture(Renderer);
	NewWorld->createTexture(Renderer);

	Pathfinder->SetWorldSize(30, 30);
	Pathfinder->AddCollision(vec2(2, 2));
	Pathfinder->AddCollision(vec2(2, 3));
	Pathfinder->AddCollision(vec2(2, 4));
	Pathfinder->AddCollision(vec2(2, 5));
	Pathfinder->AddCollision(vec2(5, 10));
	Pathfinder->AddCollision(vec2(6, 10));
	Pathfinder->AddCollision(vec2(6, 11));
	Pathfinder->AddCollision(vec2(6, 12));
	Pathfinder->AddCollision(vec2(7, 12));
	Pathfinder->AddCollision(vec2(7, 13));
	Pathfinder->AddCollision(vec2(6, 12));
	Pathfinder->AddCollision(vec2(5, 10));
	Pathfinder->AddCollision(vec2(5, 9));
	Pathfinder->AddCollision(vec2(4, 10));
	Pathfinder->AddCollision(vec2(3, 10));
	Pathfinder->AddCollision(vec2(13, 13));
	Pathfinder->AddCollision(vec2(13, 14));
	Pathfinder->AddCollision(vec2(14, 14));


	Pathfinder->AddCollision(vec2(9, 7));
	Pathfinder->AddCollision(vec2(9, 8));
	Pathfinder->AddCollision(vec2(9, 9));
	Pathfinder->AddCollision(vec2(10, 10));
	Pathfinder->AddCollision(vec2(8, 9));

	Mouse = vec2(5, 5) * 20;
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
	delete NewWorld;
	SDL_DestroyRenderer(Renderer);
	Renderer = nullptr;
	delete DemoWindow;
}

void Demo::Update(float dt)
{
	// Handle input
	switch (IOEvents->eventQueue())
	{
		case 100: GameLoop = false; break;
		case 1: LineOfSight = (LineOfSight == true) ? false : true; break; // turn on or off
		case 2: DrawPaths = (DrawPaths == true) ? false : true; break; // turn on or off
		case 3: DrawGrids = (DrawGrids == true) ? false : true; break; // turn on or off
		case 4: MoveDirectionVector = (MoveDirectionVector == true) ? false : true; break; // turn on or off
	}

	// If the user has left clicked with the left mouse button on a grid, recompute path
	if (0 == IOEvents->mouseQueue())
	{
		Mouse = IOEvents->getMouseLocation();
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

	NewWorld->draw(Renderer);

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

	// draw certain visuals if they are turned on or not
	if (LineOfSight)
	{
		SDL_RenderDrawLine(Renderer, (BotOne->GetPlayerSightRay().x * 20) + 10, (BotOne->GetPlayerSightRay().y * 20) + 10,
											(ThePlayer->GetLocation().x * 20) + 10, (ThePlayer->GetLocation().y * 20) + 10);
		SDL_RenderDrawLine(Renderer, (BotTwo->GetPlayerSightRay().x * 20) + 10, (BotTwo->GetPlayerSightRay().y * 20) + 10,
											(ThePlayer->GetLocation().x * 20) + 10, (ThePlayer->GetLocation().y * 20) + 10);
		//SDL_RenderDrawLine(Renderer, inSightB.x, inSightB.y, botTwo.getPosition().x, botTwo.getPosition().y);
	}
	if (MoveDirectionVector)
	{
		SDL_RenderDrawLine(Renderer, (BotOne->GetLocation().x * 20) + 10, (BotOne->GetLocation().y * 20) + 10,
											 (BotOne->GetMoveAwayDirection().x * 20) + 10 , (BotOne->GetMoveAwayDirection().y * 20) + 10);
		SDL_RenderDrawLine(Renderer, (BotTwo->GetLocation().x * 20) + 10, (BotTwo->GetLocation().y * 20) + 10,
											(BotTwo->GetMoveAwayDirection().x * 20) + 10, (BotTwo->GetMoveAwayDirection().y * 20) + 10);
	}
	for (int x = 0; x < 30 * 20; x += 20)
	{
		SDL_RenderDrawLine(Renderer, 0, x, 600, x);
		SDL_RenderDrawLine(Renderer, x, 0, x, 600);
	}

	SDL_RenderPresent(Renderer);
}
