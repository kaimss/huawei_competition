#pragma once
#ifndef _EDGE_
#define _EDGE_

#include <vector>
using namespace std;
const int INF = 0x6f6f6f6f;

struct edge
{
	int id;			//道路编号
	int channel;	//通道数量
	int length;		//道路长度
	int maxSpeed;	//最大速度
	vector<vector<int> > road;     //道路数组
	//int **road;     //道路数组

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


	//一般重载双目运算符为友元函数，重载单目运算符和复合运算符为成员函数
	//必须重载"="为成员函数，重载"<<"">>"为友元函数
	int operator =(const edge &a);
	friend bool operator >(const edge &a, const edge &b);
	friend bool operator >=(const edge &a, const edge &b);
	friend bool operator <(const edge &a, const edge &b);
	friend bool operator <=(const edge &a, const edge &b);
	friend bool operator ==(const edge &a, const edge &b);
	friend bool operator !=(const edge &a, const edge &b);
	friend bool operator !=(const edge &a, const int &b);
	friend edge operator + (const edge &a, const edge &b);//重载结构体＋，目前仅将length相加，其他的量保持与a相同
	friend edge operator - (const edge &a, const edge &b);//重载结构体-，目前仅将length相加，其他的量保持与a相同
	//friend ostream& operator << (ostream &out, const edge &p);//重载输出流，输出内容待定（使用时需要引入头文件及定义命名空间）


	

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