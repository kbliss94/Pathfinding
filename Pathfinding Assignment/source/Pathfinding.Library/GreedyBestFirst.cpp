#include "pch.h"
#include "GreedyBestFirst.h"

namespace Library
{
	GreedyBestFirst::GreedyBestFirst(const GreedyBestFirst& rhs)
	{
		*this = rhs;
	}

	GreedyBestFirst& GreedyBestFirst::operator=(const GreedyBestFirst& rhs)
	{
		mFrontier = rhs.mFrontier;

		return *this;
	}

	std::deque<std::shared_ptr<Node>> GreedyBestFirst::FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::set<std::shared_ptr<Node>>& closedSet)
	{
		std::deque<std::shared_ptr<Node>> path;
		std::shared_ptr<Node> currentNode;
		std::shared_ptr<Node> currentNeighbor;

		//calculate heuristic for each of start's neighbors & add them to mFrontier
		for (int i = 0; i < (int)(start->Neighbors().size()); ++i)
		{
			currentNeighbor = start->Neighbors()[i].lock();

			//setting the parent of currentNode's neighbors to currentNode
			currentNeighbor->SetParent(currentNode);

			currentNeighbor->SetHeuristic(CalculateHeuristic(currentNeighbor->Location(), end->Location()));
			mFrontier.push_back(currentNeighbor);
		}

		closedSet.insert(start);

		//enter loop
		while (!mFrontier.empty())
		{
			//sort frontier (lowest heuristic to highest)
			std::sort(mFrontier.begin(), mFrontier.end(), [](std::shared_ptr<Library::Node> a, std::shared_ptr<Library::Node> b)
			{
				return a->Heuristic() < b->Heuristic();
			});

			//set current node to front of frontier
			currentNode = mFrontier.front();

			//pop front of frontier
			mFrontier.pop_front();

			if (*currentNode != *end)
			{
				for (int i = 0; i < (int)(currentNode->Neighbors().size()); ++i)
				{
					currentNeighbor = currentNode->Neighbors()[i].lock();

					//check to make sure its neighbors aren't in the frontier or the closedSet
					if ((std::find(mFrontier.begin(), mFrontier.end(), currentNeighbor) == mFrontier.end()) &&
						(std::find(closedSet.begin(), closedSet.end(), currentNeighbor) == closedSet.end()))
					{
						//setting the parent of currentNode's neighbors to currentNode
						currentNeighbor->SetParent(currentNode);

						//calculate heuristic for neighbor
						currentNeighbor->SetHeuristic(CalculateHeuristic(currentNeighbor->Location(), end->Location()));

						//add it to the frontier
						mFrontier.push_back(currentNeighbor);
					}
				}

				//add current node to the closedSet
				closedSet.insert(currentNode);
			}
			else
			{
				//early outing if end node is found
				closedSet.insert(currentNode);
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