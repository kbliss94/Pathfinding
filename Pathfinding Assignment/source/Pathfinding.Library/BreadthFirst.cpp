#include "pch.h"
#include "BreadthFirst.h"

namespace Library
{
	std::deque<std::shared_ptr<Node>> BreadthFirst::FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet)
	{
		std::deque<std::shared_ptr<Node>> path;

		//path.push_back(start);

		//*parent is set when node is added to the frontier

		//closedSet == visited nodes

		//start at the given start node
		//compare it to end node
			//if equal, stop the process
			//if not equal, set the parent of its neighbors to it, add its neighbors to mFrontier, & add the start node (aka current node) to closedSet
		

		//look at first node in mFrontier
		//compare it to end node
			//if equal, break (add to closedSet first?)
			//if not equal, set the parent of its neighbors to it, add its neighbors to mFrontier (**if they're not already in there || in closedSet**), & add it to closedSet
		//^repeat the above process until either the end node is found or mFrontier is empty

		mFrontier.push_front(start);

		std::shared_ptr<Node> currentNode;

		//begin the loop now
		while (!mFrontier.empty())
		{
			currentNode = mFrontier.front();

			if (*currentNode != *end)
			{
				for (int i = 0; i < currentNode->Neighbors().size(); ++i)
				{
					std::shared_ptr<Node> currentNeighbor = currentNode->Neighbors()[i].lock();

					//checking if currentNode's neighbors are in mFrontier && closedSet
					if ((std::find(mFrontier.begin(), mFrontier.end(), currentNeighbor) != mFrontier.end()) &&
						(std::find(closedSet.begin(), closedSet.end(), currentNeighbor) != closedSet.end()))
					{
						//setting the parent of currentNode's neighbors to currentNode
						currentNeighbor->SetParent(currentNode);

						//adding currentNode's neighbors to mFrontier
						mFrontier.push_front(currentNeighbor);
					}
				}

				//adding currentNode to closedSet
				closedSet.insert(currentNode);
			}
			else
			{
				//early outing if end node is found
				closedSet.insert(currentNode);
				break;
			}
		}

		//now check end's parent?

		if (end->Parent().lock() != nullptr)
		{
			//a path was found

			//constructing the path

		}
		else
		{
			//a path was not found
			//only add the start node to the path
		}


		return path;
	}
}