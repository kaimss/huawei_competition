#pragma once
#ifndef _CAR_
#define _CAR_

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


	int direction;//当前行驶方向
	int turn;//在路口的转向

	
	car() :id(0), from(0), to(0), maxSpeed(0), planTime(0),second(0) {}

	car(int id, int from, int to, int maxSpeed,int planTime, int second) :
		id(id), from(from), to(to), maxSpeed(maxSpeed), planTime(planTime), second(second) {}




};





#endif