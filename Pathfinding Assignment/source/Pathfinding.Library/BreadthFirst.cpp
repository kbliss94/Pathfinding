#include "pch.h"
#include "BreadthFirst.h"

namespace Library
{
	std::deque<std::shared_ptr<Node>> BreadthFirst::FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet)
	{
		std::deque<std::shared_ptr<Node>> path;
		std::shared_ptr<Node> currentNode;
		std::shared_ptr<Node> currentNeighbor;

		mFrontier.push_front(start);

		while (!mFrontier.empty())
		{
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
						mFrontier.push_back(currentNeighbor);
					}
				}
			}
			else
			{
				break;
			}
		}

		//constructing the path found
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
			//a path was not found, so only adding the start node to the path
			path.push_front(start);
		}

		return path;
	}
}