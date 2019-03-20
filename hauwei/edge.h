#pragma once
#ifndef _EDGE_
#define _EDGE_
//可不可以将include的文件放到同一头文件中，防止重复编译？
#include <iostream>
using namespace std;
struct edge
{
	int id;			//道路编号
	int channel;	//通道数量
	int length;		//道路长度
	int maxSpeed;	//最大速度

	edge() :id(0),channel(0), length(0), maxSpeed(0) {}

	edge(int theId, int theChannel, int theLength, int topSpeed) :
		id(theId), channel(theChannel), length(theLength), maxSpeed(topSpeed) {}

	//重载结构体比较（两个参数）
	friend bool operator >(const edge &a, const edge &b)
	{
		return a.length > b.length;
	}
	//重载结构体比较（两个参数）
	friend bool operator >=(const edge &a, const edge &b)
	{
		return a.length >= b.length;
	}
	//重载结构体比较（两个参数）
	friend bool operator <(const edge &a, const edge &b)
	{
		return a.length < b.length;
	}
	//重载结构体比较（两个参数）
	friend bool operator <=(const edge &a, const edge &b)
	{
		return a.length <= b.length;
	}
	//重载结构体比较（两个参数）
	friend bool operator ==(const edge &a, const edge &b)
	{
		return a.length == b.length;
	}
	//重载结构体＋,edge=edge_a+edge_b
	//目前仅将length相加，其他的量保持与a相同
	friend edge operator + (const edge &a, const edge &b)
	{
		return edge(a.id, a.channel, a.length + b.length, a.maxSpeed);
	}
	//重载结构体＋,edge=edge_a-edge_b
	//目前仅将length相加，其他的量保持与a相同
	friend edge operator - (const edge &a, const edge &b)
	{
		return edge(a.id, a.channel, a.length - b.length, a.maxSpeed);
	}

	//重载输出，即cout<<node;
	friend ostream& operator << (ostream &out, const edge &p)
	{
		out << "(" << p.id << ", " << p.channel << ", " << p.length << ", " << p.maxSpeed << ")\n";
		return out;
	}

};



#endif