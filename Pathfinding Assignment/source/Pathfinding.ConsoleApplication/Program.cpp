#include "pch.h"

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

	return 0;
}