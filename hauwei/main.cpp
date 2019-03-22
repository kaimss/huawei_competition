#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include "adjacencyWDigraph.h"

using namespace std;

int main()
{

	adjacencyWDigraph graph(64);
	graph.iniRoad("data1//road_process.txt");

	int **a, **b;
	a = new int*[65];
	b = new int*[65];
	for (int i = 0; i <= 64; i++)
		{
			a[i] = new int[65];
			b[i] = new int[65];
		}
	graph.allpairs(a,b);
	outputPath(a, b, 57, 8);
	cout << a[57][8];
  
	return 0;
}