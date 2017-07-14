#include "pch.h"
#include "AStar.h"

namespace Library
{
	std::deque<std::shared_ptr<Node>> AStar::FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet)
	{
		std::deque<std::shared_ptr<Node>> path;

		start;
		end;
		closedSet;

		return path;
	}

	float AStar::CalculateHeuristic(Point node, Point end)
	{
		return (float)(abs(end.X() - node.X()) + abs(end.Y() - node.Y()));
	}
}