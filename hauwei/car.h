#pragma once
#ifndef _CAR_
#define _CAR_
#include <iostream>
using namespace std;
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

	int croad;//��ǰ���ڵ�·
	int cspeed;//��ǰ��ʻ�ٶȣ�����min(��·���٣�ǰ���������ٶ����ƣ���������ٶ�)
	int cchannel;//��ǰ��ʻ����
	int cfrom;//��ǰ����·��
	int cto;//��ǰĿ��·��
	int cdistance = 0;//�ڵ�ǰ��·��ʻ�ľ���
	int direction = 1;//��ǰ��ʻ����1Ϊ����8Ϊ����-1Ϊ�ϣ�-8Ϊ��
	int turn;//��·�ڵ�ת��1ֱ�У�2��ת��3��ת

	int i = 0;//������·�ڻ��·�ļ�������·����������
	
	car() :id(0), from(0), to(0), maxSpeed(0), planTime(0),second(0) {}

	car(int id, int from, int to, int maxSpeed,int planTime, int second) :
		id(id), from(from), to(to), maxSpeed(maxSpeed), planTime(planTime), second(second) {}

	friend ostream& operator << (ostream &out, const car &p);//�����������������ݴ�����ʹ��ʱ��Ҫ����ͷ�ļ������������ռ䣩


};

ostream& operator << (ostream &out, const car &p)
{
	out << "id:"<< p.id << "\tmaxspeed:" << p.maxSpeed << "\nfrom:" << p.from << "\tto:" << p.to ;
	out << "\nplanTime:" << p.planTime << "\n";
	out << "croad:" << p.croad << "\ncchannel:" << p.cchannel << "\tcfrom:" << p.cfrom << "\tcto:" << p.cto;
	out << "\ncspeed:" << p.cspeed << "\tcdistance:" << p.cdistance << "\ndirection:" << p.direction;
	out << "\n";
	return out;
}



#endif