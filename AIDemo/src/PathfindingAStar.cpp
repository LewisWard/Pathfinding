// Author : Lewis Ward
// Date: 29/08/2017
#include "PathfindingAStar.h"

AStar::AStar()
{
	Directions.reserve(4);
	Directions = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };
}

void AStar::RemoveCollision(vec2 Coordinates)
{
	std::vector<vec2>::iterator it = std::find(Walls.begin(), Walls.end(), Coordinates);
	if (it != Walls.end())
	{
		Walls.erase(it);
	}
}

AStarNode* AStar::FindNodeOnList(std::vector<AStarNode*>& Nodes, vec2 Coordinates)
{
	for (AStarNode* Node : Nodes)
	{
		if (Node->Coordinate == Coordinates)
			return Node;
	}

	return nullptr;
}

void AStar::ReleaseNodes(std::vector<AStarNode*>& Nodes)
{
	for (std::vector<AStarNode*>::iterator it = Nodes.begin(); it != Nodes.end();)
	{
		delete *it;
		it = Nodes.erase(it);
	}
}

bool AStar::DetectCollision(vec2 Coordinates)
{
	if (Coordinates.x < 0 || Coordinates.x >= WorldSize.x || Coordinates.y < 0 || Coordinates.y >= WorldSize.y
		|| std::find(Walls.begin(), Walls.end(), Coordinates) != Walls.end())
		return true;

	return false;
}

std::vector<vec2> AStar::FindPath(vec2 Start, vec2 Target)
{
	Start.x = (int)Start.x;
	Start.y = (int)Start.y;
	Target.x = (int)Target.x;
	Target.y = (int)Target.y;

	std::vector<vec2> Path;
	if (DetectCollision(Target))
	{
		Path.push_back(Start);
		std::cout << "Dectection: " << Target.x << " " << Target.y << std::endl;
		return Path;
	}

	AStarNode* Current = nullptr;
	std::vector<AStarNode*> CloseSet, OpenSet;
	OpenSet.push_back(new AStarNode(Start));

	while (!OpenSet.empty())
	{
		Current = *OpenSet.begin();

		// Find smallest F score
		for (AStarNode* Node : OpenSet)
		{
			if (Node->GetScore() <= Current->GetScore())
				Current = Node;
		}

		// Found the target?
		if (Current->Coordinate == Target)
		{
			break;
		}

		CloseSet.push_back(Current);
		OpenSet.erase(std::find(OpenSet.begin(), OpenSet.end(), Current));

		// For each of the nodes around this node, if valid/not on the closed list compute it's total cost
		for (int i = 0; i < DirectionsCount; i++)
		{
			vec2 NewCoord(Current->Coordinate + Directions[i]);

			if (DetectCollision(NewCoord) || FindNodeOnList(CloseSet, NewCoord))
			{
				continue;
			}

			int TotalNodeCost = Current->G + 10;

			// If not in the open list, add it. Otherwise, each if the total cost for it is less increase it to the actual value
			AStarNode* Succesor = FindNodeOnList(OpenSet, NewCoord);
			if (!Succesor)
			{
				Succesor = new AStarNode(NewCoord, Current);
				Succesor->G = TotalNodeCost;
				Succesor->H = fabs(Succesor->Coordinate.x + Target.x) + fabs(Succesor->Coordinate.y + Target.y);
				OpenSet.push_back(Succesor);
			}
			else if (Succesor && TotalNodeCost < Succesor->G)
			{
				Succesor->Parent = Current;
				Succesor->G = TotalNodeCost;
			}
		}
	}

	// Return the path and clean up
	while (Current)
	{
		Path.push_back(Current->Coordinate);
		Current = Current->Parent;
	}

	ReleaseNodes(OpenSet);
	ReleaseNodes(CloseSet);
	return Path;
}


std::vector<vec2> AStar::FindPathAI(vec2 Start, vec2 Target)
{
	Start.x = (int)Start.x;
	Start.y = (int)Start.y;
	Target.x = (int)Target.x;
	Target.y = (int)Target.y;

	std::vector<vec2> Path;
	if (DetectCollision(Target))
	{
		Path.push_back(Start); 
		std::cout << "Dectection: " << Target.x << " " << Target.y << std::endl;
		return Path;
	}

	AStarNode* Current = nullptr;
	std::vector<AStarNode*> CloseSet, OpenSet;
	OpenSet.push_back(new AStarNode(Start));

	while (!OpenSet.empty())
	{
		Current = *OpenSet.begin();

		// Find smallest F score
		for (AStarNode* Node : OpenSet)
		{
			if (Node->GetScore() <= Current->GetScore())
				Current = Node;
		}

		// Found the target?
		if (Current->Coordinate == Target)
		{
			break;
		}

		CloseSet.push_back(Current);
		OpenSet.erase(std::find(OpenSet.begin(), OpenSet.end(), Current));

		// For each of the nodes around this node, if valid/not on the closed list compute it's total cost
		for (int i = 0; i < DirectionsCount; i++)
		{
			vec2 NewCoord(Current->Coordinate + Directions[i]);

			if (DetectCollision(NewCoord) || FindNodeOnList(CloseSet, NewCoord))
			{
				continue;
			}

			int TotalNodeCost = Current->G + 10;

			// If not in the open list, add it. Otherwise, each if the total cost for it is less increase it to the actual value
			AStarNode* Succesor = FindNodeOnList(OpenSet, NewCoord);
			if (!Succesor)
			{
				Succesor = new AStarNode(NewCoord, Current);
				Succesor->G = TotalNodeCost;
				Succesor->H = fabs(Succesor->Coordinate.x + Target.x) + fabs(Succesor->Coordinate.y + Target.y);
				OpenSet.push_back(Succesor);
			}
			else if (Succesor && TotalNodeCost < Succesor->G)
			{
				Succesor->Parent = Current;
				Succesor->G = TotalNodeCost;
			}
		}
	}

	// Return the path and clean up
	while (Current)
	{
		Path.push_back(Current->Coordinate);
		Current = Current->Parent;
	}

	ReleaseNodes(OpenSet);
	ReleaseNodes(CloseSet);
	return Path;
}