#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "adjacencyWDigraph.h"

using namespace std;

int main()
{
	adjacencyWDigraph graph(64);
	graph.iniRoad("C:\\huawei\\data1\\road_process.txt");
	/*
	car.open("C:\\huawei\\data1\\car_process.txt", ios::in | ios::out|ios::binary);
	
	if (!car.is_open()) {
		cout << "文件打开错误" << endl;
		exit(0);
	}
	char buffer[256];
	int i = 0;
	while (!car.eof())
	{
		car.getline(buffer, 100);
		cout << buffer << endl;
	}
	car.close();
	*/
	return 0;
}