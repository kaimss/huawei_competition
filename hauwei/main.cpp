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

void dispatch(adjacencyWDigraph&, car&);

int main(int argc, char** argv)
{
	if (argc < 6)
	{
		cout << "usage: ./CodeCraft-2019 ../config/car.txt ";
		cout << "../config/road.txt ../config/cross.txt ";
		cout << "../config/preSetAnswer.txt ../config/answer.txt" << endl;
		exit(0);
	}

	string car_path(argv[1]);		//读入车辆文件路径
	string roads_path(argv[2]);		//读入道路文件路径
	string crosses_path(argv[3]);	//读入路口文件路径
	string preSet_path(argv[4]);	//预置车辆文件路径
	string answer_path(argv[5]);	//生成结果文件路径

	cout << "car file path: " << argv[1] << endl;
	cout << "road file path: " << argv[2] << endl;
	cout << "cross file path: " << argv[3] << endl;
	cout << "preSet car file path: " << argv[4] << endl;
	cout << "result file path: " << argv[5] << endl;

	ofstream clean;//清除上一次answer的数据
	clean.open(argv[5], ios::out);
	clean.close();

	adjacencyWDigraph graph(argv[2], argv[3]);		///这个需要改动，因为未知结点个数

	graph.initPreset(argv[4], argv[5]);
	//graph.iniRoad("data1//road_process.txt");
	//graph.iniCross(argv[3]);
	//graph.iniRoad2(argv[2]);

	//未处理文件读取
	//graph.output();

	carArray cars;
	//cars.iniCar("data1//car_process.txt");
	cars.iniCar2(argv[1]);
	//未处理文件读取
	//vector<pair<int ,int>> carTime(cars.getNumber());	///这个需要改动，因为未知车辆数量
	float **a;
	int **b;
	a = new float*[graph.getNumber() + 1];		///这个需要改
	b = new int*[graph.getNumber() + 1];		///这个需要改
	for (int i = 0; i <= graph.getNumber(); i++)	///这个需要改
	{
		a[i] = new float[graph.getNumber() + 1];		///这个需要改
		b[i] = new int[graph.getNumber() + 1];			///这个需要改
	}

	//graph.allpairs(a,b);
	/*for (int index = 0; index < 10240; index++)
	{
		//int index = 1;
	//计算 index 号车的最短路径所经过的路口序列和道路序列
		outputPath(a, b, cars.getCar(index).from, cars.getCar(index).to, cars.getCar(index).path, cars.getCar(index).dot, graph);
		//尝试调度一辆车
		dispatch(graph, cars.getCar(index));
		carTime[index].first = index + 10000;		///这个需要改
		carTime[index].second = cars.getCar(index).planTime + cars.getCar(index).second;
		//cout << cars.getCar(index).id << " " << cars.getCar(index).planTime << " "<<cars.getCar(index).second << " " << cars.getCar(index).planTime + cars.getCar(index).second<<endl;
	}*/
	//for (int index = 0; index < cars.getNumber(); index++)
	//{
	//	carTime[index].first = cars.getCar(index).id;
	//	carTime[index].second = cars.getCar(index).planTime;
	//}
	binSort(cars);//桶排倒序
	//for (int index = 0; index < 10240; index++)
	//	cout << carTime[index].first << " " << carTime[index].second<<endl;
	//graph.output(argv[4], a, b, cars,count);
	//for (int i = cars.getNumber()-1; i >= 0; i--)
	//	graph.outputPathFile(argv[4], a, b, cars.getCar(i).id, cars.getCar(i).planTime, cars.getCar(i).from, cars.getCar(i).to,count);
	graph.dynamicselect(argv[5],cars);
	return 0;
}
