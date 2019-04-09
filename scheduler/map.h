#pragma once
#ifndef _theMap_
#define _theMap_

#include "dependencies.h"
#include "carList.h"
#include "crossList.h"

class theMap
{
public:
	//���캯���������ĸ��ļ���
	theMap(const char* roadFilePath, const char* crossFilePath, 
		const char* carFilePath, const char* answerFilePath);
	//���ƹ��캯������ʵ��
	theMap(const theMap& thetheMap);
	//������������ʵ��
	~theMap();

	//���������ճ���˳��������򣬴�ǰ������Ͱ����
	void sortCars(int range) { binSort(range); }
	//���г������ȣ��ɹ����� 0 �������������ʱ���ϵͳ�ܵ���ʱ��
	//ʧ�ܷ�������·�ڲ���������������������
	//��������·�ڱ�ţ��������󷵻ظ�ֵ
	int simulate(int& totalTimes, int& finishTime);
	void dispCars();
	void PriorityQueue();

private:
	int numRoads;			//��·������
	carList *carlist;		//��������
	crossList *crosslist;	//·������

	vector<vector<road>> *roadMap;		//�߼���
	vector<pair<int, int>>* carTime;	//����������

	ifstream roadStream;	//��·�ļ���
	ifstream routeStream;	//·���ļ���

	bool initRoad(const char* roadFilePath);		//��ʼ����·��Ϣ
	bool initRoute(const char* answerFilePath);		//��ʼ��·����Ϣ

	void binSort(int range);			//�Գ������ճ���ʱ���������
	void setCarStatus(int theSecond);	//�������г�����״̬
	int proBlockCars(int theSecond);	//�������г���
	void driveCarInitList(const bool& priority);

	//<��· id, pair< ��㣨�±꣩,�յ㣨�±꣩>
	map<int, pair<int,int> > *roadMAPPING;	//��· id �������յ��ӳ��
};

theMap::theMap(const char* roadFilePath, const char* crossFilePath,
	const char* carFilePath, const char* answerFilePath)
{
	crosslist = new crossList(crossFilePath);
	initRoad(roadFilePath);
	carlist = new carList(carFilePath);
	initRoute(answerFilePath);
	//dispCars();	debug ��
}

bool theMap::initRoad(const char* roadFilePath)
{
	roadMAPPING = new map<int, pair<int, int> >();

	const int roads = crosslist->size();
	if (roads == 0)
	{
		cout << "���ȼ���·���ļ�!" << endl;
		return false;
	}
	roadMap = new vector<vector<road>>(roads + 1, vector<road>(roads + 1));

	roadStream.open(roadFilePath, ios::in | ios::out);
	if (!roadStream.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		return false;
	}
	string infile;
	char str[10], one;
	int id, channel, start, dest, length, maxSpeed, single;
	road *insert;
	int posI = 0, posJ = 0;
	while (!roadStream.eof())
	{
		one = roadStream.get();//���������Ż���'#'
		if (one == '#')//�����������'#'�������һ��
			getline(roadStream, infile);
		else//���򰴸�ʽ��ȡ
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

			one = roadStream.get();//�������з�

			roadMap->at(posI).at(posJ).id = id;
			roadMap->at(posI).at(posJ).length = length;
			roadMap->at(posI).at(posJ).maxRoadSpeed = maxSpeed;
			roadMap->at(posI).at(posJ).channels = channel;
			//roadMap->at(start).at(dest).disp();	debug ��

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
				//roadMap->at(dest).at(start).disp();	debug ��

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
	//��ʼ����������������ļ���д·��
	string infile;
	char str[10], one;
	routeStream.open(answerFilePath, ios::in | ios::out);
	if (!routeStream.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		throw UNKNOWN_METHOD;
	}
	int id, scheduledTime, passNode;
	int sum = 0;
	int i = 0;//�м��������������µ���vector������С
	int posI = 0, posJ = 0;
	car* iter;
	int initRoad = 0;
	int nextPoint = 0;
	int initCross = 0;
	while (!routeStream.eof())
	{
		one = routeStream.get();//���������Ż���'#'
		if (routeStream.eof())
			return true;
		if (one == '#')//�����������'#'�������һ��
			getline(routeStream, infile);
		else//���򰴸�ʽ��ȡ
		{
			char str[10];
			routeStream.getline(str, 10, ',');	//��id
			id = std::atoi(str);
			iter = &(carlist->getCar(id));

			routeStream.getline(str, 10, ',');	//��scheduledTime
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
			//��ó�������ʼ·��
			initCross = iter->deparID;
			nextPoint = crosslist->nextPoint(
				initCross, initRoad, roadMAPPING, roadMap);
			if (nextPoint == -1)
				throw 100;	//˵��û���ҵ�·��
			posI = crosslist->getIndex(initCross);
			posJ = crosslist->getIndex(nextPoint);

			roadMap->at(posI).at(posJ).enQueue(*iter);	//�����������������

			one = routeStream.get();//�������з�
			i++;
		}
	}
	routeStream.close();
}

void theMap::binSort(int range)
{	//��ʼ��
	carTime = new vector<pair<int, int>>();
	carTime->resize(carlist->size());
	//�Գ������ճ���ʱ�����Ͱ����pair<����ID����������ʱ��>
	car *iter;
	for (int index = 0; index < carlist->size(); index++)
	{
		//������û����
		//carTime->at(index).first = index + carlist->firstID();
		//carTime->at(index).second = carlist->getCar(index+carlist->firstID()).planTime;
		iter = &(carlist->getCarByIndex(index));

		carTime->at(index).first = iter->carID;
		carTime->at(index).second = iter->planTime;
	}
	//�����ܳ���
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
	//debug��
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
	//�趨���г�����״̬
	//ɨ�����г�����ɨ������·����ɨ�賵��Ҫ�õ���һ��·����ɨ��·����Ҫ�õ���һ��·���Ǳ�·���ĳ�
	//������εõ�
	//for (int i = 0; i < carlist->size(); i++)
	//{
	//	if (carlist->getCar(i).planTime == theSecond)
	//	{
	//		//carlist->getCar(i).status = WAITING;
	//		int froad = carlist->getCar(i).routine->at(0);//��Ҫ�����ĳ����ĵ�һ��·�����
	//		//�������·��
	//		//��������ɨ��ǰ���Ƿ��г��赲
	//		//����г��赲��״̬����Ϊwaiting
	//		//���û�г��赲��״̬����Ϊterminated
	//	}
	//}
	//��ÿ����·�ϵĳ����е���
	for (int i = 1; i < roadMap->size(); i++)
	{
		for (int j = 1; j < roadMap->at(i).size(); j++)
		{
			road& trd = roadMap->at(i).at(j);
			if (trd.length == 0)
				break;
			//��һ����·��ÿ�������ϵ����г���˳�����
			/*
			1,1			1,2			1,3			...			1,length			====>>
			2,1			2,2			2,3			...			2,length			====>>
			...			...			...			...			...					====>>
			channels,1 channels,2	channels,3	...			channels,length		====>>
			*/
			//�ж�ͬһ����ǰ���Ƿ��г�������flag[m]=n������m������n��λ���г�
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
					{//�����ǰ��·��ǰ�������г�
						car& tcar = carlist->getCar(id);
						int cspeed = trd.maxRoadSpeed > tcar.maxCarSpeed ? tcar.maxCarSpeed : trd.maxRoadSpeed;
						if (flag[m] > n && flag[m] <= (n + cspeed))
						{//ǰ���赲
							int foreid = trd.roads[m][flag[m]];
							tcar.status = carlist->getCar(foreid).status;
						}
						else
						{//ǰ��û���赲
							if (n + cspeed > trd.length)//���Թ�·�ڣ���Ϊ�ȴ�״̬
								tcar.status = WAITING;
							else//���ɹ�·�ڣ���Ϊ��ֹ״̬
								tcar.status = TERMINATE;
						}
						flag[m] = n;//���µ�ǰ������ǰ����������λ��
					}
				}
			}
			delete[] flag;
		}
	}
	//��ÿ��·�ڽ�Ҫ��·�ڵĳ������е���
}

int theMap::proBlockCars(int theSecond)
{
	//��������������Ϣ
	//��������·�ڱ�ţ��ɹ����ȷ���0������ԭ�򷵻ظ���
	//�����൱��ͼ�е� driveCarInWaitState()
	bool AllTerminate = false;	//���г�����δ������̬
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
	//������·����
	//priority true ֻ��·���ȳ���
	//priority false ���г�����������·���������ȳ���������·
	for (/*�����е�·���б���*/;;)
	{
		//road.runCarInitList();
	}
}

int theMap::simulate(int& totalTimes, int& finishTime)
{
	//����֮ǰҪ�Գ������ճ���ʱ���������
	//�Գ������е���
	bool deadLock = false;
	bool finished = false;
	int blockPort = 0;
	totalTimes = 0;
	while (blockPort == 0)
	{
		totalTimes++;
		setCarStatus(totalTimes);	//�������г�����״̬
		driveCarInitList(true);
		blockPort = proBlockCars(totalTimes);	//��������״̬Ϊ WAITING �ĳ���
		if (blockPort > 0)
		{
			cout << "����·��" << endl;
			return blockPort;
		}
		driveCarInitList(false);
												//createCarSequence()	//�������ȼ����У�
		//��carArray���ҵ����еĳ�����������Ҫ�����ĳ���״̬��Ϊ WAITING
		//����·�ڱ��������������������������еĳ���
		//����г���Ҫ�����յ㣬״̬��Ϊ WAITING
		//��������ȴ��ĳ�״̬Ϊ WAITING�����Լ���״̬��Ϊ WAITING
		//��������ȴ��ĳ�״̬Ϊ TERMINATE�����Լ���״̬��Ϊ TERMINATE
		//�Ƚ����е��ܹ�һ�����е���ֹ״̬�ĳ������е�ָ��λ�ò����Ϊ TERMINATE
		///��һ��
		///a)	�ȴ���ÿ����·�ϵĳ���������Щ�������б���ɨ��
		///		������ھ�����ʻ�ٶȣ�ǰ��û�г����赲�����Գ�·�ڣ�����Щ�������Ϊ�ȴ���ʻ������
		///b)	���������ʻ�����У�ǰ��û���赲����Ҳ�����·�ڣ�v=min(����٣���·����)��
		///		��ó�����ʻ����ʻ������٣�v=min(����٣���·����)��
		///		��ʱ�ó����ڱ��ε���ȷ���˸�ʱ�̵���ֹλ�á��ó������Ϊ��ֹ״̬��
		///c)	���������ʻ�����У�����ǰ���г����赲�����赲�ĳ���Ϊ�ȴ�����
		///		�������Ҳ�����Ϊ�ȴ���ʻ�����������赲�����ľ���s < v*t)��
		///		���У�v=min(����٣���·����),t=1
		///d)	���������ʻ�����У�����ǰ���г����赲�����赲�ĳ���Ϊ��ֹ״̬����
		///		�������Ҳ�����Ϊ��ֹ����������ǰ���赲�ĳ����ľ����Ϊs����ó��������ʻ�ٶ�Ϊ
		///		v = min(��߳��٣���·���٣�s/t) ����t=1���ó���������ʻ����Ϊs��
		///e)	������·�ϳ����ɵ�һ�������һ�Ž��б�����ȷ��ÿ��������ʻ״̬
		///		������·��Ϊ��·��һ�ţ����·��Ϊ�Ǻ�һ�ţ�
		///
		///�ڶ���
		///		��������·�ڡ���·�д��ڵȴ�״̬�ĳ������ȴ������ĵ���˳��7��8��9���е��ȡ�
		///7.	����ϵͳ���Ȱ�·��ID������е��ȸ���·�ڣ�·���ڸ���·����·ID������е��ȡ�
		///		ÿ��·�ڱ�����·ʱ��ֻ���ȸõ�·��·�ڵķ���
		///8.	��·�ڲ��������Ȱ����������������˳����е��ȡ�
		///a)	��ÿ�ε����У����ȵ��ĳ���Ҫô��ʻ�����ʻ������٣�Ҫô�ͻ���ȴ�����������ʻ�����ڵȴ���ʻ״̬
		///		�����ȴ���ʻ�ĳ�����ʻ����ʹ�ó�����ʻ�����ʻ������١�
		///b)	�Ƿ�����ͻ��ֻ����ص�·�ĵ�һ���ȼ���������ʻ������бȽϣ��ж��Ƿ�����ͻ��
		///c)	ÿ����·�����ǰ��·��һ���ȼ�����������ʻ����ǰ��·����ĳ�����������ʻ
		///		ֻ�е�һ���ȼ��ĳ�����ʻ�ˣ�����ڶ����ȼ��ſ���ȷ���Ƿ������ʻ��
		///ע��
		///		ÿ����·����·R��һ����һ���ȴ���������Ϊ��A�����ڳ�����ΪC��
		///		ͨ��·�ڶ���Ϊ��ֹ״̬�����õ�·R�ĳ���C�����г�������һ�ε���
		///		���һ����ʾ����������õ�·�ó��������ڸó�������ʻ���Ϊ��ֹ״̬�ĳ���
		///		�����ڵ��Ⱥ���Ȼ�ǵȴ�״̬�ĳ��������е��ȣ�����Ȼ���Ϊ�ȴ�״̬��
		///		----�����ܶࡢ�����ܿ�ؽ�����ȷ��Ϊ��ֹ״̬
		///		���������ڽ����Դﵽ��ֹ״̬��ҪĿ���Ǿ����ó���λ��������·�ĳ������Խ���õ�·
		///		ͬʱ������ʶ�������ȴ���·�ڵĳ�������Ϊ��Щ��������Ϊǰ���ǵȴ�״̬�������Լ�Ҳ�ǵȴ�״̬
		///		�п������Լ���θ��������·�ڣ�Ҳ�����䲻�����·�ڵ����ȼ�����---ֻ�г�·�ڵĳ����Ų������ȼ�����


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
	cout << "��: " << sum << " ����" << endl;
}
#endif