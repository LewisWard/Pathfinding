// Author : Lewis Ward
// Date: 29/08/2017
#include "PathfindingAStar.h"

AStar::AStar()
{

}

AStar::~AStar()
{

}

std::vector<int> AStar::compute()
{
	// size of the world (grids)
	const int width = 10;
	const int height = 10;

	int startingGridIndex = 0;
	int currentGridIndex = 0;

	// reset vector
	m_gridIndex.clear();

	startingGridIndex = getIndex(m_startPosition);
	currentGridIndex = startingGridIndex;

	// create a path to end point
	// compute the grid index for grids around clicked grod
	//	0	1	2		| 0 == X - (width - 1) | 1 == X - width | 2 == (X - width) + 1
	//	3	X	4		| 3 == X - 1           | current grid   | 4 == X + 1
	//	5	6	7		| 5 == X + (width - 1) | 6 == X + width | 7 == (X + width) + 1
	float shortestDistance = FLT_MAX;
	float lowestCost = FLT_MAX;
	int shortestIndex = currentGridIndex;
	int T0, T1, T2, M0, M2, B0, B1, B2;
	int gridCount = 0;
	

	vec2 atFinalGrid;

	// compute path as long as there is still some distance to travel and it capped to vector size
	while (shortestDistance >= 0.0f && gridCount < 100.0f && m_finishGridIndex != currentGridIndex)
	{
		m_targetInFinish = false;
		gridCount++;

		// 4-way movement
		int gridsNextTo[] = {
			T1 = currentGridIndex - width,
			M0 = currentGridIndex - 1,
			M2 = currentGridIndex + 1,
			B1 = currentGridIndex + width,
		};
		float movementWaySize = 4;

		for (int i = 0; i < movementWaySize; ++i)
		{
			if (gridsNextTo[i] < 0 || gridsNextTo[i] > 99)
			{
				gridsNextTo[i] = currentGridIndex;
			}
		}


		// cycle all grids to find the shortest distance
		for (int i = 0; i < movementWaySize; ++i)
		{
			// make sure the grid is walkable
			if (m_grids[gridsNextTo[i]].walkable == true)
			{
				// compute distance from final grid (centre of the grid)
				vec2 distance;
				distance.x = m_endPosition.x - (m_grids[gridsNextTo[i]].gridBounds.m_min.x);
				distance.y = m_endPosition.y - (m_grids[gridsNextTo[i]].gridBounds.m_min.y);

				// the distance between the current and end grids
				float vectorDistance = length(distance);
				float movementCost = m_grids[gridsNextTo[i]].cost;

				// if its the shortset distance to the end grid, store it
				if (vectorDistance < shortestDistance && movementCost <= lowestCost && m_grids[gridsNextTo[i]].visited == false)
				{
					shortestDistance = vectorDistance;
					shortestIndex = gridsNextTo[i];
					currentGridIndex = shortestIndex;
					lowestCost = movementCost;
				}
			}
		}
		m_gridIndex.push_back(shortestIndex);

		// stop pushing back the same index to fill vector to 100 in size.
		// make sure we have at least two elements
		if (m_gridIndex.size() > 1)
		{
			// if the last two were the same, stop the search
			if (m_gridIndex[m_gridIndex.size() - 1] == m_gridIndex[m_gridIndex.size() - 2])
			{
				// remove the copy index
				m_gridIndex.pop_back();

				// replace the copy with the final index
				m_gridIndex.push_back(m_finishGridIndex);

				break;
			}
		}
	}

	m_gridIndex.push_back(m_finishGridIndex);
	m_grids[startingGridIndex].visited = true;
	return m_gridIndex;
}

void AStar::end(vec2 e)
{
	// size of the world (grids)
	const int width = 10;
	const int height = 10;

	for (int i = 0; i < m_grids.size(); ++i)
		m_grids[i].visited = false;

	// find the grid we are in
	for (size_t y = 0; y < width; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			size_t index = y * width + x;

			// test to see what grid we are in
			if (e.x >= (x * 50.0f) && e.y >= (y * 50.0f) &&
				e.x <= (x * 50.0f) + 50.0f && e.y <= (y * 50.0f + 50.0f))
			{
				m_endPosition.x = (x * 50.0f) + 25.0f;
				m_endPosition.y = (y * 50.0f) + 25.0f;

				m_finishGridIndex = (int)index;

				// break from for loop
				y = width;
				x = width;
			}
		}
	}
}
