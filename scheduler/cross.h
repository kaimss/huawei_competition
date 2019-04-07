#pragma once
#ifndef _CROSS_
#define _CROSS_

#include <vector>
#include <iostream>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

struct cross
{
	cross() :id(0) {}

	void disp()
	{
		cout << id << ",";
		for (int i = 0; i < 4; i++)
			cout << adjaRoadID.at(i) << ",";
		cout << endl;
	}

	int id;

	vector<int> adjaRoadID;
};

#endif