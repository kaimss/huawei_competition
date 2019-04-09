#pragma once
#ifndef _DEPENDENCIES_
#define _DEPENDENCIES_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include <algorithm>

#include <assert.h>

#include "car.h"
#include "cross.h"
#include "road.h"

#define UNKNOWN_METHOD 0xf1
#define ILLEGAL_PARAMETER 0xf2

const void ASSERT(const bool& exp, const string& theString)
{
	if (exp)
	{
		cout << theString << endl;
		assert(exp);
	}

}

typedef enum DIRECTION { UP, RIGHT, DOWN, LEFT };

using std::cin;
using std::cout;
using std::endl;
using std::operator==;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::ios;
using std::pair;
using std::map;

#endif