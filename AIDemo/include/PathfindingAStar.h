// Author : Lewis Ward
// Date: 29/08/2017
#pragma once
#include "Window.h"
#include <vector>
#include "Texture.h"
#include "AABB.h"

struct AStarNode
{
	AStarNode* Parent;
	Vec2 Coordinate;
	int G = 0, H = 0;

	AStarNode(Vec2 Coord)
	{
		Coordinate = Coord;
		Parent = nullptr;
	};

	AStarNode(Vec2 Coord, AStarNode* Successor)
	{
		Parent = Successor;
		Coordinate = Coord;
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

	inline void SetWorldSize(float X, float Y) { WorldSize.X = X; WorldSize.Y = Y; }
	inline Vec2 GetWorldSize() { return WorldSize; }
	inline void ClearCollisions() { Walls.clear(); }
	inline std::vector<Vec2> GetCollisions() { return Walls; }
	inline void AddCollision(Vec2 Corrdinates) { Walls.push_back(Corrdinates); }

	void RemoveCollision(Vec2 Coordinates);

	AStarNode* FindNodeOnList(std::vector<AStarNode*>& Nodes, Vec2 Coordinates);

	void ReleaseNodes(std::vector<AStarNode*>& Nodes);

	bool DetectCollision(Vec2 Coordinates);

	std::vector<Vec2> FindPath(Vec2 Start, Vec2 Target);

private:
	std::vector<Vec2> Directions, Walls;
	Vec2 WorldSize;
	int DirectionsCount = 4;
};
