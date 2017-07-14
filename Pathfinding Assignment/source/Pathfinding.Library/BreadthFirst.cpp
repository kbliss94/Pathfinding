#include "pch.h"
#include "BreadthFirst.h"

namespace Library
{
	BreadthFirst::BreadthFirst(const BreadthFirst& rhs)
	{
		*this = rhs;
	}

	BreadthFirst& BreadthFirst::operator=(const BreadthFirst& rhs)
	{
		mFrontier = rhs.mFrontier;

		return *this;
	}

	std::deque<std::shared_ptr<Node>> BreadthFirst::FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet)
	{
		std::deque<std::shared_ptr<Node>> path;
		std::shared_ptr<Node> currentNode;

		mFrontier.push_front(start);

		while (!mFrontier.empty())
		{
			currentNode = mFrontier.front();

			//remove current node from the front of mFrontier
			mFrontier.pop_front();
			closedSet.insert(currentNode);

			if (*currentNode != *end)
			{
				for (int i = 0; i < (int)(currentNode->Neighbors().size()); ++i)
				{
					std::shared_ptr<Node> currentNeighbor = currentNode->Neighbors()[i].lock();

					//checking if currentNode's neighbors are in mFrontier && closedSet
					if ((std::find(mFrontier.begin(), mFrontier.end(), currentNeighbor) == mFrontier.end()) &&
						(std::find(closedSet.begin(), closedSet.end(), currentNeighbor) == closedSet.end()))
					{
						//setting the parent of currentNode's neighbors to currentNode
						currentNeighbor->SetParent(currentNode);

						//adding currentNode's neighbors to mFrontier
						mFrontier.push_back(currentNeighbor);
					}
				}

				//adding currentNode to closedSet
				//closedSet.insert(currentNode);
			}
			else
			{
				//early outing if end node is found
				//closedSet.insert(currentNode);
				break;
			}
		}

		//now check end's parent?
		std::shared_ptr<Node> currentParent;
		currentParent = end->Parent().lock();

		if (currentParent != nullptr)
		{
			//a path was found
			path.push_front(end);

			//constructing the path
			while (currentParent != nullptr)
			{
				path.push_front(currentParent);
				currentParent = currentParent->Parent().lock();
			}
		}
		else
		{
			//a path was not found

			//only add the start node to the path
			path.push_front(start);
		}


		return path;
	}
}