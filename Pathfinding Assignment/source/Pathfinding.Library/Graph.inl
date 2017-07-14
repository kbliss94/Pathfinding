#include "Graph.h"

using namespace std;

namespace Library
{
	inline const std::map<Point, std::shared_ptr<Node>>& Library::Graph::Nodes() const
	{
		return mNodes;
	}

	inline std::shared_ptr<Node> Graph::At(const Point& location) const
	{
		return mNodes.at(location);
	}

	inline std::shared_ptr<Node> Graph::At(const int x, const int y) const
	{
		return At(Point(x, y));
	}

	inline bool Graph::Contains(const Point& location) const
	{
		return mNodes.find(location) != mNodes.end();
	}

	inline bool Graph::Contains(const int x, const int y) const
	{
		return Contains(Point(x, y));
	}

	inline void Graph::Draw()
	{
		cout << " - : traversable space" << endl;
		cout << " | : wall/obstacle" << endl << endl;

		int gridWidth = (int)(pow(mNodes.size(), 0.5));

		for (int j = 0; j < gridWidth; ++j)
		{
			cout << "  ";

			for (int i = 0; i < gridWidth; ++i)
			{
				if (mNodes[Point(i, j)]->Type() == NodeType::Normal)
				{
					cout << "- ";
				}
				else
				{
					cout << "| ";
				}
			}

			cout << endl;
		}
	}

	inline void Graph::DrawPath(std::deque<std::shared_ptr<Node>>& path)
	{
		if (path.size() > 1)
		{
			mNodes[path.front()->Location()]->SetAsStart();
			mNodes[path.back()->Location()]->SetAsEnd();

			for (int i = 1; i < (int)(path.size() - 1); ++i)
			{
				mNodes[path[i]->Location()]->SetAsPath();
			}

			cout << endl << " S : start node" << endl;
			cout << " E : end node" << endl;
			cout << " X : path" << endl << endl;

			int gridWidth = (int)(pow(mNodes.size(), 0.5));

			for (int j = 0; j < gridWidth; ++j)
			{
				cout << "  ";

				for (int i = 0; i < gridWidth; ++i)
				{
					Node currentNode = *mNodes[Point(i, j)];

					if (currentNode.Type() == NodeType::Normal)
					{
						cout << "- ";
					}
					else if (currentNode.Type() == NodeType::Path)
					{
						cout << "X ";
					}
					else if (currentNode.Type() == NodeType::Wall)
					{
						cout << "| ";
					}
					else if (currentNode.Type() == NodeType::Start)
					{
						cout << "S ";
					}
					else
					{
						cout << "E ";
					}
				}

				cout << endl;
			}

			for (int i = 0; i < (int)(path.size()); ++i)
			{
				mNodes[path[i]->Location()]->SetAsNormal();
			}
		}
		else
		{
			cout << endl << "No path found." << endl;
		}
	}
}