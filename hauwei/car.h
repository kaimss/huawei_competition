#pragma once
#ifndef _CAR_
#define _CAR_
#include <iostream>
using namespace std;
struct car
{
	int id;//车辆编号
	int from;//始发地
	int to;//目的地
	int maxSpeed;//最大速度
	int planTime;//出发时间

	int second;//调度时间
	vector<int> dot;//规划途径路口
	vector<int> adot;//实际途径路口
	vector<int> path;//规划路径
	vector<int> apath;//实际路径

	int croad;//当前所在道路
	int cspeed;//当前行驶速度，等于min(道路限速，前方车辆的速度限制，自身最大速度)
	int cchannel;//当前行驶车道
	int cfrom;//当前出发路口
	int cto;//当前目的路口
	int cdistance = 0;//在当前道路行驶的距离
	int direction = 1;//当前行驶方向，1为北，8为东，-1为南，-8为西
	int turn;//在路口的转向，1直行，2左转，3右转

	int i = 0;//所经过路口或道路的计数器（路径计数器）
	
	car() :id(0), from(0), to(0), maxSpeed(0), planTime(0),second(0) {}

	car(int id, int from, int to, int maxSpeed,int planTime, int second) :
		id(id), from(from), to(to), maxSpeed(maxSpeed), planTime(planTime), second(second) {}

	friend ostream& operator << (ostream &out, const car &p);//重载输出流，输出内容待定（使用时需要引入头文件及定义命名空间）


};

ostream& operator << (ostream &out, const car &p)
{
	out << "id:"<< p.id << "\tmaxspeed:" << p.maxSpeed << "\nfrom:" << p.from << "\tto:" << p.to ;
	out << "\nplanTime:" << p.planTime << "\n";
	out << "croad:" << p.croad << "\ncchannel:" << p.cchannel << "\tcfrom:" << p.cfrom << "\tcto:" << p.cto;
	out << "\ncspeed:" << p.cspeed << "\tcdistance:" << p.cdistance << "\ndirection:" << p.direction;
	out << "\n";
	return out;
}



#endif