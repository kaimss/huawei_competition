#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdio.h>
#include "adjacencyWDigraph.h"
#include "car.h"

using namespace std;



int main()
{
	adjacencyWDigraph graph(64);
	//graph.iniRoad("data1//road_process.txt");
	graph.iniRoad2("data2//road.txt");
  
	//graph.output();

	int **a, **b;
	a = new int*[65];
	b = new int*[65];
	for (int i = 0; i <= 64; i++)
	{
		a[i] = new int[65];
		b[i] = new int[65];
	}
	graph.allpairs(a,b);
	outputPath(a, b, 1, 36);
	cout << a[1][36];










	return 0;
}