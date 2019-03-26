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
		car theCar(id, 0, 0, 0, 0);
		vector<car>::iterator search = find(carsets->begin(), carsets->end(), theCar);
		if (search != carsets->begin())
			return carsets->at(search - carsets->begin());
	}
private:
	vector<car> *carsets;
	ifstream carstream;
};

carList::carList(const char* filePath)
{
	carsets = new vector<car>();
	//��ʼ����������������ļ���д����������
	string infile;
	char str[10], one;
	carsets->resize(100);//��ʼ����container��������������޸Ĵ�С
	carstream.open(filePath, ios::in | ios::out);
	if (!carstream.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		throw UNKNOWN_METHOD;
	}
	int id, from, to, speed, planTime;
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

			carstream.getline(str, 10, ',');
			carsets->at(i).deparID = std::atoi(str);

			carstream.getline(str, 10, ',');
			carsets->at(i).destID = std::atoi(str);

			carstream.getline(str, 10, ',');
			carsets->at(i) .maxCarSpeed= std::atoi(str);

			carstream.getline(str, 10, ')');
			carsets->at(i).planTime = std::atoi(str);
			i++;
			}
		}
	carsets->resize(i);//����������С
	carstream.close();
}

#endif
