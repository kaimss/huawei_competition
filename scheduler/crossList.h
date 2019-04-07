#pragma once
#ifndef _CROSSLIST_
#define _CROSSLIST_

#include "dependencies.h"

class crossList
{
	//����·�ڵ�����
public:
	crossList() { crossets = NULL; MAPPING = NULL; }
	~crossList() { delete crossets; delete MAPPING; }
	crossList(const char* filePath);

	//ͨ��·��
	const cross& getCross(const int& id);
	const cross& getCrossByIndex(const int& index);
	//���·���������ҵĵ�·���
	const int& getRoadID(const int& id, const DIRECTION& dir);
	const int& getRoadIDByIndex(const int& index, const DIRECTION& dir);
	//����·�� ID ������ڵ��±�
	const int& getIndex(const int& id);
	//���·���������ӵ�·�ı��
	void getRoads(const int& id, int* roadsIDs);
	void getRoadsByIndex(const int& index, int* roadsIDs);
	//�����·����Ŀ
	const int& size() { return crossets->size(); }

	const int& nextPoint(const int& originPoint, const int& roadID, 
		map<int, int>* MAPPINGfirst, map<int, int>* MAPPINGsecond,
		vector<vector<road> >  *roadMap);

private:
	vector<cross> *crossets;			//·�ڼ���
	ifstream crosstream;
	map<int, int> *MAPPING;		//��·�ڱ�ŵ��±��ӳ��
};

crossList::crossList(const char* filePath)
{	
	MAPPING = new map<int, int>();
	//����·���ļ�
	crossets = new vector<cross>();
	//��ʼ����������������ļ���д·��
	string infile;
	char str[10], one;
	crossets->resize(300);	//��ʼ��
	crosstream.open(filePath, ios::in | ios::out);
	if (!crosstream.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		throw UNKNOWN_METHOD;
	}
	int id, from, to, speed, planTime;
	int i = 0;//�м��������������µ���vector������С
	while (!crosstream.eof())
	{
		one = crosstream.get();//���������Ż���'#'
		if (one == '#')//�����������'#'�������һ��
			getline(crosstream, infile);
		else//���򰴸�ʽ��ȡ
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

			//crosstheMap->at(crossID).disp();	debug ��
			i++;
			one = crosstream.get();
		}
	}
	crossets->resize(i);//����������С
	crosstream.close();

}

const cross& crossList::getCross(const int& id)
{	//����·�� id ��ö�Ӧ��·��
	if (id < 0)
	{
		cout << "cross ��ŷǷ���" << id << endl;
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
		cout << "�±�Ƿ�:" << index << endl;
		throw ILLEGAL_PARAMETER;
	}
	return crossets->at(index);
}

const int& crossList::getRoadID(const int& id, const DIRECTION& dir)
{
	if (id < 0)
	{
		cout << "·�� id �Ƿ�:" << id << endl;
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
		cout << "�±�Ƿ�:" << index << endl;
		throw ILLEGAL_PARAMETER;
	}
	return crossets->at(index).adjaRoadID[dir];
}

const int& crossList::getIndex(const int& id)
{	//����·�� id ����������е��±�
	if (id < 0)
	{
		cout << "·�� id �Ƿ���" << id << endl;
		throw ILLEGAL_PARAMETER;
	}
	map<int, int>::iterator iter = MAPPING->find(id);
	return (*iter).second;
}

void crossList::getRoads(const int& id, int* roadsIDs)
{
	if (id < 0)
	{
		cout << "·�� id �Ƿ�:" << id << endl;
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
		cout << "�±�Ƿ�:" << index << endl;
		throw ILLEGAL_PARAMETER;
	}
	const cross& theCross = crossets->at(index);
	memcpy(roadsIDs, &(crossets[0]), 4);
}

const int& crossList::nextPoint(const int& originPoint, const int& roadID, 
	map<int,int>* MAPPINGfirst, map<int,int>* MAPPINGsecond, vector<vector<road> >  *roadMap)
{
	///---------------------------------------------------------------
	///������ originPoint ����������·�����Ӷ��õ�ָ����· ID ���յ�
	/// originPoint Ϊ��ʼ·�ڵı��
	cross theCross = getCross(originPoint);	//���·��
	//�ҵ����㣬��������·
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