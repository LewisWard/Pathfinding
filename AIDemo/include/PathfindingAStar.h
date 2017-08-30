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


class AStarFast
{
	std::vector<vec2> Directions, Walls;
	vec2 WorldSize;
	int DirectionsCount = 4;

public:
	
	AStarFast()
	{
		Directions.reserve(4);
		Directions = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };
	}

	inline void SetWorldSize(int X, int Y) { WorldSize.x = X; WorldSize.y = Y; }
	inline void ClearCollisions() { Walls.clear(); }
	inline std::vector<vec2> GetCollisions() { return Walls; }
	inline void AddCollision(vec2 Corrdinates) 	{	Walls.push_back(Corrdinates); }

	void RemoveCollision(vec2 Coordinates)
	{
		std::vector<vec2>::iterator it = std::find(Walls.begin(), Walls.end(), Coordinates);
		if (it != Walls.end())
		{
			Walls.erase(it);
		}
	}

	AStarNode* FindNodeOnList(std::vector<AStarNode*>& Nodes, vec2 Coordinates)
	{
		for (AStarNode* Node : Nodes)
		{
			if (Node->Coordinate == Coordinates)
				return Node;
		}

		return nullptr;
	}

	void ReleaseNodes(std::vector<AStarNode*>& Nodes)
	{
		for (std::vector<AStarNode*>::iterator it = Nodes.begin(); it != Nodes.end();)
		{
			delete *it;
			it = Nodes.erase(it);
		}
	}

	bool DetectCollision(vec2 Coordinates)
	{
		if (Coordinates.x < 0 || Coordinates.x >= WorldSize.x || Coordinates.y < 0 || Coordinates.y >= WorldSize.y 
			  || std::find(Walls.begin(), Walls.end(), Coordinates) != Walls.end())
			return true;

		return false;
	}

	std::vector<vec2> FindPath(vec2 Start, vec2 Target)
	{
		Start.x = (int)Start.x;
		Start.y = (int)Start.y;
		Target.x = (int)Target.x;
		Target.y = (int)Target.y;


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

				if(DetectCollision(NewCoord) || FindNodeOnList(CloseSet, NewCoord))
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
		std::vector<vec2> Path;
		while (Current)
		{
			Path.push_back(Current->Coordinate);
			Current = Current->Parent;
		}

		ReleaseNodes(OpenSet);
		ReleaseNodes(CloseSet);
		return Path;
	}
};


//----------------------------------------------------------------------------------------------------------------------
/// \brief  A* pathfinding 
//----------------------------------------------------------------------------------------------------------------------
class AStar
{
public:
	/// \brief Constr
	AStar();
	/// \brief Destr
	~AStar();

	/// \brief compute a path from current position to destination
	/// \return std::vector<int> path (grids) index values 
	std::vector<int> compute();

	/// \brief get the last computed path
	/// \return std::vector<int> path (grids) index values 
	inline std::vector<int> path()
	{ return m_gridIndex; }

	/// \brief set the start position
	/// \prama vec2 position
	inline void start(vec2 s)
	{ m_startPosition = s; }

	/// \brief set the end position
	/// \prama vec2 end
	void end(vec2 e);

	/// \brief set the grid data
	/// \prama std::vector<Grid> grids
	inline void grids(std::vector<Grid>& g)
	{ m_grids = g;}

	/// \brief get the end position
	/// \return vec2 end
	inline vec2 getEnd()
	{ return m_endPosition; }

	/// \brief whats the character got to the end of the path
	/// \return bool
	inline bool targetEndzone()
	{ return m_targetInFinish; }

private:
	vec2 m_startPosition; ///< start A* search from
	vec2 m_endPosition; ///< end A* search
	std::vector<int> m_gridIndex; ///< which grids to use (path)
	std::vector<Grid> m_grids; ///< all the grids in the world
	int m_finishGridIndex; ///< index of final grid 
	bool m_targetInFinish; ///< character got to the end of the path
	float m_movementCost; ///< movement cost of the path (based on per grid)

	/// \brief get movement cost score
	/// \prama float score A
	/// \prama float score B
	/// \return float score
	inline float getMoveScore(float a, float b)
	{ return a + b; }
};
