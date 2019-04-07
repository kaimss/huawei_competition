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
	{	//���� id ���Ҷ�Ӧ�ĳ����ṹ��
		//������������� MAPPING ��
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
	map<int, int> *MAPPING;	//���ڲ���
};

carList::carList(const char* filePath)
{
	MAPPING = new map<int, int>();	//�������� id ���±��ӳ��
	carsets = new vector<car>();
	//��ʼ����������������ļ���д����������
	string infile;
	char str[10], one;
	carsets->resize(70000);//��ʼ����container��������������޸Ĵ�С
	carstream.open(filePath, ios::in | ios::out);
	if (!carstream.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		throw UNKNOWN_METHOD;
	}
	int id = 0, from = 0, to = 0;
	bool preset = false, priority = false;
	int i = 0;//�м��������������µ���vector������С
	while (!carstream.eof())
	{
		one = carstream.get();//���������Ż���'#'
		if (one == '#')//�����������'#'�������һ��
			getline(carstream, infile);
		else//���򰴸�ʽ��ȡ
		{	//���� ID
			carstream.getline(str, 10, ',');
			id = std::atoi(str);
			carsets->at(i).carID = id;

			//����·�� ID
			carstream.getline(str, 10, ',');
			from = std::atoi(str);
			carsets->at(i).deparID = from;

			//Ŀ�ĵ�·�� ID
			carstream.getline(str, 10, ',');
			to = std::atoi(str);
			carsets->at(i).destID = to;

			//�������
			carstream.getline(str, 10, ',');
			carsets->at(i).maxCarSpeed= std::atoi(str);
			
			//�ƻ�����ʱ��
			carstream.getline(str, 10, ',');
			carsets->at(i).planTime = std::atoi(str);

			carstream.getline(str, 10, ',');
			priority = (std::atoi(str) == 0) ? false : true;
			carsets->at(i).isPriority = priority;

			carstream.getline(str, 10, ')');
			preset = (std::atoi(str) == 0) ? false : true;
			carsets->at(i).isPreSet = preset;
			
			MAPPING->insert(pair<int, int>(id, i));

			//carsets->at(i).disp();	debug ��
			i++;
			one = carstream.get();
		}
	}
	carsets->resize(i);//����������С
	carstream.close();
}

#endif
