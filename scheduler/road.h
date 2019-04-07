#pragma once
#ifndef _ROAD_
#define _ROAD_

#include <vector>
#include <iostream>
#include <queue>

using std::vector;
using std::queue;
using std::cin;
using std::cout;
using std::endl;

struct road
{
	road() :id(0), length(0), maxRoadSpeed(0), channels(0) {}
	road(int theID, int theLength, int theMaxSpeed, int theChannels) :
		id(theID), length(theLength), maxRoadSpeed(theMaxSpeed), channels(theChannels) {}
	void disp()
	{
		cout << id << "," << length << "," << maxRoadSpeed << "," << channels << endl;
	}

	void enQueue(const car& theCar);

	int id;				//道路 ID
	int length;			//道路长度
	int maxRoadSpeed;	//最大限速
	int channels;		//车道数量

	vector<vector<int>> roads;//道路数组

	//使用队列添加要上路的车辆
	queue<int> waitingPriority;		//等待上路的优先车辆（按出发时间排序）
	queue<int> waitingGeneral;		//等待上路的非优先车辆（按出发时间排序）
};

void road::enQueue(const car& theCar)
{
	bool isPriority = theCar.isPriority;
	if (isPriority)
		waitingPriority.push(theCar.carID);
	else
		waitingGeneral.push(theCar.carID);
}

#endif