#pragma once
#ifndef _CROSS_
#define _CROSS_

#include <vector>

using std::vector;

struct cross
{
	cross() :id(0) {};

	int id;
	vector<int> adjaRoadID;
};

#endif