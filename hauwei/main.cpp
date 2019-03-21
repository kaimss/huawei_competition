#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdio.h>
#include <vector>
#include "adjacencyWDigraph.h"
#include "carArray.h"
using namespace std;

#define maxsecond 20000//最大调度时间

void dispatch(adjacencyWDigraph, car);//暂时的调度函数

int main()
{
	adjacencyWDigraph graph(64);
	graph.iniRoad("data1//road_process.txt");
	//graph.iniRoad2("data2//road.txt");
	//graph.output();

	carArray cars;
	cars.iniCar("data1//car_process.txt");
	//cars.iniCar2("data2//car.txt");
	

	int **a, **b;
	a = new int*[65];
	b = new int*[65];
	for (int i = 0; i <= 64; i++)
	{
		a[i] = new int[65];
		b[i] = new int[65];
	}
	graph.allpairs(a,b);
	//outputPath(a, b, 1, 36);
	//cout << a[1][36];

	//计算0号车的路径
	outputPath(a, b, cars.getCar(0).from, cars.getCar(0).to, cars.getCar(0).path, graph);

	










	return 0;
}
void dispatch(adjacencyWDigraph graph, car acar)
{
	acar.second = 0;
	int second = 0;

	acar.from;

	for (; second <= maxsecond; second++)
	{

	}
}