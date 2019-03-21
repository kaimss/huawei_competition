#pragma once
#ifndef _EDGE_
#define _EDGE_

#include <vector>
using namespace std;
const int INF = 0x6f6f6f6f;

struct edge
{
	int id;			//��·���
	int channel;	//ͨ������
	int length;		//��·����
	int maxSpeed;	//����ٶ�
	vector<vector<int> > road;     //��·����
	//int **road;     //��·����

	edge() :id(0),channel(0), length(INF), maxSpeed(0) {}

	edge(int theId, int theChannel, int theLength, int topSpeed) :
		id(theId), channel(theChannel), length(theLength), maxSpeed(topSpeed) 
	{

		/*road = new int*[channel];
		for (int i = 0; i < channel; i++)
		{
			road[i] = new int[length];
		}*/
	}


	//һ������˫Ŀ�����Ϊ��Ԫ���������ص�Ŀ������͸��������Ϊ��Ա����
	//��������"="Ϊ��Ա����������"<<"">>"Ϊ��Ԫ����
	int operator =(const edge &a);
	friend bool operator >(const edge &a, const edge &b);
	friend bool operator >=(const edge &a, const edge &b);
	friend bool operator <(const edge &a, const edge &b);
	friend bool operator <=(const edge &a, const edge &b);
	friend bool operator ==(const edge &a, const edge &b);
	friend bool operator !=(const edge &a, const edge &b);
	friend bool operator !=(const edge &a, const int &b);
	friend edge operator + (const edge &a, const edge &b);//���ؽṹ�士��Ŀǰ����length��ӣ���������������a��ͬ
	friend edge operator - (const edge &a, const edge &b);//���ؽṹ��-��Ŀǰ����length��ӣ���������������a��ͬ
	//friend ostream& operator << (ostream &out, const edge &p);//�����������������ݴ�����ʹ��ʱ��Ҫ����ͷ�ļ������������ռ䣩


	

};

int edge::operator =(const edge &a)
{
	return a.length;
}
bool operator >(const edge &a, const edge &b)
{
	return a.length > b.length;
}
bool operator >=(const edge &a, const edge &b)
{
	return a.length >= b.length;
}
bool operator <(const edge &a, const edge &b)
{
	return a.length < b.length;
}
bool operator <=(const edge &a, const edge &b)
{
	return a.length <= b.length;
}
bool operator ==(const edge &a, const edge &b)
{
	return a.length == b.length;
}
bool operator !=(const edge &a, const edge &b)
{
	return a.length != b.length;
}
bool operator !=(const edge &a, const int &b)
{
	return a.length != b;
}
edge operator + (const edge &a, const edge &b)
{
	return edge(a.id, a.channel, a.length + b.length, a.maxSpeed);
}

edge operator - (const edge &a, const edge &b)
{
	return edge(a.id, a.channel, a.length - b.length, a.maxSpeed);
}

//ostream& operator << (ostream &out, const edge &p)
//{
//	out << "(" << p.id << ", " << p.channel << ", " << p.length << ", " << p.maxSpeed << ")\n";
//	return out;
//}



#endif