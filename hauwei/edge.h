#pragma once
#ifndef _EDGE_
#define _EDGE_

struct edge
{
	int vertex1;	//道路起点
	int vertex2;	//道路终点
	int length;		//道路长度
	int maxSpeed;	//最大速度
	int width;		//道路宽度

	edge() :vertex1(0), vertex2(0), length(0), maxSpeed(0), width(0) {}

	edge(int theVertex1, int theVertex2, int theLength, int topSpeed, int theWidth) :
		vertex1(theVertex1), vertex2(theVertex2), length(theLength), maxSpeed(topSpeed), width(theWidth) {}
};



#endif