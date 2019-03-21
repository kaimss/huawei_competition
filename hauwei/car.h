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

	int cspeed;//当前速度
	int direction;//当前行驶方向
	int turn;//在路口的转向
	int croad;//当前行驶道路
	int cchannel;//当前行驶车道
	int cfcross;//当前出发路口
	int ctcross;//当前目的路口
	
	car() :id(0), from(0), to(0), maxSpeed(0),planTime(1) {}

	car(int id, int from, int to, int maxSpeed,int planTime) :
		id(id), from(from),to(to),maxSpeed(maxSpeed),planTime(planTime) {}


};





#endif