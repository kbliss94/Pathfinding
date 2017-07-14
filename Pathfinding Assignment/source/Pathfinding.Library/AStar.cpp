#include "pch.h"
#include "AStar.h"

namespace Library
{
	std::deque<std::shared_ptr<Node>> AStar::FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet)
	{
		std::deque<std::shared_ptr<Node>> path;
		std::shared_ptr<Node> currentNode;
		std::shared_ptr<Node> currentNeighbor;

		start->SetPathCost(0);
		mFrontier.push_front(start);

		while (!mFrontier.empty())
		{
			//sort frontier (lowest total cost to highest)
			std::sort(mFrontier.begin(), mFrontier.end(), [](std::shared_ptr<Library::Node> a, std::shared_ptr<Library::Node> b)
			{
				return a->TotalCost() < b->TotalCost();
			});

			currentNode = mFrontier.front();
			mFrontier.pop_front();
			closedSet.insert(currentNode);

			if (*currentNode != *end)
			{
				float currentPathCost = currentNode->PathCost() + 1;

				for (int i = 0; i < (int)(currentNode->Neighbors().size()); ++i)
				{
					currentNeighbor = currentNode->Neighbors()[i].lock();

					//if the neighbor isn't in the closed set (aka if it hasn't been visited yet)
					if (std::find(closedSet.begin(), closedSet.end(), currentNeighbor) == closedSet.end())
					{
						//if the neighbor isn't in frontier
						if (std::find(mFrontier.begin(), mFrontier.end(), currentNeighbor) == mFrontier.end())
						{
							currentNeighbor->SetParent(currentNode);
							currentNeighbor->SetPathCost(currentPathCost);
							currentNeighbor->SetHeuristic(CalculateHeuristic(currentNeighbor->Location(), end->Location()));
							mFrontier.push_front(currentNeighbor);
						}
						//if the neighbor is in the frontier, update its path cost if its bigger than the current path cost
						else
						{
							if (currentPathCost < currentNeighbor->PathCost())
							{
								currentNeighbor->SetParent(currentNode);
								currentNeighbor->SetPathCost(currentPathCost);
							}
						}
					}
				}
			}
			else
			{
				break;
			}
		}

		//constructing the path
		std::shared_ptr<Node> currentParent;
		currentParent = end->Parent().lock();

		if (currentParent != nullptr)
		{
			path.push_front(end);

			while (currentParent != nullptr)
			{
				path.push_front(currentParent);
				currentParent = currentParent->Parent().lock();
			}
		}
		else
		{
			path.push_front(start);
		}

		return path;
	}

	float AStar::CalculateHeuristic(Point node, Point end)
	{
		return (float)(abs(end.X() - node.X()) + abs(end.Y() - node.Y()));
	}
}