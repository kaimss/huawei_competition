#pragma once
#ifndef _CARARRAY_
#define _CARARRAY_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "car.h"
using namespace std;

const int CONTAINER = 100000;

class carArray
{
public:
	bool iniCar(const char* fileName);//初始化车辆数据，参数为文件路径
	bool iniCar2(const char* fileName);//初始化车辆数据之二，参数为文件路径

	car& getCar(int i);//返回第i辆车
	int getNumber();//返回车辆数目
	int getmaxplantime();//返回最大出发时间
	void pop_back();
	car back();
	void push_back(car tcar);
	
	

private:
	//vector<car> carsets(contianer);//需要给定一个初始化值以减少后面push_back的次数而减少时间
						   //有错，在声明.h 文件中不能直接调用vector类的析构函数赋值，需要在其他函数中声明大小
	vector<car> carsets;//车辆集合
	ifstream carstream;//读取car.txt文件流
	int maxplantime = 0;//最大非预置车辆出行时间
	int persetnumber = 0;//预置车数量
	int npernumber = 0;//非预置车数量
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
	srand((unsigned int)time(NULL));
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
	bool isPriority, isPreSet;
	int i = 0;//行计数器，用于重新调整vector容器大小    //也即非预置车辆的树目
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

			carstream.getline(str, 10, ',');
			planTime = std::atoi(str);	

			if(planTime > maxplantime)
				maxplantime = planTime;

			carstream.getline(str, 10, ',');
			isPriority = std::atoi(str) == 1 ? true : false;

			carstream.getline(str, 10, ')');
			isPreSet = std::atoi(str) == 1 ? true : false;

			one = carstream.get();//读掉换行符

			//赋值
			if (!isPreSet)
			{//如果是非预置车辆，则读取并加入carsets
				carsets[i].id = id;
				carsets[i].from = from;
				carsets[i].to = to;
				carsets[i].maxSpeed = speed;
				carsets[i].planTime = planTime;
				carsets[i].isPriority = isPriority;
				carsets[i].isPreSet = isPreSet;
				i++;
				persetnumber++;
			}
			else
			{
				if ((npernumber % 10 + rand() % 9) == 0)
				{
					carsets[i].id = id;
					carsets[i].from = from;
					carsets[i].to = to;
					carsets[i].maxSpeed = speed;
					carsets[i].planTime = planTime;
					carsets[i].isPriority = isPriority;
					carsets[i].isPreSet = isPreSet;
					i++;
				}



				npernumber++;
			}
			//cout << i << "  " << id << endl;
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
int carArray::getmaxplantime()
{
	return maxplantime;
}
void carArray::pop_back()
{
	carsets.pop_back();
}
car carArray::back()
{
	return carsets.back();
}
void carArray::push_back(car tcar)
{
	carsets.push_back(tcar);

}
void binSort(carArray& carTime)
{
	//for (int index = 0; index < 10240; index++)
	//{
	//	carTime[index].first = index + 10000;
	//	carTime[index].second = cars.getCar(index).planTime;
	//}
	int range = carTime.getmaxplantime() + 1;
	int numberOfElements = carTime.getNumber();
	vector<car> one;
	vector<vector<car>> cars(range, one);
	for (int i = 0; i < numberOfElements; i++)
	{
		
		//car[i](1);
		car temp = carTime.back();
		carTime.pop_back();
		//cout << "one " << i << "temp.second = " << temp.second << endl;
		cars[temp.planTime].push_back(temp);
	}

	for (int j = range-1; j >= 0; j--)
	{
		//cout << "two " << j << endl;
		while (!cars[j].empty()) 
		{
			car temp = cars[j].front();
			vector<car>::iterator k = cars[j].begin();
			cars[j].erase(k);
			carTime.push_back(temp);
         }
	}
	//delete []car;
}


#endif

