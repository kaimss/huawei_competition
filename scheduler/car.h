#pragma once
#ifndef _CAR_
#define _CAR_

enum carStatus { UNUSED, WAITING,  TERMINATE };
//四种情况下的车状态

struct car
{
	car() :carID(0), deparID(0), destID(0), maxCarSpeed(0), planTime(0), realTime(0), status(UNUSED)
	{
		routine = NULL;
	}

	car(int theCarID, int theDeparID, int theDestID, int theMaxCarSpeed, int thePlanTime) :
		carID(theCarID), deparID(theDeparID), destID(theDestID), maxCarSpeed(theMaxCarSpeed), planTime(thePlanTime)
	{
		status = WAITING;
		realTime = thePlanTime;
		routine = new vector<int>();
		routine->resize(10);
	}

	bool operator==(const car& theCar)
	{
		return this->carID == theCar.carID;
	}

	int carID;
	int deparID;
	int destID;
	int maxCarSpeed;
	int planTime;
	int realTime;
	carStatus status;

	vector<int> *routine;	//车辆路线
};


#endif