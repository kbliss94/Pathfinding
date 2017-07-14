#pragma once

#include "IPathFinder.h"

/*
Implementing Dijkstra's pathfinding algorithm.
*/

namespace Library
{
	class Dijkstra final : public IPathFinder
	{
	public:
		//!Default constructor
		Dijkstra() {};

		Dijkstra(const Dijkstra& rhs) = delete;

		Dijkstra& operator=(const Dijkstra& rhs) = delete;

		//!Destructor
		~Dijkstra() {};

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