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
	//��ʼ����������������ļ���д����������
	string infile;
	char str[10], one;
	carsets->resize(20000);//��ʼ����container��������������޸Ĵ�С
	carstream.open(filePath, ios::in | ios::out);
	if (!carstream.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		throw UNKNOWN_METHOD;
	}
	int id = 0, from = 0, to = 0, speed = 0, planTime = 0;
	int i = 0;//�м��������������µ���vector������С
	while (!carstream.eof())
	{
		one = carstream.get();//���������Ż���'#'
		if (one == '#')//�����������'#'�������һ��
			getline(carstream, infile);
		else//���򰴸�ʽ��ȡ
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
			//carsets->at(i).disp();	debug ��
			i++;
			one = carstream.get();
		}
	}
	carsets->resize(i);//����������С
	carstream.close();
}

#endif
