// Author : Lewis Ward
// Date: 29/08/2017
#include "PathfindingAStar.h"

AStar::AStar()
{
	Directions.reserve(4);
	Directions = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };
}

void AStar::RemoveCollision(Vec2 Coordinates)
{
	std::vector<Vec2>::iterator it = std::find(Walls.begin(), Walls.end(), Coordinates);
	if (it != Walls.end())
	{
		Walls.erase(it);
	}
}

AStarNode* AStar::FindNodeOnList(std::vector<AStarNode*>& Nodes, Vec2 Coordinates)
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

bool AStar::DetectCollision(Vec2 Coordinates)
{
	if (Coordinates.X < 0 || Coordinates.X >= WorldSize.X || Coordinates.Y < 0 || Coordinates.Y >= WorldSize.Y
		|| std::find(Walls.begin(), Walls.end(), Coordinates) != Walls.end())
		return true;

	return false;
}

std::vector<Vec2> AStar::FindPath(Vec2 Start, Vec2 Target)
{
	Start.X = (int)Start.X;
	Start.Y = (int)Start.Y;
	Target.X = (int)Target.X;
	Target.Y = (int)Target.Y;

	std::vector<Vec2> Path;

	// Quick exit if invalid target location, returns a path of the starting location
	if (DetectCollision(Target))
	{
		Path.push_back(Start); 
		return Path;
	}

	AStarNode* Current = nullptr;
	std::vector<AStarNode*> CloseSet, OpenSet;
	OpenSet.push_back(new AStarNode(Start));

	// Keep going over the open list until it is empty, create a linked list of nodes that will be the path to return
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
			Vec2 NewCoord(Current->Coordinate + Directions[i]);

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
				Succesor->H = fabs(Succesor->Coordinate.X + Target.X) + fabs(Succesor->Coordinate.Y + Target.Y);
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