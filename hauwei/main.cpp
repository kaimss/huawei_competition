#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <string>
#include "adjacencyWDigraph.h"
#include "carArray.h"
#include "testdispatch.h"
using namespace std;



void dispatch(adjacencyWDigraph&, car&);//暂时的调度函数

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


	int index = 88;
	//计算index号车的最短路径所经过的路口序列和道路序列
	outputPath(a, b, cars.getCar(index).from, cars.getCar(index).to, cars.getCar(index).path, cars.getCar(index).dot, graph);

	

	//尝试调度一辆车
	dispatch(graph, cars.getCar(index));






	return 0;
}
