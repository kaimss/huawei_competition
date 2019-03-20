#pragma once
#ifndef _EDGE_
#define _EDGE_
//�ɲ����Խ�include���ļ��ŵ�ͬһͷ�ļ��У���ֹ�ظ����룿
#include <iostream>
using namespace std;
struct edge
{
	int id;			//��·���
	int channel;	//ͨ������
	int length;		//��·����
	int maxSpeed;	//����ٶ�

	edge() :id(0),channel(0), length(0), maxSpeed(0) {}

	edge(int theId, int theChannel, int theLength, int topSpeed) :
		id(theId), channel(theChannel), length(theLength), maxSpeed(topSpeed) {}

	//���ؽṹ��Ƚϣ�����������
	friend bool operator >(const edge &a, const edge &b)
	{
		return a.length > b.length;
	}
	//���ؽṹ��Ƚϣ�����������
	friend bool operator >=(const edge &a, const edge &b)
	{
		return a.length >= b.length;
	}
	//���ؽṹ��Ƚϣ�����������
	friend bool operator <(const edge &a, const edge &b)
	{
		return a.length < b.length;
	}
	//���ؽṹ��Ƚϣ�����������
	friend bool operator <=(const edge &a, const edge &b)
	{
		return a.length <= b.length;
	}
	//���ؽṹ��Ƚϣ�����������
	friend bool operator ==(const edge &a, const edge &b)
	{
		return a.length == b.length;
	}
	//���ؽṹ�士,edge=edge_a+edge_b
	//Ŀǰ����length��ӣ���������������a��ͬ
	friend edge operator + (const edge &a, const edge &b)
	{
		return edge(a.id, a.channel, a.length + b.length, a.maxSpeed);
	}
	//���ؽṹ�士,edge=edge_a-edge_b
	//Ŀǰ����length��ӣ���������������a��ͬ
	friend edge operator - (const edge &a, const edge &b)
	{
		return edge(a.id, a.channel, a.length - b.length, a.maxSpeed);
	}

	//�����������cout<<node;
	friend ostream& operator << (ostream &out, const edge &p)
	{
		out << "(" << p.id << ", " << p.channel << ", " << p.length << ", " << p.maxSpeed << ")\n";
		return out;
	}

};



#endif