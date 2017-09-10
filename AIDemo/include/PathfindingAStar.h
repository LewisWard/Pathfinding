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

	bool DetectCollision(Vec2 Coordinates);

	/// \breif Returns a path between two locations
	/// \prama Vec2 
	/// \prama Vec2 
	/// \return std::vector<vec2> locations in the path
	std::vector<Vec2> FindPath(Vec2 Start, Vec2 Target);

	/// \breif Set the size of the pathfinding world
	/// \prama float width
	/// \prama float height
	void SetWorldSize(float X, float Y);

	inline Vec2 GetWorldSize() { return WorldSize; }

	/// \breif Adds a collision locations (i.e. Walls)
	void AddCollision(Vec2 Corrdinates);

	/// \breif Clears all collision locations (i.e. Walls)
	inline void ClearCollisions() { Walls.clear(); }

	/// \breif Clears a collision locations (i.e. Wall)
	/// \prama Location
	void RemoveCollision(Vec2 Coordinates);

	inline std::vector<Vec2> GetCollisions() { return Walls; }
	
	/// \breif Clears a path of nodes
	/// \prama std::vector<AStarNode*>
	void ReleaseNodes(std::vector<AStarNode*>& Nodes);

	/// \breif Returns a random valid location to move to
	/// \prama Vec2 valid location
	Vec2 RandomValidPosition();

private:
	std::vector<Vec2> Directions, Walls, ValidLocations;
	Vec2 WorldSize;
	int DirectionsCount = 4;

	/// \breif Checks if a collision location is already on a node list
	/// \prama std::vector<AStarNode*> list to check
	/// \prama Vec2 collision location
	/// \return AStarNode* the found node, if none are found returns nullptr
	AStarNode* FindNodeOnList(std::vector<AStarNode*>& Nodes, Vec2 Coordinates);
};
