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

	int id;				//��· ID
	int length;			//��·����
	int maxRoadSpeed;	//�������
	int channels;		//��������

	vector<vector<int>> roads;//��·����

	//ʹ�ö������Ҫ��·�ĳ���
	queue<int> waitingPriority;		//�ȴ���·�����ȳ�����������ʱ������
	queue<int> waitingGeneral;		//�ȴ���·�ķ����ȳ�����������ʱ������
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