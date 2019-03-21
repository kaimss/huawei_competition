#pragma once
#ifndef _EDGE_
#define _EDGE_

const int INF = 0x6f6f6f6f;

struct edge
{
	int id;			//道路编号
	int channel;	//通道数量
	int length;		//道路长度
	int maxSpeed;	//最大速度

	edge() :id(0),channel(0), length(INF), maxSpeed(0) {}

	edge(int theId, int theChannel, int theLength, int topSpeed) :
		id(theId), channel(theChannel), length(theLength), maxSpeed(topSpeed) {}
};



#endif