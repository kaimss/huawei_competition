#pragma once
#ifndef _ROAD_
#define _ROAD_

struct road
{
	int id;
	int from;
	int to;
	road():id(0),from(0),to(0){}
	road(int id, int from, int to):
		id(id), from(from), to(to) {}
};

#endif

