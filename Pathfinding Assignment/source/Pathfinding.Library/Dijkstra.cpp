#include "pch.h"
#include "Dijkstra.h"

namespace Library
{
	std::deque<std::shared_ptr<Node>> Dijkstra::FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet)
	{
		//uses breadth-first to expand the frontier
		//uses the path cost (its the parent's path cost + 1)
		//if the neighbor is in mFrontier, aka it hasn't been visited yet, then you update the path cost if the current path cost is less than the neighbor's path cost???

		std::deque<std::shared_ptr<Node>> path;
		std::shared_ptr<Node> currentNode;

		start->SetPathCost(0);
		mFrontier.push_front(start);

		while (!mFrontier.empty())
		{
			//sort frontier (lowest heuristic to highest)
			std::sort(mFrontier.begin(), mFrontier.end(), [](std::shared_ptr<Library::Node> a, std::shared_ptr<Library::Node> b)
			{
				return a->PathCost() < b->PathCost();
			});

			currentNode = mFrontier.front();

			//remove current node from the front of mFrontier
			mFrontier.pop_front();
			closedSet.insert(currentNode);

			if (*currentNode != *end)
			{
				float currentPathCost = currentNode->PathCost() + 1;

				//go through each of the neighbors of currentNode
				for (int i = 0; i < (int)(currentNode->Neighbors().size()); ++i)
				{
					std::shared_ptr<Node> currentNeighbor = currentNode->Neighbors()[i].lock();

					//if the neighbor isn't in the closed set (aka if it hasn't been visited yet)
					if (std::find(closedSet.begin(), closedSet.end(), currentNeighbor) == closedSet.end())
					{
						//if the neighbor isn't in frontier
						if (std::find(mFrontier.begin(), mFrontier.end(), currentNeighbor) == mFrontier.end())
						{
							currentNeighbor->SetParent(currentNode);
							currentNeighbor->SetPathCost(currentPathCost);
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
				//early outing if end node is found
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
}