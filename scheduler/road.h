#pragma once
#ifndef _ROAD_
#define _ROAD_

#include <vector>
#include <iostream>
#include <queue>

using std::vector;
using std::queue;
using std::priority_queue;
using std::cin;
using std::cout;
using std::endl;
using std::operator<;
using std::operator>;

struct queueNode
{
	int carID;
	int depTime;
	queueNode(const int& x, const int& y) : carID(x), depTime(y) {}
	friend bool operator < (const queueNode& theNode, const queueNode& theNode2)
	{
		return theNode2.depTime > theNode.depTime;
	}
};

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

	vector<vector<int> > roads;	//道路数组

	// 自定义小根堆	<车辆 ID, 指定出发时间>
	priority_queue<queueNode, vector<queueNode>, std::less<queueNode> > waitingPriority;	//等待上路的优先车辆（按出发时间排序）
	priority_queue<queueNode, vector<queueNode>, std::less<queueNode> > waitingGeneral;		//等待上路的非优先车辆（按出发时间排序）
};

void road::enQueue(const car& theCar)
{
	bool isPriority = theCar.isPriority;
	if (isPriority)
		waitingPriority.push(queueNode(theCar.carID, theCar.realTime));
	else
		waitingGeneral.push(queueNode(theCar.carID, theCar.realTime));
}

#endif