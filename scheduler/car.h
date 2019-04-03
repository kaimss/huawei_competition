#pragma once
#ifndef _CAR_
#define _CAR_

#include <vector>
#include <iostream>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

enum carStatus { STANDSTILL, WAITING,  TERMINATE };
//四种情况下的车状态

struct car
{
	car() :carID(0), deparID(0), destID(0),
		maxCarSpeed(0), planTime(0), realTime(0),
		status(STANDSTILL), isPreSet(false), isPriority(false)
	{
		routine = new vector<int>();
	}

	car(int theCarID, int theDeparID, int theDestID,
		int theMaxCarSpeed, int thePlanTime, bool ISPRESET, bool ISPRIORITY) :
		carID(theCarID), deparID(theDeparID), destID(theDestID),
		maxCarSpeed(theMaxCarSpeed), planTime(thePlanTime),
		isPreSet(ISPRESET), isPriority(ISPRIORITY)
	{
		status = STANDSTILL;
		realTime = thePlanTime;
		routine = new vector<int>(10);
		routine->resize(10);
	}

	bool operator==(const int& id)
	{
		return carID == id;
	}

	void disp()
	{
		cout << carID << "," << deparID << "," << destID
			<< "," << maxCarSpeed << "," << planTime
			<< "," << realTime << "," << status << endl;
	}

	vector<int> *routine;	//车辆路线

	int carID;
	int deparID;
	int destID;
	int maxCarSpeed;
	int planTime;
	int realTime;

	bool isPreSet;		//是否预置
	bool isPriority;	//是否优先

	carStatus status;
};

#endif