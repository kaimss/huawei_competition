#pragma once
#ifndef _ROAD_
#define _ROAD_

#include <vector>
#include <iostream>

using std::vector;
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
	int id;				//道路 ID
	int length;			//道路长度
	int maxRoadSpeed;	//最大限速
	int channels;		//车道数量

	vector<vector<int>> roads;
};

#endif