#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "adjacencyWDigraph.h"

using namespace std;

int main()
{
	adjacencyWDigraph graph(64);
	graph.iniRoad("data1//road_process.txt");
	return 0;
}