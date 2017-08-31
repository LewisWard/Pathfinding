// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "World.h"

struct AStarNode
{
	AStarNode* Parent;
	vec2 Coordinate;
	int G = 0, H = 0;

	AStarNode(vec2 coord)
	{
		Coordinate = coord;
		Parent = nullptr;
	};

	AStarNode(vec2 coord, AStarNode* successor)
	{
		Parent = successor;
		Coordinate = coord;
	};

	int GetScore()
	{
		return G + H;
	}
};


class AStar
{
public:
	
	AStar();

	inline void SetWorldSize(int X, int Y) { WorldSize.x = X; WorldSize.y = Y; }
	inline void ClearCollisions() { Walls.clear(); }
	inline std::vector<vec2> GetCollisions() { return Walls; }
	inline void AddCollision(vec2 Corrdinates) 	{	Walls.push_back(Corrdinates); }

	void RemoveCollision(vec2 Coordinates);

	AStarNode* FindNodeOnList(std::vector<AStarNode*>& Nodes, vec2 Coordinates);

	void ReleaseNodes(std::vector<AStarNode*>& Nodes);

	bool DetectCollision(vec2 Coordinates);

	std::vector<vec2> FindPath(vec2 Start, vec2 Target);

	std::vector<vec2> FindPathAI(vec2 Start, vec2 Target);

private:
	std::vector<vec2> Directions, Walls;
	vec2 WorldSize;
	int DirectionsCount = 4;
};
