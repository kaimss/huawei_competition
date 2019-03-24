#pragma once
#ifndef _TESTDISPATCH_
#define _TESTDISPATCH_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <string>
#include "adjacencyWDigraph.h"
#include "carArray.h"
using namespace std;

#define maxsecond 200//最大调度时间
int min(int &a, int &b)
{
	return a > b ? b : a;
}

//计算转向
int qualifyturn(int a, int b)
{
	int x = b - a;
	if (x == 0)
	{//直行
		return 1;
	}
	else if (x == 7)
	{
		if (a == 1)
		{//右转
			return 3;
		}
		else if (a == -8)
		{//左转
			return 2;
		}
	}
	else if (x == -7)
	{
		if (a == 8)
			return 2;
		else if (a == -1)
			return 3;
	}
	else if (x == 9)
	{
		if (a == -8)
			return 3;
		else if (a == -1)
			return 2;
	}
	else if (x == -9)
	{
		if (a == 1)
			return 2;
		else if (a == 8)
			return 3;
	}


}
//将数字转向转为汉字转向
string itd(int turn)
{
	if (turn == 1)
		return "直行";
	else if (turn == 2)
		return "左转";
	else if (turn == 3)
		return "右转";

}

//调度器
void dispatch(adjacencyWDigraph &graph, car &acar)
{
	int second;

	for (second = 0; second <= maxsecond; second++)
	{
		
		if (second == acar.planTime)
		{//到达出发时间

			//cout << "第" << second << "秒车辆开始出发\n";

			acar.second = 0;//每辆车的计时器
			acar.cchannel = 1;//车道选择1
			acar.cfrom = acar.dot[acar.i];//目前从cfrom路口行驶到cto路口
			acar.cto = acar.dot[acar.i + 1];
			acar.direction = acar.cto - acar.cfrom;//目前行驶方向
			acar.turn = 1;//目前是直行状态
			acar.cdistance = 0;//目前行驶距离为0
			

			
			edge &droad = graph.getEdge(acar.cfrom, acar.cto);//获取当前将要行驶的道路
			acar.croad = droad.id;//目前行驶道路编号
			acar.cspeed = min(droad.maxSpeed, acar.maxSpeed);//获得当前速度
			droad.road[acar.cchannel][acar.cdistance] = acar.id;//将此车标记在道路上
		}
		else if (second > acar.planTime)
		{//行驶中
			acar.second++;
			edge &droad = graph.getEdge(acar.cfrom, acar.cto);
			if (acar.cdistance + acar.cspeed >= droad.length)
			{//下一秒会到达路口
				if (acar.cto == acar.to)
				{//到达终点
					acar.cdistance = droad.length;
					//cout << "第" << second << "秒车辆到达终点\n";
					//cout << acar;
					return;
				}
				else
				{//路口调度
					int S1 = droad.length - acar.cdistance;
					edge &ndroad = graph.getEdge(acar.cto, acar.dot[acar.i + 2]);
					int S2 = min(acar.maxSpeed, ndroad.maxSpeed);
				
					if (S2 <= S1)
					{//无法通过路口
						//cout << "第" << second << "秒车辆到达路口" << acar.dot[acar.i + 1] << "且未通过\n";

						droad.road[acar.cchannel][acar.cdistance] = 0;//清除上一个位置
						acar.cdistance = droad.length;//更新当前行驶距离
						droad.road[acar.cchannel][acar.cdistance] = acar.id;//更新当前位置
					}
					else
					{//可以通过路口




					   //更新车辆信息与道路信息
						acar.i++;//更新路径计数器
						acar.cfrom = acar.dot[acar.i];//更新行驶路口序列，目前从cfrom路口行驶到cto路口
						acar.cto = acar.dot[acar.i + 1];
						acar.turn = qualifyturn(acar.direction, acar.cto - acar.cfrom);//确定转向
						acar.direction = acar.cto - acar.cfrom;//更新行驶方向
						acar.croad = ndroad.id;//更新行驶道路编号

						//cout << "第" << second << "秒车辆" << itd(acar.turn) << "穿过路口" << acar.dot[acar.i] << "且到达道路" << ndroad.id << "\n";

						droad.road[acar.cchannel][acar.cdistance] = 0;//清除在上一条道路的信息
						acar.cdistance = S2 - S1;//目前行驶距离为S2-S1
						acar.cspeed = min(ndroad.maxSpeed, acar.maxSpeed);//更新最大速度
						ndroad.road[acar.cchannel][acar.cdistance] = acar.id;//更新在下一条道路的位置
					}
				}


			}
			else
			{//下一秒未到达路口
				//cout << "第" << second << "秒车辆在道路" << droad.id << "上行驶\n";
				droad.road[acar.cchannel][acar.cdistance] = 0;//清除上一个位置
				acar.cdistance += acar.cspeed;//更新当前行驶距离
				droad.road[acar.cchannel][acar.cdistance] = acar.id;//更新当前位置

			}

			
			//cout << acar << "\n";

		}
		else
		{//未到达出发时间

		}




		//出发前的判定（是否延缓发车，及选择车道）

		//行驶道路时的判定（行驶车道前方是否有车，是否限速）

		//到达路口时的判定（方向与转向，行驶优先级，是否可过路口，下一路口的车道选择）

		//到达目的地的判定
		
	}
}
#endif
