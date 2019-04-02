#pragma once
#ifndef _MAP_
#define _MAP_

#include "dependencies.h"
#include "carList.h"

class map
{
public:
	//���캯���������ĸ��ļ���
	map(const char* roadFilePath, const char* crossFilePath, 
		const char* carFilePath, const char* answerFilePath);
	//���ƹ��캯������ʵ��
	map(const map& theMap);
	//������������ʵ��
	~map();

	//���������ճ���˳��������򣬴�ǰ������Ͱ����
	void sortCars(int range) { binSort(range); }
	//���г������ȣ��ɹ����� 0 �������������ʱ���ϵͳ�ܵ���ʱ��
	//ʧ�ܷ�������·�ڲ���������������������
	//��������·�ڱ�ţ��������󷵻ظ�ֵ
	int simulate(int& totalTimes, int& finishTime);

private:
	int numRoads;		//��·������
	carList *carlist;	//��������
	vector<vector<road>> *roadMap;	//�߼���
	vector<cross> *crossMap;		//·�ڼ���
	vector<pair<int, int>>* carTime;//����������

	ifstream roadStream;	//��·�ļ���
	ifstream crossStream;	//·���ļ���
	ifstream routeStream;	//·���ļ���

	bool initRoad(const char* roadFilePath);		//��ʼ����·��Ϣ
	bool initCross(const char* crossFilePath);		//��ʼ��·����Ϣ
	bool initRoute(const char* answerFilePath);		//��ʼ��·����Ϣ

	void binSort(int range);	//�Գ������ճ���ʱ���������
	void setCarStatus(int theSecond);	//�������г�����״̬
	int proBlockCars(int theSecond);	//�������г���
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
		cout << "���ȼ��ص�·�ļ�!" << endl;
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

			roadStream.getline(str, 10, ',');
			dest = std::atoi(str);

			roadStream.getline(str, 10, ')');
			single = std::atoi(str);

			one = roadStream.get();//�������з�

			roadMap->at(start).at(dest).id = id;
			roadMap->at(start).at(dest).length = length;
			roadMap->at(start).at(dest).maxRoadSpeed = maxSpeed;
			roadMap->at(start).at(dest).channels = channel;
			//roadMap->at(start).at(dest).disp();	debug ��
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
				//roadMap->at(dest).at(start).disp();	debug ��
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
	crossMap = new vector<cross>();
	//��ʼ����������������ļ���д·��
	string infile;
	char str[10], one;
	crossMap->resize(100);	//��ʼ��
	crossStream.open(crossFilePath, ios::in | ios::out);
	if (!crossStream.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		throw UNKNOWN_METHOD;
	}
	int id, from, to, speed, planTime;
	int i = 0;//�м��������������µ���vector������С
	while (!crossStream.eof())
	{
		int crossID = 0;
		one = crossStream.get();//���������Ż���'#'
		if (one == '#')//�����������'#'�������һ��
			getline(crossStream, infile);
		else//���򰴸�ʽ��ȡ
		{
			crossStream.getline(str, 10, ',');
			crossID = std::atoi(str);
			crossMap->at(crossID).id = crossID;

			crossStream.getline(str, 10, ',');
			crossMap->at(crossID).adjaRoadID.push_back(std::atoi(str));

			crossStream.getline(str, 10, ',');
			crossMap->at(crossID).adjaRoadID.push_back(std::atoi(str));

			crossStream.getline(str, 10, ',');
			crossMap->at(crossID).adjaRoadID.push_back(std::atoi(str));

			crossStream.getline(str, 10, ')');
			crossMap->at(crossID).adjaRoadID.push_back(std::atoi(str));

			//crossMap->at(crossID).disp();	debug ��
			i++;
			one = crossStream.get();
		}
	}
	crossMap->resize(i);//����������С
	crossStream.close();
}

bool map::initRoute(const char* answerFilePath)
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

	while (!routeStream.eof())
	{
		one = routeStream.get();//���������Ż���'#'
		if (routeStream.eof())
			return true;
		if (one == '#')//�����������'#'�������һ��
			getline(routeStream, infile);
		else//���򰴸�ʽ��ȡ
		{
			//cout << i << "\t";
			char str[10];
			routeStream.getline(str, 10, ',');//��id
			id = std::atoi(str);
			routeStream.getline(str, 10, ',');//��scheduledTime
			carlist->getCar(id).realTime = std::atoi(str);
			
			while (1)
			{
				sum = 0;
				one = routeStream.get();
				while (one >= 48 && one <= 57)
				{
					sum = sum * 10 + (one - 48);
					one = routeStream.get();

				}
				carlist->getCar(id).routine->push_back(sum);
				if (one == ')')
					break;
			}
			one = routeStream.get();//�������з�
			i++;
		}
	}
	routeStream.close();
}

void map::binSort(int range)
{	
	//��ʼ��
	carTime = new vector<pair<int, int>>();
	carTime->resize(carlist->size());
	//�Գ������ճ���ʱ�����Ͱ����
	for (int index = 0; index < carlist->size(); index++)
	{
		carTime->at(index).first = index + carlist->firstID();
		carTime->at(index).second = carlist->getCar(index+carlist->firstID()).planTime;
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

void map::setCarStatus(int theSecond)
{
	//�趨���г�����״̬
}

int map::proBlockCars(int theSecond)
{
	//��������������Ϣ
	//��������·�ڱ�ţ��ɹ����ȷ���0������ԭ�򷵻ظ���

}

int map::simulate(int& totalTimes, int& finishTime)
{
	//����֮ǰҪ�Գ������ճ���ʱ���������
	//�Գ������е���
	bool deadLock = false;
	bool finished = false;
	int blockPort = 0;
	totalTimes = 0;
	while (blockPort == 0)
	{
		setCarStatus(totalTimes);	//�������г�����״̬
		blockPort = proBlockCars(totalTimes);	//��������״̬Ϊ WAITING �ĳ���
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

#endif