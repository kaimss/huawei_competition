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

	int id;				//��· ID
	int length;			//��·����
	int maxRoadSpeed;	//�������
	int channels;		//��������

	vector<vector<int> > roads;	//��·����

	// �Զ���С����	<���� ID, ָ������ʱ��>
	priority_queue<queueNode, vector<queueNode>, std::less<queueNode> > waitingPriority;	//�ȴ���·�����ȳ�����������ʱ������
	priority_queue<queueNode, vector<queueNode>, std::less<queueNode> > waitingGeneral;		//�ȴ���·�ķ����ȳ�����������ʱ������
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