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

	int second;//����ʱ��
	vector<int> dot;//�滮;��·��
	vector<int> adot;//ʵ��;��·��
	vector<int> path;//�滮·��
	vector<int> apath;//ʵ��·��


	int direction;//��ǰ��ʻ����
	int turn;//��·�ڵ�ת��

	
	car() :id(0), from(0), to(0), maxSpeed(0), planTime(0),second(0) {}

	car(int id, int from, int to, int maxSpeed,int planTime, int second) :
		id(id), from(from), to(to), maxSpeed(maxSpeed), planTime(planTime), second(second) {}




};





#endif