#pragma once
#ifndef _CARARRAY_
#define _CARARRAY_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include "car.h"
using namespace std;

const int CONTAINER = 20000;

class carArray
{
public:
	bool iniCar(const char* fileName);//初始化车辆数据，参数为文件路径
	bool iniCar2(const char* fileName);//初始化车辆数据之二，参数为文件路径

	car& getCar(int i);//返回第i辆车
	int getNumber();//返回车辆数目

private:
	//vector<car> carsets(contianer);//需要给定一个初始化值以减少后面push_back的次数而减少时间
						   //有错，在声明.h 文件中不能直接调用vector类的析构函数赋值，需要在其他函数中声明大小
	vector<car> carsets;//车辆集合
	ifstream carstream;//读取car.txt文件流
};
bool carArray::iniCar(const char* fileName)
{
	//初始化函数，将读入的文件填写到车数组中
	carsets.resize(CONTAINER);//初始化有container辆车，后面可以修改大小
	carstream.open(fileName, ios::in | ios::out);
	if (!carstream.is_open()) {
		cout << "文件打开错误" << endl;
		return false;
	}
	int id, from, to, speed, planTime;
	int i = 0;
	car tempcar;
	while (!carstream.eof())
	{
		carstream >> id >> from >> to >> speed >> planTime;

		//赋值
		carsets[i].id = id;//id从0开始
		carsets[i].from = from;
		carsets[i].to = to;
		carsets[i].maxSpeed = speed;
		carsets[i].planTime = planTime;

		i++;
	}
	carsets.resize(i);//调整容器大小
	carstream.close();
	return true;
}
bool carArray::iniCar2(const char* fileName)
{
	//初始化函数，将读入的文件填写到车数组中
	string infile;
	char str[10], one;
	carsets.resize(CONTAINER);//初始化有container辆车，后面可以修改大小
	carstream.open(fileName, ios::in | ios::out);
	if (!carstream.is_open()) {
		cout << "文件打开错误" << endl;
		return false;
	}
	int id, from, to, speed, planTime;
	int i = 0;//行计数器，用于重新调整vector容器大小
	while (!carstream.eof())
	{
		one = carstream.get();//读掉左括号或者'#'
		if (one == '#')//如果读到的是'#'则忽略这一行
			getline(carstream, infile);
		else//否则按格式读取
		{
			carstream.getline(str, 10, ',');
			id = std::atoi(str);

			carstream.getline(str, 10, ',');
			from = std::atoi(str);

			carstream.getline(str, 10, ',');
			to = std::atoi(str);

			carstream.getline(str, 10, ',');
			speed = std::atoi(str);

			carstream.getline(str, 10, ')');
			planTime = std::atoi(str);

			one = carstream.get();//读掉换行符

			//赋值
			carsets[i].id = id;//id从0开始
			carsets[i].from = from;
			carsets[i].to = to;
			carsets[i].maxSpeed = speed;
			carsets[i].planTime = planTime;

			i++;
		}
	}
	carsets.resize(i);//调整容器大小
	carstream.close();
	return true;
}

car& carArray::getCar(int i)
{
	return carsets[i];
}
int carArray::getNumber()
{
	return carsets.size();
}
#endif
void binSort(vector<pair<int,int>>& carTime,int range)
{
	int numberOfElements = carTime.size();
	vector<pair<int, int>>* car = new vector<pair<int, int>>[range]();

	for (int i = 0; i < numberOfElements; i++)
	{
		//car[i](1);
		pair<int, int> temp = carTime.back();
		carTime.pop_back();
		car[temp.second].push_back(temp);
	}
	for (int j = range-1; j >= 0; j--)
	{
		while (!car[j].empty()) 
		{
			pair<int, int> temp = car[j].front();
			vector<pair<int,int>>::iterator k = car[j].begin();
			car[j].erase(k);
			carTime.push_back(temp);
         }
	}
	delete []car;
}


