#pragma once

#include "IPathFinder.h"

//!Implementing the Breadth-First pathfinding algorithm.

namespace Library
{
	class BreadthFirst final : public IPathFinder
	{
	public:
		//!Default constructor
		BreadthFirst() {};

		//!Copy constructor
		BreadthFirst(const BreadthFirst& rhs) = delete;

		//!Assignment operator
		BreadthFirst& operator=(const BreadthFirst& rhs) = delete;

		//!Destructor
		~BreadthFirst() {};

		//!Finds path to given end node when starting at the given start node using the breadth-first pathfinding algorithm
		/*!
		Returns path between nodes if one exists. If one doesn't exist, the deque returned will only contain the start node.
		*/
		std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet) override;

	private:
		std::deque<std::shared_ptr<Node>> mFrontier;
	};
}
