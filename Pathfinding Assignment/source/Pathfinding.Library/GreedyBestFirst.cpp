#include "pch.h"
#include "GreedyBestFirst.h"

namespace Library
{
	std::deque<std::shared_ptr<Node>> GreedyBestFirst::FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet)
	{
		std::deque<std::shared_ptr<Node>> path;
		std::shared_ptr<Node> currentNode;
		std::shared_ptr<Node> currentNeighbor;

		//calculate heuristic for each of start's neighbors & add them to mFrontier
		for (int i = 0; i < (int)(start->Neighbors().size()); ++i)
		{
			currentNeighbor = start->Neighbors()[i].lock();

			currentNeighbor->SetParent(currentNode);
			currentNeighbor->SetHeuristic(CalculateHeuristic(currentNeighbor->Location(), end->Location()));
			mFrontier.push_back(currentNeighbor);
		}

		closedSet.insert(start);

		while (!mFrontier.empty())
		{
			//sort frontier (lowest heuristic value to highest)
			std::sort(mFrontier.begin(), mFrontier.end(), [](std::shared_ptr<Library::Node> a, std::shared_ptr<Library::Node> b)
			{
				return a->Heuristic() < b->Heuristic();
			});

			currentNode = mFrontier.front();
			mFrontier.pop_front();
			closedSet.insert(currentNode);

			if (*currentNode != *end)
			{
				for (int i = 0; i < (int)(currentNode->Neighbors().size()); ++i)
				{
					currentNeighbor = currentNode->Neighbors()[i].lock();

					//checking to make sure the current neighbor isn't in mFrontier or closedSet
					if ((std::find(mFrontier.begin(), mFrontier.end(), currentNeighbor) == mFrontier.end()) &&
						(std::find(closedSet.begin(), closedSet.end(), currentNeighbor) == closedSet.end()))
					{
						currentNeighbor->SetParent(currentNode);
						currentNeighbor->SetHeuristic(CalculateHeuristic(currentNeighbor->Location(), end->Location()));
						mFrontier.push_back(currentNeighbor);
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

		path.push_front(start);

		return path;
	}

	float GreedyBestFirst::CalculateHeuristic(Point node, Point end)
	{
		return (float)(abs(end.X() - node.X()) + abs(end.Y() - node.Y()));
	}
}