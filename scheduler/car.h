#pragma once
#ifndef _CAR_
#define _CAR_

#include <vector>
#include <iostream>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

enum carStatus { WAITING,  TERMINATE };
//四种情况下的车状态

struct car
{
	car() :carID(0), deparID(0), destID(0), maxCarSpeed(0), planTime(0), realTime(0), status(WAITING)
	{
		routine = new vector<int>();
	}

	car(int theCarID, int theDeparID, int theDestID, int theMaxCarSpeed, int thePlanTime) :
		carID(theCarID), deparID(theDeparID), destID(theDestID), maxCarSpeed(theMaxCarSpeed), planTime(thePlanTime)
	{
		status = WAITING;
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
	carStatus status;
};

#endif