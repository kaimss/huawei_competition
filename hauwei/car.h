#pragma once
#ifndef _CAR_
#define _CAR_

struct car
{
	int id;//�������
	int from;//ʼ����
	int to;//Ŀ�ĵ�
	int maxSpeed;//����ٶ�
	int planTime;//����ʱ��

	int cspeed;//��ǰ�ٶ�
	int direction;//��ǰ��ʻ����
	int turn;//��·�ڵ�ת��
	int croad;//��ǰ��ʻ��·
	int cchannel;//��ǰ��ʻ����
	int cfcross;//��ǰ����·��
	int ctcross;//��ǰĿ��·��
	
	car() :id(0), from(0), to(0), maxSpeed(0),planTime(1) {}

	car(int id, int from, int to, int maxSpeed,int planTime) :
		id(id), from(from),to(to),maxSpeed(maxSpeed),planTime(planTime) {}


};





#endif