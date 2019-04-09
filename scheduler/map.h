#pragma once
#ifndef _theMap_
#define _theMap_

#include "dependencies.h"
#include "carList.h"
#include "crossList.h"

class theMap
{
public:
	//构造函数，输入四个文件名
	theMap(const char* roadFilePath, const char* crossFilePath, 
		const char* carFilePath, const char* answerFilePath);
	//复制构造函数，待实现
	theMap(const theMap& thetheMap);
	//析构函数，待实现
	~theMap();

	//将车辆按照出发顺序进行排序，从前向后采用桶排序
	void sortCars(int range) { binSort(range); }
	//进行车辆调度，成功返回 0 并设置最短运行时间和系统总调度时间
	//失败返回死锁路口并报以死锁或者其他错误
	//死锁返回路口编号，其他错误返回负值
	int simulate(int& totalTimes, int& finishTime);
	void dispCars();
	void PriorityQueue();

private:
	int numRoads;			//道路的数量
	carList *carlist;		//车辆序列
	crossList *crosslist;	//路口序列

	vector<vector<road>> *roadMap;		//边集合
	vector<pair<int, int>>* carTime;	//车辆排序用

	ifstream roadStream;	//道路文件流
	ifstream routeStream;	//路线文件流

	bool initRoad(const char* roadFilePath);		//初始化道路信息
	bool initRoute(const char* answerFilePath);		//初始化路径信息

	void binSort(int range);			//对车辆按照出发时间进行排序
	void setCarStatus(int theSecond);	//更新所有车辆的状态
	int proBlockCars(int theSecond);	//处理所有车辆
	void driveCarInitList(const bool& priority);

	//<道路 id, pair< 起点（下标）,终点（下标）>
	map<int, pair<int,int> > *roadMAPPING;	//道路 id 到起点和终点的映射
};

theMap::theMap(const char* roadFilePath, const char* crossFilePath,
	const char* carFilePath, const char* answerFilePath)
{
	crosslist = new crossList(crossFilePath);
	initRoad(roadFilePath);
	carlist = new carList(carFilePath);
	initRoute(answerFilePath);
	//dispCars();	debug 用
}

bool theMap::initRoad(const char* roadFilePath)
{
	roadMAPPING = new map<int, pair<int, int> >();

	const int roads = crosslist->size();
	if (roads == 0)
	{
		cout << "请先加载路口文件!" << endl;
		return false;
	}
	roadMap = new vector<vector<road>>(roads + 1, vector<road>(roads + 1));

	roadStream.open(roadFilePath, ios::in | ios::out);
	if (!roadStream.is_open()) {
		cout << "文件打开错误" << endl;
		return false;
	}
	string infile;
	char str[10], one;
	int id, channel, start, dest, length, maxSpeed, single;
	road *insert;
	int posI = 0, posJ = 0;
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
			posI = crosslist->getIndex(start) + 1;

			roadStream.getline(str, 10, ',');
			dest = std::atoi(str);
			posJ = crosslist->getIndex(dest) + 1;

			roadStream.getline(str, 10, ')');
			single = std::atoi(str);

			one = roadStream.get();//读掉换行符

			roadMap->at(posI).at(posJ).id = id;
			roadMap->at(posI).at(posJ).length = length;
			roadMap->at(posI).at(posJ).maxRoadSpeed = maxSpeed;
			roadMap->at(posI).at(posJ).channels = channel;
			//roadMap->at(start).at(dest).disp();	debug 用

			roadMAPPING->insert(pair<int, pair<int, int> >(id, pair<int, int>(start, dest)));

			numRoads++;

			vector<int> temp(length + 1, 0);
			temp[0] = length;
			for (int i = 0; i <= channel; i++)
				roadMap->at(posI).at(posJ).roads.push_back(temp);

			if (single == 1)
			{
				roadMap->at(posJ).at(posI).id = id;
				roadMap->at(posJ).at(posI).length = length;
				roadMap->at(posJ).at(posI).maxRoadSpeed = maxSpeed;
				roadMap->at(posJ).at(posI).channels = channel;
				//roadMap->at(dest).at(start).disp();	debug 用

				numRoads++;
				for (int i = 0; i <= channel; i++)
					roadMap->at(posJ).at(posI).roads.push_back(temp);
			}
		}
	}
	roadStream.close();
	return true;
}

bool theMap::initRoute(const char* answerFilePath)
{
	//初始化函数，将读入的文件填写路口
	string infile;
	char str[10], one;
	routeStream.open(answerFilePath, ios::in | ios::out);
	if (!routeStream.is_open()) {
		cout << "文件打开错误" << endl;
		throw UNKNOWN_METHOD;
	}
	int id, scheduledTime, passNode;
	int sum = 0;
	int i = 0;//行计数器，用于重新调整vector容器大小
	int posI = 0, posJ = 0;
	car* iter;
	int initRoad = 0;
	int nextPoint = 0;
	int initCross = 0;
	while (!routeStream.eof())
	{
		one = routeStream.get();//读掉左括号或者'#'
		if (routeStream.eof())
			return true;
		if (one == '#')//如果读到的是'#'则忽略这一行
			getline(routeStream, infile);
		else//否则按格式读取
		{
			char str[10];
			routeStream.getline(str, 10, ',');	//读id
			id = std::atoi(str);
			iter = &(carlist->getCar(id));

			routeStream.getline(str, 10, ',');	//读scheduledTime
			iter->realTime = std::atoi(str);
			
			while (1)
			{
				sum = 0;
				one = routeStream.get();
				while (one >= 48 && one <= 57)
				{
					sum = sum * 10 + (one - 48);
					one = routeStream.get();
				}
				if(sum != 0)
					iter->routine->push_back(sum);
				if (one == ')')
					break;
			}
			initRoad = iter->routine->at(0);
			//获得车辆的起始路口
			initCross = iter->deparID;
			nextPoint = crosslist->nextPoint(
				initCross, initRoad, roadMAPPING, roadMap);
			if (nextPoint == -1)
				throw 100;	//说明没有找到路口
			posI = crosslist->getIndex(initCross);
			posJ = crosslist->getIndex(nextPoint);

			roadMap->at(posI).at(posJ).enQueue(*iter);	//将车辆放入就绪队列

			one = routeStream.get();//读掉换行符
			i++;
		}
	}
	routeStream.close();
}

void theMap::binSort(int range)
{	//初始化
	carTime = new vector<pair<int, int>>();
	carTime->resize(carlist->size());
	//对车辆按照出发时间进行桶排序，pair<车辆ID，车辆出发时间>
	car *iter;
	for (int index = 0; index < carlist->size(); index++)
	{
		//这两行没用了
		//carTime->at(index).first = index + carlist->firstID();
		//carTime->at(index).second = carlist->getCar(index+carlist->firstID()).planTime;
		iter = &(carlist->getCarByIndex(index));

		carTime->at(index).first = iter->carID;
		carTime->at(index).second = iter->planTime;
	}
	//计算总长度
	int numberOfElements = carlist->size();
	vector<pair<int, int>> one;
	vector<vector<pair<int, int>>> car(range, one);

	for (int i = 0; i < numberOfElements; i++)
	{
		pair<int, int> temp = carTime->back();
		carTime->pop_back();
		car[temp.second].push_back(temp);
	}

	for (int j = range - 1; j >= 0; j--)
	{
		while (!car[j].empty())
		{
			pair<int, int> temp = car[j].front();
			vector<pair<int, int>>::iterator k = car[j].begin();
			car[j].erase(k);
			carTime->push_back(temp);
		}
	}
}

void theMap::PriorityQueue()
{
	//debug用
	int sum = 0;
	int temp = 0;
	road *iter = NULL;
	for (int i = 0; i < crosslist->size(); i++)
	{
		for (int j = 0; j < crosslist->size(); j++)
		{
			cout << "(" << crosslist->getCrossByIndex(i).id << ",";
			cout << crosslist->getCrossByIndex(j).id << ")" << " ";
			iter = &(roadMap->at(i).at(j));
			iter->popAll();
		}
	}
}

void theMap::setCarStatus(int theSecond)
{
	//设定所有车辆的状态
	//扫描所有车或者扫描所有路径，扫描车需要得到第一条路径，扫描路径需要得到第一条路径是本路径的车
	//现在如何得到
	//for (int i = 0; i < carlist->size(); i++)
	//{
	//	if (carlist->getCar(i).planTime == theSecond)
	//	{
	//		//carlist->getCar(i).status = WAITING;
	//		int froad = carlist->getCar(i).routine->at(0);//将要出发的车辆的第一条路径编号
	//		//获得这条路径
	//		//按照条件扫描前方是否有车阻挡
	//		//如果有车阻挡，状态设置为waiting
	//		//如果没有车阻挡，状态设置为terminated
	//	}
	//}
	//对每条道路上的车进行调度
	for (int i = 1; i < roadMap->size(); i++)
	{
		for (int j = 1; j < roadMap->at(i).size(); j++)
		{
			road& trd = roadMap->at(i).at(j);
			if (trd.length == 0)
				break;
			//对一条道路上每条车道上的所有车按顺序调度
			/*
			1,1			1,2			1,3			...			1,length			====>>
			2,1			2,2			2,3			...			2,length			====>>
			...			...			...			...			...					====>>
			channels,1 channels,2	channels,3	...			channels,length		====>>
			*/
			//判断同一车道前方是否有车的数组flag[m]=n表明第m车道第n个位置有车
			int *flag = new int[trd.channels + 1];
			for (int index = 0; index <= trd.channels; index++)
			{
				flag[index] = 0;
			}
			for (int n = trd.length; n >= 1; n--)
			{
				for (int m = 1; m <= trd.channels; m++)
				{
					int id = trd.roads[m][n];
					if (id != 0)
					{//如果当前道路当前车道上有车
						car& tcar = carlist->getCar(id);
						int cspeed = trd.maxRoadSpeed > tcar.maxCarSpeed ? tcar.maxCarSpeed : trd.maxRoadSpeed;
						if (flag[m] > n && flag[m] <= (n + cspeed))
						{//前方阻挡
							int foreid = trd.roads[m][flag[m]];
							tcar.status = carlist->getCar(foreid).status;
						}
						else
						{//前方没有阻挡
							if (n + cspeed > trd.length)//可以过路口，置为等待状态
								tcar.status = WAITING;
							else//不可过路口，置为终止状态
								tcar.status = TERMINATE;
						}
						flag[m] = n;//更新当前车道最前方车辆所在位置
					}
				}
			}
			delete[] flag;
		}
	}
	//对每个路口将要出路口的车辆进行调度
}

int theMap::proBlockCars(int theSecond)
{
	//处理车辆并返回信息
	//死锁返回路口编号，成功调度返回0，其他原因返回负数
	//函数相当于图中的 driveCarInWaitState()
	bool AllTerminate = false;	//所有车辆尚未到达终态
	int roadsIDs[4] = { 0 };
	while (!AllTerminate)
	{
		for (int i = 0; i < crosslist->size(); i++)
		{
			crosslist->getRoadsByIndex(i, roadsIDs);
		}
	}
	return 0;
}

void theMap::driveCarInitList(const bool& priority)
{
	//设置上路车辆
	//priority true 只上路优先车辆
	//priority false 所有车辆都可以上路，但是优先车辆优先上路
	for (/*对所有道路进行遍历*/;;)
	{
		//road.runCarInitList();
	}
}

int theMap::simulate(int& totalTimes, int& finishTime)
{
	//调度之前要对车辆按照出发时间进行排序
	//对车辆进行调度
	bool deadLock = false;
	bool finished = false;
	int blockPort = 0;
	totalTimes = 0;
	while (blockPort == 0)
	{
		totalTimes++;
		setCarStatus(totalTimes);	//设置所有车辆的状态
		driveCarInitList(true);
		blockPort = proBlockCars(totalTimes);	//处理所有状态为 WAITING 的车辆
		if (blockPort > 0)
		{
			cout << "死锁路口" << endl;
			return blockPort;
		}
		driveCarInitList(false);
												//createCarSequence()	//生成优先级队列？
		//从carArray中找到所有的车辆，将马上要出发的车辆状态改为 WAITING
		//按照路口遍历，处理车道上上所有正在运行的车辆
		//如果有车辆要到达终点，状态改为 WAITING
		//如果车辆等待的车状态为 WAITING，则自己的状态改为 WAITING
		//如果车辆等待的车状态为 TERMINATE，则自己的状态改为 TERMINATE
		//先将所有的能够一次运行到终止状态的车辆运行到指定位置并标记为 TERMINATE
		///第一步
		///a)	先处理每条道路上的车辆，将这些车辆进行遍历扫描
		///		如果车在经过行驶速度（前方没有车辆阻挡）可以出路口，将这些车辆标记为等待行驶车辆。
		///b)	车辆如果行驶过程中，前方没有阻挡并且也不会出路口（v=min(最大车速，道路限速)）
		///		则该车辆行驶可行驶的最大车速（v=min(最大车速，道路限速)）
		///		此时该车辆在本次调度确定了该时刻的终止位置。该车辆标记为终止状态。
		///c)	车辆如果行驶过程中，发现前方有车辆阻挡，且阻挡的车辆为等待车辆
		///		则该辆车也被标记为等待行驶车辆。（与阻挡车辆的距离s < v*t)）
		///		其中：v=min(最大车速，道路限速),t=1
		///d)	车辆如果行驶过程中，发现前方有车辆阻挡，且阻挡的车辆为终止状态车辆
		///		则该辆车也被标记为终止车辆。（与前方阻挡的车辆的距离记为s）则该车辆最大行驶速度为
		///		v = min(最高车速，道路限速，s/t) 其中t=1，该车辆最大可行驶距离为s。
		///e)	遍历道路上车辆由第一排向最后一排进行遍历，确定每辆车的行驶状态
		///		（出道路处为道路第一排，入道路处为是后一排）
		///
		///第二步
		///		处理所有路口、道路中处于等待状态的车辆，等待车辆的调度顺序按7、8、9进行调度。
		///7.	整个系统调度按路口ID升序进行调度各个路口，路口内各道路按道路ID升序进行调度。
		///		每个路口遍历道路时，只调度该道路出路口的方向。
		///8.	道路内部车辆调度按任务书给定的优先顺序进行调度。
		///a)	在每次调度中，调度到的车辆要么行驶其可行驶的最大车速，要么就会因等待其他车辆行驶而处于等待行驶状态
		///		待所等待行驶的车辆行驶后，再使该车辆行驶其可行驶的最大车速。
		///b)	是否发生冲突，只与相关道路的第一优先级车辆的行驶方向进行比较，判定是否发生冲突。
		///c)	每条道路如果当前道路第一优先级车辆不能行驶，则当前道路后面的车辆都不能行驶
		///		只有第一优先级的车辆行驶了，后面第二优先级才可以确定是否可以行驶。
		///注：
		///		每个道路（道路R）一旦有一辆等待车辆（记为车A，所在车道记为C）
		///		通过路口而成为终止状态，则会该道路R的车道C上所有车辆进行一次调度
		///		如第一步所示，仅仅处理该道路该车道上能在该车道内行驶后成为终止状态的车辆
		///		（对于调度后依然是等待状态的车辆不进行调度，且依然标记为等待状态）
		///		----尽可能多、尽可能快地将车辆确定为终止状态
		///		（本车道内将可以达到终止状态主要目的是尽快让出空位让其他道路的车辆可以进入该道路
		///		同时会重新识别真正等待出路口的车辆。因为有些车辆是因为前车是等待状态而导致自己也是等待状态
		///		有可能他自己这次根本不会出路口，也就是其不参与出路口的优先级排序---只有出路口的车辆才参与优先级排序）


		totalTimes++;
	}


	return deadLock;
}

void theMap::dispCars()
{
	int sum = 0;
	int temp = 0;
	road *iter = NULL;
	for (int i = 0; i < crosslist->size(); i++)
	{
		for (int j = 0; j < crosslist->size(); j++)
		{
			iter = &(roadMap->at(i).at(j));
			temp = iter->waitingGeneral.size() + iter->waitingPriority.size();
			if (temp == 0)
				continue;
			cout << i << " " << j << " " << temp << "  ";
			sum += temp;
		}
		cout << endl;
	}
	cout << "共: " << sum << " 辆车" << endl;
}
#endif