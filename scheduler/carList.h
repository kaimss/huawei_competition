#pragma once
#ifndef _CARLIST_
#define _CARLIST_

#include "dependencies.h"

#include "crossList.h"

class carList
{
public:
	carList() { carsets = NULL; }
	carList(const char* filePath);

	car &getCar(const int id)
	{	//根据 id 查找对应的车辆结构体
		//索引存放在容器 MAPPING 中
		if (carsets->size() == 0)
			throw UNKNOWN_METHOD;
		map<int, int>::iterator iter;
		iter = MAPPING->find(id);
		if (iter != MAPPING->end())
			return carsets->at((*iter).second);
		else
			return carsets->at(carsets->size());
	}

	car &getCarByIndex(const int& index)
	{
		return carsets->at(index);
	}

	car & operator[](std::size_t position) { return carsets->at(position); }

	void resize(int size) { carsets->resize(size); }
	int size() { return carsets->size(); }

private:
	vector<car> *carsets;
	ifstream carstream;
	map<int, int> *MAPPING;	//用于查找
};

carList::carList(const char* filePath)
{
	MAPPING = new map<int, int>();	//建立车辆 id 到下标的映射
	carsets = new vector<car>();
	//初始化函数，将读入的文件填写到车数组中
	string infile;
	char str[10], one;
	carsets->resize(70000);//初始化有container辆车，后面可以修改大小
	carstream.open(filePath, ios::in | ios::out);
	if (!carstream.is_open()) {
		cout << "文件打开错误" << endl;
		throw UNKNOWN_METHOD;
	}
	int id = 0, from = 0, to = 0;
	bool preset = false, priority = false;
	int i = 0;//行计数器，用于重新调整vector容器大小
	while (!carstream.eof())
	{
		one = carstream.get();//读掉左括号或者'#'
		if (one == '#')//如果读到的是'#'则忽略这一行
			getline(carstream, infile);
		else//否则按格式读取
		{	//车辆 ID
			carstream.getline(str, 10, ',');
			id = std::atoi(str);
			carsets->at(i).carID = id;

			//出发路口 ID
			carstream.getline(str, 10, ',');
			from = std::atoi(str);
			carsets->at(i).deparID = from;

			//目的地路口 ID
			carstream.getline(str, 10, ',');
			to = std::atoi(str);
			carsets->at(i).destID = to;

			//最大限速
			carstream.getline(str, 10, ',');
			carsets->at(i).maxCarSpeed= std::atoi(str);
			
			//计划出发时间
			carstream.getline(str, 10, ',');
			carsets->at(i).planTime = std::atoi(str);

			carstream.getline(str, 10, ',');
			priority = (std::atoi(str) == 0) ? false : true;
			carsets->at(i).isPriority = priority;

			carstream.getline(str, 10, ')');
			preset = (std::atoi(str) == 0) ? false : true;
			carsets->at(i).isPreSet = preset;
			
			MAPPING->insert(pair<int, int>(id, i));

			//carsets->at(i).disp();	debug 用
			i++;
			one = carstream.get();
		}
	}
	carsets->resize(i);//调整容器大小
	carstream.close();
}

#endif
