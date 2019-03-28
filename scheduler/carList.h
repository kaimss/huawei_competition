#pragma once
#ifndef _CARLIST_
#define _CARLIST_

#include "dependencies.h"

class carList
{
public:
	carList() { carsets = NULL; }
	carList(const char* filePath);

	car &getCar(const int id)
	{
		if (carsets->size() == 0)
			throw UNKNOWN_METHOD;
		return carsets->at(id - firstCarID);
	}

	car & operator[](std::size_t position) { return carsets->at(position); }

	void resize(int size) { carsets->resize(size); }
	int firstID() { return firstCarID; }
	int size() { return carsets->size(); }

private:
	vector<car> *carsets;
	ifstream carstream;
	int firstCarID;
	bool isRead;
};

carList::carList(const char* filePath)
{
	isRead = false;
	carsets = new vector<car>();
	//初始化函数，将读入的文件填写到车数组中
	string infile;
	char str[10], one;
	carsets->resize(20000);//初始化有container辆车，后面可以修改大小
	carstream.open(filePath, ios::in | ios::out);
	if (!carstream.is_open()) {
		cout << "文件打开错误" << endl;
		throw UNKNOWN_METHOD;
	}
	int id = 0, from = 0, to = 0, speed = 0, planTime = 0;
	int i = 0;//行计数器，用于重新调整vector容器大小
	while (!carstream.eof())
	{
		one = carstream.get();//读掉左括号或者'#'
		if (one == '#')//如果读到的是'#'则忽略这一行
			getline(carstream, infile);
		else//否则按格式读取
		{
			carstream.getline(str, 10, ',');
			carsets->at(i).carID = std::atoi(str);

			if (!isRead) {
				firstCarID = std::atoi(str);
				isRead = true;
			}

			carstream.getline(str, 10, ',');
			carsets->at(i).deparID = std::atoi(str);

			carstream.getline(str, 10, ',');
			carsets->at(i).destID = std::atoi(str);

			carstream.getline(str, 10, ',');
			carsets->at(i).maxCarSpeed= std::atoi(str);

			carstream.getline(str, 10, ')');
			carsets->at(i).planTime = std::atoi(str);
			//carsets->at(i).disp();	debug 用
			i++;
			one = carstream.get();
		}
	}
	carsets->resize(i);//调整容器大小
	carstream.close();
}

#endif
