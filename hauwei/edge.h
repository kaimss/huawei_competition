#pragma once
#ifndef _EDGE_
#define _EDGE_

struct edge
{
	int vertex1;	//��·���
	int vertex2;	//��·�յ�
	int length;		//��·����
	int maxSpeed;	//����ٶ�
	int width;		//��·���

	edge() :vertex1(0), vertex2(0), length(0), maxSpeed(0), width(0) {}

	edge(int theVertex1, int theVertex2, int theLength, int topSpeed, int theWidth) :
		vertex1(theVertex1), vertex2(theVertex2), length(theLength), maxSpeed(topSpeed), width(theWidth) {}
};



#endif