// Author : Lewis Ward
// Date: 29/08/2017
#include "Demo.h"

Demo::Demo()
{
	DemoWindow = new Window();
	Renderer = SDL_CreateRenderer(DemoWindow->window(), -1, 0);
	NewWorld = new TheNewWorld(30, 30);
	Pathfinder = new AStarFast();
	ThePlayer = new Player();
	IOEvents = new Events();
	BotOne = new NPC(vec2(8, 8));
	BotTwo = new NPC(vec2(1, 1));

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
	Pathfinder->AddCollision(vec2(6, 11));
	Pathfinder->AddCollision(vec2(7, 12));
	Pathfinder->AddCollision(vec2(7, 13));
	Pathfinder->AddCollision(vec2(6, 12));
	Pathfinder->AddCollision(vec2(5, 10));
	Pathfinder->AddCollision(vec2(5, 9));
	Pathfinder->AddCollision(vec2(4, 10));
	Pathfinder->AddCollision(vec2(3, 10));
	Pathfinder->AddCollision(vec2(13, 13));
	Pathfinder->AddCollision(vec2(14, 14));

	Mouse = vec2(5, 5) * 20;
	ThePlayer->Position(vec2(5, 5));
	ThePlayer->createTexture(Renderer);
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

void Demo::MoveTo(float& dt, Player& player, std::vector<vec2>& path)
{
	vec2 Node = path.back();

	player.update(dt, Node);

	if (withinRange(player.getPosition(), Node))
	{
		player.Position(Node);
		path.pop_back();
	}
}


void Demo::Update(float dt)
{
	switch (IOEvents->eventQueue())
	{
		case 100: GameLoop = false; break;
		case 1: LineOfSight = (LineOfSight == true) ? false : true; break; // turn on or off
		case 2: DrawPaths = (DrawPaths == true) ? false : true; break; // turn on or off
		case 3: DrawGrids = (DrawGrids == true) ? false : true; break; // turn on or off
		case 4: MoveDirectionVector = (MoveDirectionVector == true) ? false : true; break; // turn on or off
	}

	if (0 == IOEvents->mouseQueue())
	{
		Mouse = IOEvents->getMouseLocation();
		Path = Pathfinder->FindPath(ThePlayer->getPosition(), Mouse / 20);
	}

	if (ThePlayer->AtPathEnd)
	{
		ThePlayer->AtPathEnd = false;

		Path = Pathfinder->FindPath(ThePlayer->getPosition(), Mouse / 20);
	}

	if (Path.size() > 0)
	{
		MoveTo(dt, *ThePlayer, Path);
	}
	else
	{
		ThePlayer->AtPathEnd = true;
	}

	ProcessLoS();
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

	ThePlayer->draw(Renderer);
	BotOne->draw(Renderer);
	BotTwo->draw(Renderer);

	// draw certain visuals if they are turned on or not
	if (LineOfSight)
	{
		SDL_RenderDrawLine(Renderer, (InSight.x * 20) + 10, (InSight.y * 20) + 10, 
											(ThePlayer->getPosition().x * 20) + 10, (ThePlayer->getPosition().y * 20) + 10);
		//SDL_RenderDrawLine(Renderer, inSightOfB.x, inSightOfB.y, player.getPosition().x, player.getPosition().y);
		//SDL_RenderDrawLine(Renderer, inSightB.x, inSightB.y, botTwo.getPosition().x, botTwo.getPosition().y);
	}
	if (MoveDirectionVector)
	{
		//SDL_RenderDrawLine(Renderer, moveAwayA.x, moveAwayA.y, botOne.getPosition().x, botOne.getPosition().y);
		//SDL_RenderDrawLine(Renderer, moveAwayB.x, moveAwayB.y, botTwo.getPosition().x, botTwo.getPosition().y);
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

	// generate direction vectors between origin and target (i.e botOne to Player)
	vec2 direction(BotOne->getPosition().x - ThePlayer->getPosition().x, BotOne->getPosition().y - ThePlayer->getPosition().y);
	InSight = RaySight.cast(ThePlayer->getPosition(), direction, length(BotOne->getPosition() - ThePlayer->getPosition()));
	std::vector<vec2> points;
	
	// get all the grids that intersect the line of sight
	//points = RaySight.bresenhamLine(ThePlayer->getPosition(), BotOne->getPosition());
	//
	//for (int x = 0; x < points.size(); x++)
	//{
	//	for (int y = 0; y < Pathfinder->GetCollisions().size(); y++)
	//	{
	//		if (Pathfinder->DetectCollision(points[x]))
	//		{
	//			InSight = points[x];
	//		}
	//	}
	//}

	// player LoS to botTwo
	//vec2 directionToB(BotTwo->getPosition().x - ThePlayer->getPosition().x, BotTwo->getPosition().y - ThePlayer->getPosition().y);
	//vec2 inSightOfB = RaySight.cast(ThePlayer->getPosition(), directionToB, length(BotTwo->getPosition() - ThePlayer->getPosition()));
	//std::vector<vec2> pointsToB;
	//
	//// get all the grids that intersect the line of sight
	//pointsToB = RaySight.bresenhamLine(ThePlayer->getPosition(), BotTwo->getPosition());
	//for (int i = 0; i < pointsToB.size(); i++)
	//{
	//	for (int ii = 0; ii < WALL_COUNT; ii++)
	//	{
	//		// if line enters a wall grid then limit LoS to the distance
	//		if (getIndex(pointsToB[i]) == walls[ii].getIndex())
	//		{
	//			inSightOfB = pointsToB[i];
	//			break;
	//		}
	//
	//		if (pointsToB.size() == 1)
	//		{
	//			inSightOfB = pointsToB[i];
	//			break;
	//		}
	//	}
	//}
	//
	//// is within line of sight and needs a new path
	//int tempGridIndex = getIndex(inSight);
	//vec2 moveAwayA;
	//if (tempGridIndex == getIndex(BotOne->getPosition()))
	//{
	//	vec2 tempA(BotOne->getPosition().x, BotOne->getPosition().y);
	//	vec2 tempB(ThePlayer->getPosition().x, ThePlayer->getPosition().y);
	//	moveAwayA = RaySight.cast(ThePlayer->getPosition(), direction, length(tempA - tempB) + 50.0f);
	//
	//	// make sure bot doesn't get stuck within a corner
	//	switch (getIndex(BotOne->getPosition()))
	//	{
	//	case 0:
	//		moveAwayA.x += 50.0f;
	//		moveAwayA.y += 50.0f;
	//		break;
	//	case 9:
	//		moveAwayA.x -= 50.0f;
	//		moveAwayA.y += 50.0f;
	//		break;
	//	case 90:
	//		moveAwayA.x += 50.0f;
	//		moveAwayA.y -= 50.0f;
	//		break;
	//	case 99:
	//		moveAwayA.x -= 50.0f;
	//		moveAwayA.y -= 50.0f;
	//		break;
	//	default: break; ///< not in the corner
	//	}
	//}
	
	//// LoS between botOne and botTwo
	//vec2 directionB(BotOne->getPosition().x - BotTwo->getPosition().x, BotOne->getPosition().y - BotTwo->getPosition().y);
	//vec2 inSightB = RaySight.cast(BotTwo->getPosition(), directionB, length(BotOne->getPosition() - BotTwo->getPosition()));
	//std::vector<vec2> pointsB;
	//
	//// get all the grids that intersect the line of sight
	//pointsB = RaySight.bresenhamLine(BotTwo->getPosition(), BotOne->getPosition());
	//for (int i = 0; i < pointsB.size(); i++)
	//{
	//	for (int ii = 0; ii < WALL_COUNT; ii++)
	//	{
	//		// if line enters a wall grid then limit LoS to the distance
	//		if (getIndex(pointsB[i]) == walls[ii].getIndex())
	//		{
	//			inSightB = pointsB[i];
	//			break;
	//		}
	//
	//		if (pointsB.size() == 1)
	//		{
	//			inSightB = pointsB[i];
	//			break;
	//		}
	//	}
	//}
	//
	//// move towards botA (this will be overwritten in switch below if in LoS of the player!)
	//tempGridIndex = getIndex(inSightB);
	//if (tempGridIndex == getIndex(BotOne->getPosition()))
	//{
	//	// prevents BotB entering the same grid as BotA or overlapping BotB
	//	vec2 tempA(BotOne->getPosition().x, BotOne->getPosition().y);
	//	vec2 tempB(BotTwo->getPosition().x, BotTwo->getPosition().y);
	//	vec2 moveTowardsA = RaySight.cast(BotTwo->getPosition(), directionB, length(tempA - tempB) - 50.0f);
	//}
	//
	//
	//tempGridIndex = getIndex(inSightOfB);
	//vec2 moveAwayB;
	//if (tempGridIndex == getIndex(BotTwo->getPosition()))
	//{
	//	vec2 tempA(botTwo.getPosition().x, botTwo.getPosition().y);
	//	vec2 tempB(player.getPosition().x, player.getPosition().y);
	//	moveAwayB = raySight.cast(player.getPosition(), directionToB, length(tempA - tempB) + 50.0f);
	//	
	//	// make sure bot doesn't get stuck within a corner
	//	switch (getIndex(botTwo.getPosition()))
	//	{
	//	case 0: 
	//		moveAwayB.x += 50.0f;
	//		moveAwayB.y += 50.0f;
	//		botBPathfinding.end(moveAwayB);
	//		break;
	//	case 9: 
	//		moveAwayB.x -= 50.0f;
	//		moveAwayB.y += 50.0f;
	//		botBPathfinding.end(moveAwayB);
	//		break;
	//	case 90: 
	//		moveAwayB.x += 50.0f;
	//		moveAwayB.y -= 50.0f;
	//		botBPathfinding.end(moveAwayB);
	//		break;
	//	case 99:
	//		moveAwayB.x -= 50.0f;
	//		moveAwayB.y -= 50.0f;
	//		botBPathfinding.end(moveAwayB);
	//		break;
	//	default: botBPathfinding.end(moveAwayB); break; ///< not in the corner
	//	}
	//}
	
	// run pathfinding for bots
	//botPathfinding.start(botOne.getPosition());
	//path = botPathfinding.compute();
}
