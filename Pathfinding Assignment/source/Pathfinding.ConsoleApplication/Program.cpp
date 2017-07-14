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

	//use grid helper to create a graph from a filename
	//pass the node list to the path finder
	//path finder returns the node path
	//visualize the path (or not if one doesn't exist)

	GridHelper gridHelper;
	Graph grid;
	StopWatch stopwatch;

	grid = gridHelper.LoadGridFromFile("Grid.grid");
	//grid = gridHelper.LoadGridFromFile("NoPathGrid.grid");

	grid.Draw();

	BreadthFirst breadthFirst;
	GreedyBestFirst greedyBestFirst;
	Dijkstra dijkstra;

	std::set<std::shared_ptr<Node>> visitedNodes;
	std::deque<std::shared_ptr<Node>> pathFound;
	std::vector<std::pair<string, std::shared_ptr<IPathFinder>>> algorithms;

	int startX, startY, endX, endY;

	cout << endl << "Enter start coordinates (x y): ";
	cin >> startX >> startY;
	cout << "Enter end coordinates (x y): ";
	cin >> endX >> endY;
	cout << endl;

	algorithms.push_back(std::pair<string, std::shared_ptr<BreadthFirst>>("breadth-first", make_shared<BreadthFirst>(breadthFirst)));
	algorithms.push_back(std::pair<string, std::shared_ptr<GreedyBestFirst>>("greedy best-first", make_shared<GreedyBestFirst>(greedyBestFirst)));
	algorithms.push_back(std::pair<string, std::shared_ptr<Dijkstra>>("Dijkstra's", make_shared<Dijkstra>(dijkstra)));

	for (int i = 0; i < (int)(algorithms.size()); ++i)
	{
		//using the algorithm
		stopwatch.Start();
		pathFound = algorithms[i].second->FindPath(grid.At(startX, startY), grid.At(endX, endY), visitedNodes);
		stopwatch.Stop();

		cout << endl << "Path found using " << algorithms[i].first << " algorithm: " << endl;

		//draw grid path found
		grid.DrawPath(pathFound);

		cout << endl << "The algorithm took " << stopwatch.ElapsedMilliseconds().count() << " milliseconds and ";
		cout << visitedNodes.size() << " nodes were visited." << endl;
		cout << "The path found was " << pathFound.size() << " nodes long." << endl << endl;

		stopwatch.Reset();
		pathFound.clear();
		visitedNodes.clear();
	}



	////using breadth-first algorithm
	//stopwatch.Start();
	//pathFound = breadthFirst.FindPath(grid.At(startX, startY), grid.At(endX, endY), visitedNodes);
	//stopwatch.Stop();

	//cout << endl << "Path found using breadth-first algorithm: " << endl;

	////draw grid path found for breadth first algorithm
	//grid.DrawPath(pathFound);

	//cout << endl << "The algorithm took " << stopwatch.ElapsedMilliseconds().count() << " milliseconds and ";
	//cout << visitedNodes.size() << " nodes were visited." << endl << endl;

	////use greedy best-first algorithm
	//stopwatch.Reset();
	//pathFound.clear();
	//visitedNodes.clear();

	//stopwatch.Start();
	//pathFound = greedyBestFirst.FindPath(grid.At(startX, startY), grid.At(endX, endY), visitedNodes);
	//stopwatch.Stop();

	//cout << endl << "Path found using greedy best-first algorithm: " << endl;

	////draw grid path found for greedy best-first algorithm
	//grid.DrawPath(pathFound);

	//cout << endl << "The algorithm took " << stopwatch.ElapsedMilliseconds().count() << " milliseconds and ";
	//cout << visitedNodes.size() << " nodes were visited." << endl << endl;

	////using dijkstra's algorithm
	//stopwatch.Reset();
	//pathFound.clear();
	//visitedNodes.clear();

	//stopwatch.Start();
	//pathFound = dijkstra.FindPath(grid.At(startX, startY), grid.At(endX, endY), visitedNodes);
	//stopwatch.Stop();

	//cout << endl << "Path found using Dijkstra's algorithm : " << endl;

	////draw grid path found for dijkstra's algorithm
	//grid.DrawPath(pathFound);

	//cout << endl << "The algorithm took " << stopwatch.ElapsedMilliseconds().count() << " milliseconds and ";
	//cout << visitedNodes.size() << " nodes were visited." << endl << endl;

	return 0;
}