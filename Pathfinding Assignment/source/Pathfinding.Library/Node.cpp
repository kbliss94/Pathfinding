#include "pch.h"
#include "Node.h"

namespace Library
{
	Node::Node(const Point& location, NodeType type) :
		mLocation(location), mType(type), mHeuristic(0.0f), mPathCost(0.0f), mTotalCost(0.0f)
	{
		CoCreateGuid(&mID);
	}

	Node::Node(const Node& rhs)
	{
		*this = rhs;
	}

	Node& Node::operator=(const Node& rhs)
	{
		mID = rhs.mID;
		mType = rhs.mType;
		mLocation = rhs.mLocation;
		mHeuristic = rhs.mHeuristic;
		mPathCost = rhs.mPathCost;
		mTotalCost = rhs.mTotalCost;
		mNeighbors = rhs.mNeighbors;
		mParent = rhs.mParent;

		return *this;
	}
}