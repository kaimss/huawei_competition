#pragma once
#ifndef _CROSSLIST_
#define _CROSSLIST_

#include "dependencies.h"

class crossList
{
	//承载路口的容器
public:
	crossList() { crossets = NULL; MAPPING = NULL; }
	~crossList() { delete crossets; delete MAPPING; }
	crossList(const char* filePath);

	//通过路口
	const cross& getCross(const int& id);
	const cross& getCrossByIndex(const int& index);
	//获得路口上下左右的道路编号
	const int& getRoadID(const int& id, const DIRECTION& dir);
	const int& getRoadIDByIndex(const int& index, const DIRECTION& dir);
	//根据路口 ID 获得所在的下标
	const int& getIndex(const int& id);
	//获得路口所有连接道路的编号
	void getRoads(const int& id, int* roadsIDs);
	void getRoadsByIndex(const int& index, int* roadsIDs);
	//获得总路口数目
	const int& size() { return crossets->size(); }

	const int& nextPoint(const int& originPoint, const int& roadID, 
		map<int, int>* MAPPINGfirst, map<int, int>* MAPPINGsecond,
		vector<vector<road> >  *roadMap);

private:
	vector<cross> *crossets;			//路口集合
	ifstream crosstream;
	map<int, int> *MAPPING;		//从路口编号到下标的映射
};

crossList::crossList(const char* filePath)
{	
	MAPPING = new map<int, int>();
	//加载路口文件
	crossets = new vector<cross>();
	//初始化函数，将读入的文件填写路口
	string infile;
	char str[10], one;
	crossets->resize(300);	//初始化
	crosstream.open(filePath, ios::in | ios::out);
	if (!crosstream.is_open()) {
		cout << "文件打开错误" << endl;
		throw UNKNOWN_METHOD;
	}
	int id, from, to, speed, planTime;
	int i = 0;//行计数器，用于重新调整vector容器大小
	while (!crosstream.eof())
	{
		one = crosstream.get();//读掉左括号或者'#'
		if (one == '#')//如果读到的是'#'则忽略这一行
			getline(crosstream, infile);
		else//否则按格式读取
		{
			crosstream.getline(str, 10, ',');
			id = std::atoi(str);
			crossets->at(i).id = id;

			crosstream.getline(str, 10, ',');
			crossets->at(i).adjaRoadID.push_back(std::atoi(str));

			crosstream.getline(str, 10, ',');
			crossets->at(i).adjaRoadID.push_back(std::atoi(str));

			crosstream.getline(str, 10, ',');
			crossets->at(i).adjaRoadID.push_back(std::atoi(str));

			crosstream.getline(str, 10, ')');
			crossets->at(i).adjaRoadID.push_back(std::atoi(str));

			MAPPING->insert(pair<int, int>(id, i));

			//crosstheMap->at(crossID).disp();	debug 用
			i++;
			one = crosstream.get();
		}
	}
	crossets->resize(i);//调整容器大小
	crosstream.close();

}

const cross& crossList::getCross(const int& id)
{	//根据路口 id 获得对应的路口
	if (id < 0)
	{
		cout << "cross 编号非法：" << id << endl;
		throw ILLEGAL_PARAMETER;
	}
	map<int, int>::iterator iter;
	iter = MAPPING->find(id);
	if (iter != MAPPING->end())
		return crossets->at((*iter).second);
	else
		return crossets->at(crossets->size());
}

const cross& crossList::getCrossByIndex(const int& index)
{
	if (index < 0 || index >= crossets->size())
	{
		cout << "下标非法:" << index << endl;
		throw ILLEGAL_PARAMETER;
	}
	return crossets->at(index);
}

const int& crossList::getRoadID(const int& id, const DIRECTION& dir)
{
	if (id < 0)
	{
		cout << "路口 id 非法:" << id << endl;
		throw ILLEGAL_PARAMETER;
	}
	map<int, int>::iterator iter = MAPPING->find(id);
	if (iter != MAPPING->end())
		return crossets->at((*iter).second).adjaRoadID[dir];
	else
		return -1;
}

const int& crossList::getRoadIDByIndex(const int& index, const DIRECTION& dir)
{
	if (index < 0 || index >= crossets->size())
	{
		cout << "下标非法:" << index << endl;
		throw ILLEGAL_PARAMETER;
	}
	return crossets->at(index).adjaRoadID[dir];
}

const int& crossList::getIndex(const int& id)
{	//根据路口 id 获得在数组中的下标
	if (id < 0)
	{
		cout << "路口 id 非法：" << id << endl;
		throw ILLEGAL_PARAMETER;
	}
	map<int, int>::iterator iter = MAPPING->find(id);
	return (*iter).second;
}

void crossList::getRoads(const int& id, int* roadsIDs)
{
	if (id < 0)
	{
		cout << "路口 id 非法:" << id << endl;
		throw ILLEGAL_PARAMETER;
	}
	map<int, int>::iterator iter = MAPPING->find(id);
	const cross& theCross = crossets->at((*iter).second);
	memcpy(roadsIDs, &(crossets[0]), 4);
}

void crossList::getRoadsByIndex(const int& index, int* roadsIDs)
{
	if (index < 0 || index >= crossets->size())
	{
		cout << "下标非法:" << index << endl;
		throw ILLEGAL_PARAMETER;
	}
	const cross& theCross = crossets->at(index);
	memcpy(roadsIDs, &(crossets[0]), 4);
}

const int& crossList::nextPoint(const int& originPoint, const int& roadID, 
	map<int,int>* MAPPINGfirst, map<int,int>* MAPPINGsecond, vector<vector<road> >  *roadMap)
{
	///---------------------------------------------------------------
	///遍历从 originPoint 出发的四条路径，从而得到指定道路 ID 的终点
	/// originPoint 为起始路口的编号
	cross theCross = getCross(originPoint);	//获得路口
	//找到顶点，遍历四条路
	int dest = 0;
	DIRECTION dir[4] = { UP,RIGHT,DOWN,LEFT };
	map<int, int>::iterator iterFirst = MAPPINGfirst->begin();
	map<int, int>::iterator iterSecond = MAPPINGsecond->begin();
	for (int i = 0; i < 4; i++)
	{
		iterFirst = MAPPINGfirst->find(roadID);
		if (iterFirst != MAPPINGfirst->end())
			return (*iterFirst).second;
		iterSecond = MAPPINGsecond->find(roadID);
		if (iterSecond != MAPPINGfirst->end())
			return (*iterSecond).second;
	}
	return -1;
}
#endif