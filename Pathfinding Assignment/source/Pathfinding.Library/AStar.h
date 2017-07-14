#pragma once

#include "IPathFinder.h"

/*
Implementing the A star pathfinding algorithm.
*/

namespace Library
{
	class AStar : public IPathFinder
	{
	public:
		//!Default constructor
		AStar() {};

		AStar(const AStar& rhs) = delete;

		AStar& operator=(const AStar& rhs) = delete;

		//!Destructor
		~AStar() {};

		//!Finds path to given end node when starting at the given start node using the greedy best-first pathfinding algorithm
		/*!
		Returns path between nodes if one exists. If one doesn't exist, the deque returned will only contain the start node.
		*/
		std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet) override;

	private:
		float CalculateHeuristic(Point node, Point end);

		std::deque<std::shared_ptr<Node>> mFrontier;
	};
}