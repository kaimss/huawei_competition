#pragma once
#ifndef _EDGE_
#define _EDGE_

struct edge
{
	int id;			//��·���
	int channel;	//ͨ������
	int length;		//��·����
	int maxSpeed;	//����ٶ�

	edge() :id(0),channel(0), length(0), maxSpeed(0) {}

	edge(int theId, int theChannel, int theLength, int topSpeed) :
		id(theId), channel(theChannel), length(theLength), maxSpeed(topSpeed) {}
};



#endif