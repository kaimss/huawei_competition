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

void dispatch(adjacencyWDigraph&, car&);//��ʱ�ĵ�Ⱥ���

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

	int index = 88;
	//����index�ų������·������·�����к͵�·����
	outputPath(a, b, cars.getCar(index).from, cars.getCar(index).to, cars.getCar(index).path, cars.getCar(index).dot, graph);
	//���Ե��һ���
	dispatch(graph, cars.getCar(index));
  
	for (int i = 0; i < 10240; i++)
		graph.outputPathFile(a,b,cars.getCar(i).id,cars.getCar(i).planTime,cars.getCar(i).from,cars.getCar(i).to);
	
	 system("Pause");
	return 0;
}
