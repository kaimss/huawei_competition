#pragma once
#ifndef _MAP_
#define _MAP_

#include "dependencies.h"
#include "carList.h"

class map
{
public:
	map(const char* roadFilePath, const char* crossFilePath, 
		const char* carFilePath, const char* answerFilePath);
	map(const map& theMap);
	~map();

private:
	int numRoads;
	carList *carlist;
	vector<vector<road>> *roadMap;	//边集合
	vector<cross> *crossMap;			//路口集合

	ifstream roadStream;	//道路文件流
	ifstream crossStream;	//路口文件流
	ifstream routeStream;	//路线文件流

	bool initRoad(const char* roadFilePath);		//初始化道路信息
	bool initCross(const char* crossFilePath);		//初始化路口信息
	bool initRoute(const char* answerFilePath);		//初始化路径信息


};

map::map(const char* roadFilePath, const char* crossFilePath, const char* carFilePath, const char* answerFilePath)
{
	carlist = new carList(carFilePath);
	initCross(crossFilePath);
	initRoad(roadFilePath);
	initRoute(answerFilePath);
}

bool map::initRoad(const char* roadFilePath)
{
	const int roads = crossMap->size();
	if (roads == 0)
	{
		cout << "请先加载道路文件!" << endl;
		return false;
	}
	roadMap = new vector<vector<road>>(roads, vector<road>(roads));

	roadStream.open(roadFilePath, ios::in | ios::out);
	if (!roadStream.is_open()) {
		cout << "文件打开错误" << endl;
		return false;
	}
	string infile;
	char str[10], one;
	int id, channel, start, dest, length, maxSpeed, single;
	road *insert;
	while (!roadStream.eof())
	{
		one = roadStream.get();//读掉左括号或者'#'
		if (one == '#')//如果读到的是'#'则忽略这一行
			getline(roadStream, infile);
		else//否则按格式读取
		{
			roadStream.getline(str, 10, ',');
			id = std::atoi(str);

			roadStream.getline(str, 10, ',');
			length = std::atoi(str);

			roadStream.getline(str, 10, ',');
			maxSpeed = std::atoi(str);

			roadStream.getline(str, 10, ',');
			channel = std::atoi(str);

			roadStream.getline(str, 10, ',');
			start = std::atoi(str);

			roadStream.getline(str, 10, ',');
			dest = std::atoi(str);

			roadStream.getline(str, 10, ')');
			single = std::atoi(str);

			one = roadStream.get();//读掉换行符

			//cout << id << length << maxSpeed << channel << start << dest << single << endl;
			roadMap->at(start).at(dest).id = id;
			roadMap->at(start).at(dest).length = length;
			roadMap->at(start).at(dest).maxRoadSpeed = maxSpeed;
			roadMap->at(start).at(dest).channels = channel;
			numRoads++;

			vector<int> temp(length + 1, 0);
			for (int i = 0; i <= channel; i++)
				roadMap->at(start).at(dest).roads.push_back(temp);

			if (single == 1)
			{
				roadMap->at(dest).at(start).id = id;
				roadMap->at(dest).at(start).length = length;
				roadMap->at(dest).at(start).maxRoadSpeed = maxSpeed;
				roadMap->at(dest).at(start).channels = channel;
				numRoads++;
				vector<int> temp(length + 1, 0);
				for (int i = 0; i <= channel; i++)
					roadMap->at(dest).at(start).roads.push_back(temp);
			}
		}
	}
	roadStream.close();
	return true;
}

bool map::initCross(const char* crossFilePath)
{
	//初始化函数，将读入的文件填写路口
	string infile;
	char str[10], one;
	crossMap->resize(100);	//初始化
	crossStream.open(crossFilePath, ios::in | ios::out);
	if (!crossStream.is_open()) {
		cout << "文件打开错误" << endl;
		throw UNKNOWN_METHOD;
	}
	int id, from, to, speed, planTime;
	int i = 0;//行计数器，用于重新调整vector容器大小
	while (!crossStream.eof())
	{
		one = crossStream.get();//读掉左括号或者'#'
		if (one == '#')//如果读到的是'#'则忽略这一行
			getline(crossStream, infile);
		else//否则按格式读取
		{
			crossStream.getline(str, 10, ',');
			crossMap->at(i).adjaRoadID.push_back(std::atoi(str));

			crossStream.getline(str, 10, ',');
			crossMap->at(i).adjaRoadID.push_back(std::atoi(str));

			crossStream.getline(str, 10, ',');
			crossMap->at(i).adjaRoadID.push_back(std::atoi(str));

			crossStream.getline(str, 10, ')');
			crossMap->at(i).adjaRoadID.push_back(std::atoi(str));
			i++;
		}
	}
	crossMap->resize(i);//调整容器大小
	crossStream.close();
}

bool map::initRoute(const char* answerFilePath)
{
	//初始化函数，将读入的文件填写路口
	string infile;
	char str[10], one;
	crossMap->resize(100);	//初始化
	routeStream.open(answerFilePath, ios::in | ios::out);
	if (!routeStream.is_open()) {
		cout << "文件打开错误" << endl;
		throw UNKNOWN_METHOD;
	}
	int id, scheduledTime, passNode;
	int i = 0;//行计数器，用于重新调整vector容器大小
	while (!crossStream.eof())
	{
		one = crossStream.get();//读掉左括号或者'#'
		if (one == '#')//如果读到的是'#'则忽略这一行
			getline(crossStream, infile);
		else//否则按格式读取
		{
			///------------------------------------------------------------------
			///------------------------------------------------------------------
			///------------------------------------------------------------------
			///------------------------------------------------------------------
			///------------------------------------------------------------------
			///------------------------------------------------------------------
			///------------------------------------------------------------------
			///------------------------------------------------------------------
			///------------------------------------------------------------------
			///------------------------------------------------------------------

			crossStream.getline(str, 10, ',');
			crossMap->at(i).adjaRoadID.push_back(std::atoi(str));

			crossStream.getline(str, 10, ',');
			crossMap->at(i).adjaRoadID.push_back(std::atoi(str));

			crossStream.getline(str, 10, ',');
			crossMap->at(i).adjaRoadID.push_back(std::atoi(str));

			crossStream.getline(str, 10, ',');
			crossMap->at(i).adjaRoadID.push_back(std::atoi(str));
			i++;
		}
	}
	crossMap->resize(i);//调整容器大小
	crossStream.close();
}


#endif