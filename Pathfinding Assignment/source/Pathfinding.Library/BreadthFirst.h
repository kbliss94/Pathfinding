#pragma once

#include "IPathFinder.h"

namespace Library
{
	class BreadthFirst final : public IPathFinder
	{
	public:
		//!Default constructor
		BreadthFirst() {};

		BreadthFirst(const BreadthFirst& rhs);

		BreadthFirst& operator=(const BreadthFirst& rhs);

		//!Destructor
		~BreadthFirst() {};

		//!Finds path to given end node when starting at the given start node using the breadth-first pathfinding algorithm
		/*!
		Returns path between nodes if one exists. If one doesn't exist, the deque returned will only contain the start node.
		*/

		//////do i need to use override?

		std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet) override;

		//the below is implemented in IPathFinder
		/*std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end);*/

	private:
		//std::deque<std::weak_ptr<Node>> mFrontier;
		std::deque<std::shared_ptr<Node>> mFrontier;

	};
}
