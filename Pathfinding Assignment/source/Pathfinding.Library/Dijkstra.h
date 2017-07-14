#pragma once

#include "AStar.h"

//!Implementing Dijkstra's pathfinding algorithm.

namespace Library
{
	class Dijkstra final : public AStar
	{
	public:
		//!Default constructor
		Dijkstra() {};

		//!Copy constructor
		Dijkstra(const Dijkstra& rhs) = delete;

		//!Assignment operator
		Dijkstra& operator=(const Dijkstra& rhs) = delete;

		//!Destructor
		~Dijkstra() {};

	private:
		float CalculateHeuristic(Point node, Point end) override;

		std::deque<std::shared_ptr<Node>> mFrontier;
	};
}
