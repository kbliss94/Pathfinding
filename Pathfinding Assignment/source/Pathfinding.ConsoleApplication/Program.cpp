#include "pch.h"

using namespace Library;
using namespace std;

int main(int argc, char* argv[])
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	GridHelper gridHelper;
	Graph grid;
	StopWatch stopwatch;

	grid = gridHelper.LoadGridFromFile("Grid.grid");
	//grid = gridHelper.LoadGridFromFile("NoPathGrid.grid");

	grid.Draw();

	std::set<std::shared_ptr<Node>> visitedNodes;
	std::deque<std::shared_ptr<Node>> pathFound;
	std::vector<std::pair<string, std::shared_ptr<IPathFinder>>> algorithms = 
	{
		std::pair<string, std::shared_ptr<BreadthFirst>>("breadth-first", make_shared<BreadthFirst>()),
		std::pair<string, std::shared_ptr<GreedyBestFirst>>("greedy best-first", make_shared<GreedyBestFirst>()),
		std::pair<string, std::shared_ptr<Dijkstra>>("Dijkstra's", make_shared<Dijkstra>()),
		std::pair<string, std::shared_ptr<AStar>>("A*", make_shared<AStar>())
	};

	int startX, startY, endX, endY;

	cout << endl << "Enter start coordinates (x y): ";
	cin >> startX >> startY;
	cout << "Enter end coordinates (x y): ";
	cin >> endX >> endY;
	cout << endl;

	for (int i = 0; i < (int)(algorithms.size()); ++i)
	{
		//using the algorithm
		stopwatch.Start();
		pathFound = algorithms[i].second->FindPath(grid.At(startX, startY), grid.At(endX, endY), visitedNodes);
		stopwatch.Stop();

		cout << endl << "Path found using " << algorithms[i].first << " algorithm: " << endl;

		//drawing grid path found
		grid.DrawPath(pathFound);

		cout << endl << "The algorithm took " << stopwatch.ElapsedMilliseconds().count() << " milliseconds and ";
		cout << visitedNodes.size() << " nodes were visited." << endl;
		cout << "The path found was " << pathFound.size() << " nodes long." << endl << endl;

		stopwatch.Reset();
		pathFound.clear();
		visitedNodes.clear();
	}

	return 0;
}