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
	ThePlayer = new Player();
	IOEvents = new Events();
	BotOne = new NPC(vec2(8, 8));
	BotTwo = new NPC(vec2(5, 16));

	BotTwo->loadNewTexture("images/botB.bmp");
	FloorTexture = new Texture("images/point.bmp");
	WallTexture = new Texture("images/wall.bmp");

	BotOne->createTexture(Renderer);
	BotTwo->createTexture(Renderer);
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

	Mouse = vec2(5, 5) * 20;
	ThePlayer->SetPosition(vec2(5, 5));
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

void Demo::MoveTo(float& dt, Player& APlayer, std::vector<vec2>& Path)
{
	vec2 Node = Path.back();

	APlayer.Update(dt, Node);

	if (withinRange(APlayer.GetPosition(), Node))
	{
		APlayer.SetPosition(Node);
		Path.pop_back();
	}
}

void Demo::MoveTo(float& dt, NPC& ANPC, std::vector<vec2>& Path)
{
	vec2 Node = Path.back();

	ANPC.update(dt, Node);

	if (withinRange(ANPC.getPosition(), Node))
	{
		ANPC.Position(Node);
		Path.pop_back();
	}
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
		Path = Pathfinder->FindPath(ThePlayer->GetPosition(), Mouse / 20);
	}

	// Find a path if the user is at the end of a path
	if (ThePlayer->IsAtPathEnd())
	{
		ThePlayer->SetAtPathEnd(false);
		Path = Pathfinder->FindPath(ThePlayer->GetPosition(), Mouse / 20);
	}

	// Move the player
	if (Path.size() > 0)
	{
		MoveTo(dt, *ThePlayer, Path);
	}
	else
	{
		ThePlayer->SetAtPathEnd(true);
	}

	ProcessLoS();

	// If the Bot is in LoS of the Player and is not moving, create a path to move away
	if (BotOne->IsPlayerInSight() && !BotOne->getIsMoving())
	{
		// Turn into a useable position for the pathfinder
		vec2 ValidLocation((int)MoveAwayA.x, (int)MoveAwayA.y);

		PathB1 = Pathfinder->FindPath(BotOne->getPosition(), ValidLocation);
		PathB1.pop_back(); // This will be the current position the AI is in
	}

	// Move away from the player
	if (PathB1.size() > 0)
	{
		MoveTo(dt, *BotOne, PathB1);
	}
	else
	{
		BotOne->isMoving(false);
	}


	// If the Bot is in LoS of the Player and is not moving, create a path to move away
	if (BotTwo->IsPlayerInSight() && !BotTwo->getIsMoving())
	{
		// Turn into a useable position for the pathfinder
		vec2 ValidLocation((int)MoveAwayB.x, (int)MoveAwayB.y);

		PathB2 = Pathfinder->FindPath(BotTwo->getPosition(), ValidLocation);
		PathB2.pop_back(); // This will be the current position the AI is in
	}

	// Move away from the player
	if (PathB2.size() > 0)
	{
		MoveTo(dt, *BotTwo, PathB2);
	}
	else
	{
		BotTwo->isMoving(false);
	}
}

void Demo::Draw()
{
	SDL_SetRenderDrawColor(Renderer, 0.0f, 0.0f, 0.0f, 0.0f);
	SDL_RenderClear(Renderer);

	NewWorld->draw(Renderer);

	for (int i = 0; i < Path.size(); ++i)
	{
		SDL_Rect destRect;
		destRect.w = 20.f;
		destRect.h = 20.f;
		destRect.x = Path[i].x * 20.f;
		destRect.y = Path[i].y * 20.f;
		SDL_RenderCopy(Renderer, FloorTexture->texture(), NULL, &destRect);
	}

	for (int i = 0; i < PathB1.size(); ++i)
	{
		SDL_Rect destRect;
		destRect.w = 20.f;
		destRect.h = 20.f;
		destRect.x = PathB1[i].x * 20.f;
		destRect.y = PathB1[i].y * 20.f;
		SDL_RenderCopy(Renderer, FloorTexture->texture(), NULL, &destRect);
	}

	for (int i = 0; i < PathB2.size(); ++i)
	{
		SDL_Rect destRect;
		destRect.w = 20.f;
		destRect.h = 20.f;
		destRect.x = PathB2[i].x * 20.f;
		destRect.y = PathB2[i].y * 20.f;
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
	BotOne->draw(Renderer);
	BotTwo->draw(Renderer);

	// draw certain visuals if they are turned on or not
	if (LineOfSight)
	{
		SDL_RenderDrawLine(Renderer, (PlayerInSightA.x * 20) + 10, (PlayerInSightA.y * 20) + 10,
											(ThePlayer->GetPosition().x * 20) + 10, (ThePlayer->GetPosition().y * 20) + 10);
		SDL_RenderDrawLine(Renderer, (PlayerInSightB.x * 20) + 10, (PlayerInSightB.y * 20) + 10,
											(ThePlayer->GetPosition().x * 20) + 10, (ThePlayer->GetPosition().y * 20) + 10);
		//SDL_RenderDrawLine(Renderer, inSightB.x, inSightB.y, botTwo.getPosition().x, botTwo.getPosition().y);
	}
	if (MoveDirectionVector)
	{
		SDL_RenderDrawLine(Renderer, (BotOne->getPosition().x * 20) + 10, (BotOne->getPosition().y * 20) + 10, 
											 (MoveAwayA.x * 20) + 10 , (MoveAwayA.y * 20) + 10);
		SDL_RenderDrawLine(Renderer, (BotTwo->getPosition().x * 20) + 10, (BotTwo->getPosition().y * 20) + 10,
											(MoveAwayB.x * 20) + 10, (MoveAwayB.y * 20) + 10);
	}
	for (int x = 0; x < 30 * 20; x += 20)
	{
		SDL_RenderDrawLine(Renderer, 0, x, 600, x);
		SDL_RenderDrawLine(Renderer, x, 0, x, 600);
	}

	SDL_RenderPresent(Renderer);
}

void Demo::ProcessLoS()
{
	rayCast RaySight;

	// Generate direction vectors between origin and target (i.e BotOne to Player)
	vec2 DirectionToA(BotOne->getPosition().x - ThePlayer->GetPosition().x, BotOne->getPosition().y - ThePlayer->GetPosition().y);
	PlayerInSightA = RaySight.cast(ThePlayer->GetPosition(), DirectionToA, length(BotOne->getPosition() - ThePlayer->GetPosition()));
	std::vector<vec2> PointsToA;
	
	// get all the grids that intersect the line of sight
	PointsToA = RaySight.bresenhamLine(ThePlayer->GetPosition(), BotOne->getPosition());
	bool HitTarget = true;

	for (int x = 0; x < PointsToA.size(); x++)
	{
		for (int y = 0; y < Pathfinder->GetCollisions().size(); y++)
		{
			if (Pathfinder->DetectCollision(PointsToA[x]))
			{
				PlayerInSightA = PointsToA[x];
				HitTarget = false;
				break;
			}
		}
	}

	// Is within line of sight and needs a new path to move away
	if (HitTarget)
	{
		vec2 tempA(BotOne->getPosition().x, BotOne->getPosition().y);
		vec2 tempB(ThePlayer->GetPosition().x, ThePlayer->GetPosition().y);
		MoveAwayA = RaySight.cast(ThePlayer->GetPosition(), DirectionToA, length(tempB - tempA) + 3.0f);
		BotOne->SetPlayerInSight(true);
	}
	else
	{
		BotOne->SetPlayerInSight(false);
	}

	// Player LoS to bBotTwo
	vec2 DirectionToB(BotTwo->getPosition().x - ThePlayer->GetPosition().x, BotTwo->getPosition().y - ThePlayer->GetPosition().y);
	PlayerInSightB = RaySight.cast(ThePlayer->GetPosition(), DirectionToB, length(BotTwo->getPosition() - ThePlayer->GetPosition()));
	std::vector<vec2> PointsToB;
	
	// Get all the grids that intersect the line of sight
	PointsToB = RaySight.bresenhamLine(ThePlayer->GetPosition(), BotTwo->getPosition());
	HitTarget = true;

	for (int x = 0; x < PointsToB.size(); x++)
	{
		for (int y = 0; y < Pathfinder->GetCollisions().size(); y++)
		{
			if (Pathfinder->DetectCollision(PointsToB[x]))
			{
				PlayerInSightB = PointsToB[x];
				HitTarget = false;
				break;
			}
		}
	}

	// Is within line of sight and needs a new path to move away
	if (HitTarget)
	{
		vec2 tempA(BotTwo->getPosition().x, BotTwo->getPosition().y);
		vec2 tempB(ThePlayer->GetPosition().x, ThePlayer->GetPosition().y);
		MoveAwayB = RaySight.cast(ThePlayer->GetPosition(), DirectionToB, length(tempB - tempA) + 3.0f);
		BotTwo->SetPlayerInSight(true);
	}
	else
	{
		BotTwo->SetPlayerInSight(false);
	}
}
