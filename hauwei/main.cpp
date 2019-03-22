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

#define maxsecond 200//最大调度时间

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

	//计算0号车的最短路径所经过的路口序列和道路序列
	outputPath(a, b, cars.getCar(0).from, cars.getCar(0).to, cars.getCar(0).path, cars.getCar(0).dot, graph);

	


	dispatch(graph, cars.getCar(0));




	cout << "hello\n";



	return 0;
}

int min(int &a, int &b)
{
	return a > b ? b : a;
}


void dispatch(adjacencyWDigraph &graph, car &acar)
{
	int second;

	for (second = 0; second <= maxsecond; second++)
	{
		//出发前的判定（是否延缓发车，及选择车道）
		if (second == acar.planTime)
		{//到达出发时间

			cout << "第" << second << "秒车辆开始出发\n";

			acar.second = 0;//每辆车的计时器
			acar.cchannel = 1;//车道选择1
			acar.cfrom = acar.dot[acar.i];//目前从cfrom路口行驶到cto路口
			acar.cto = acar.dot[acar.i + 1];
			acar.direction = acar.cto - acar.cfrom;//目前行驶方向
			acar.turn = 1;//目前是直行状态
			acar.cdistance = 0;//目前行驶距离为0

			//行驶道路时的判定（行驶车道前方是否有车，是否限速）
			edge &droad = graph.getEdge(acar.cfrom, acar.cto);
			//acar.cspeed = droad.maxSpeed > acar.maxSpeed ? acar.maxSpeed : droad.maxSpeed;
			acar.cspeed = min(droad.maxSpeed, acar.maxSpeed);
			droad.road[acar.cchannel][acar.cdistance] = acar.id;
		}
		else if (second > acar.planTime)
		{//行驶中
			acar.second++;
			edge &droad = graph.getEdge(acar.cfrom, acar.cto);
			if (acar.cdistance + acar.cspeed >= droad.length)
			{//下一秒会到达路口
				if (acar.cto == acar.to)
				{//到达终点

					//一些操作
					cout << "第" << second << "秒车辆到达终点\n";

					
					
					return;
				}
				else
				{//路口调度
					int S1 = droad.length - acar.cdistance;
					edge &ndroad = graph.getEdge(acar.cto, acar.dot[acar.i+2]);
					int S2 = min(acar.maxSpeed, ndroad.maxSpeed);
					if (S2 <= S1)
					{//无法通过路口
						cout << "第" << second << "秒车辆到达路口"<<acar.dot[acar.i+1]<<"且未通过\n";

						droad.road[acar.cchannel][acar.cdistance] = 0;//清除上一个位置
						acar.cdistance = droad.length;//更新当前行驶距离
						droad.road[acar.cchannel][acar.cdistance] = acar.id;//更新当前位置
					}
					else
					{//可以通过路口

						cout << "第" << second << "秒车辆穿过路口" << acar.dot[acar.i + 2] << "且到达道路" << droad.id << "\n";

						//更新车辆信息与道路信息
						acar.i++;//更新路径计数器
						acar.cfrom = acar.dot[acar.i];//目前从cfrom路口行驶到cto路口
						acar.cto = acar.dot[acar.i + 1];
						acar.direction = acar.cto - acar.cfrom;//目前行驶方向

						droad.road[acar.cchannel][acar.cdistance] = 0;//清除在上一条道路的信息
						acar.cdistance = S2 - S1;//目前行驶距离为S2-S1
						acar.cspeed = min(ndroad.maxSpeed, acar.maxSpeed);//更新最大速度
						ndroad.road[acar.cchannel][acar.cdistance] = acar.id;//更新在下一条道路的位置
					}
				}
				

			}
			else
			{//下一秒未到达路口
				cout << "第" << second << "秒车辆在道路" << droad.id << "上行驶\n";
				//一些操作
				droad.road[acar.cchannel][acar.cdistance] = 0;//清除上一个位置
				acar.cdistance += acar.cspeed;//更新当前行驶距离
				droad.road[acar.cchannel][acar.cdistance] = acar.id;//更新当前位置

			}
		    //行驶道路时的判定（行驶车道前方是否有车，是否限速）

		}
		else
		{//未到达出发时间

		}
		


		




		//到达路口时的判定（方向与转向，行驶优先级，是否可过路口，下一路口的车道选择）

		//到达目的地的判定
		cout << acar << "\n";
	}
}