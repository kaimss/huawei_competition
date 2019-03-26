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
	vector<vector<road>> *roadMap;	//�߼���
	vector<cross> *crossMap;			//·�ڼ���

	ifstream roadStream;	//��·�ļ���
	ifstream crossStream;	//·���ļ���
	ifstream routeStream;	//·���ļ���

	bool initRoad(const char* roadFilePath);		//��ʼ����·��Ϣ
	bool initCross(const char* crossFilePath);		//��ʼ��·����Ϣ
	bool initRoute(const char* answerFilePath);		//��ʼ��·����Ϣ


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
	roadMap = new vector<vector<road>>(roads, vector<road>(roads));

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
		one = crossStream.get();//���������Ż���'#'
		if (one == '#')//�����������'#'�������һ��
			getline(crossStream, infile);
		else//���򰴸�ʽ��ȡ
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
	crossMap->resize(i);//����������С
	crossStream.close();
}

bool map::initRoute(const char* answerFilePath)
{
	//��ʼ����������������ļ���д·��
	string infile;
	char str[10], one;
	crossMap->resize(100);	//��ʼ��
	routeStream.open(answerFilePath, ios::in | ios::out);
	if (!routeStream.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		throw UNKNOWN_METHOD;
	}
	int id, scheduledTime, passNode;
	int i = 0;//�м��������������µ���vector������С
	while (!crossStream.eof())
	{
		one = crossStream.get();//���������Ż���'#'
		if (one == '#')//�����������'#'�������һ��
			getline(crossStream, infile);
		else//���򰴸�ʽ��ȡ
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
	crossMap->resize(i);//����������С
	crossStream.close();
}


#endif