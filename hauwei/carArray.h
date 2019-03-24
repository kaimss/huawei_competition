#pragma once
#ifndef _CARARRAY_
#define _CARARRAY_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include "car.h"
using namespace std;

const int CONTAINER = 20000;

class carArray
{
public:
	bool iniCar(const char* fileName);//��ʼ���������ݣ�����Ϊ�ļ�·��
	bool iniCar2(const char* fileName);//��ʼ����������֮��������Ϊ�ļ�·��

	car& getCar(int i);//���ص�i����
	int getNumber();//���س�����Ŀ

private:
	//vector<car> carsets(contianer);//��Ҫ����һ����ʼ��ֵ�Լ��ٺ���push_back�Ĵ���������ʱ��
						   //�д�������.h �ļ��в���ֱ�ӵ���vector�������������ֵ����Ҫ������������������С
	vector<car> carsets;//��������
	ifstream carstream;//��ȡcar.txt�ļ���
};
bool carArray::iniCar(const char* fileName)
{
	//��ʼ����������������ļ���д����������
	carsets.resize(CONTAINER);//��ʼ����container��������������޸Ĵ�С
	carstream.open(fileName, ios::in | ios::out);
	if (!carstream.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		return false;
	}
	int id, from, to, speed, planTime;
	int i = 0;
	car tempcar;
	while (!carstream.eof())
	{
		carstream >> id >> from >> to >> speed >> planTime;

		//��ֵ
		carsets[i].id = id;//id��0��ʼ
		carsets[i].from = from;
		carsets[i].to = to;
		carsets[i].maxSpeed = speed;
		carsets[i].planTime = planTime;

		i++;
	}
	carsets.resize(i);//����������С
	carstream.close();
	return true;
}
bool carArray::iniCar2(const char* fileName)
{
	//��ʼ����������������ļ���д����������
	string infile;
	char str[10], one;
	carsets.resize(CONTAINER);//��ʼ����container��������������޸Ĵ�С
	carstream.open(fileName, ios::in | ios::out);
	if (!carstream.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		return false;
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
			id = std::atoi(str);

			carstream.getline(str, 10, ',');
			from = std::atoi(str);

			carstream.getline(str, 10, ',');
			to = std::atoi(str);

			carstream.getline(str, 10, ',');
			speed = std::atoi(str);

			carstream.getline(str, 10, ')');
			planTime = std::atoi(str);

			one = carstream.get();//�������з�

			//��ֵ
			carsets[i].id = id;//id��0��ʼ
			carsets[i].from = from;
			carsets[i].to = to;
			carsets[i].maxSpeed = speed;
			carsets[i].planTime = planTime;

			i++;
		}
	}
	carsets.resize(i);//����������С
	carstream.close();
	return true;
}

car& carArray::getCar(int i)
{
	return carsets[i];
}
int carArray::getNumber()
{
	return carsets.size();
}
#endif
void binSort(vector<pair<int,int>>& carTime,int range)
{
	int numberOfElements = carTime.size();
	vector<pair<int, int>>* car = new vector<pair<int, int>>[range]();

	for (int i = 0; i < numberOfElements; i++)
	{
		//car[i](1);
		pair<int, int> temp = carTime.back();
		carTime.pop_back();
		car[temp.second].push_back(temp);
	}
	for (int j = range-1; j >= 0; j--)
	{
		while (!car[j].empty()) 
		{
			pair<int, int> temp = car[j].front();
			vector<pair<int,int>>::iterator k = car[j].begin();
			car[j].erase(k);
			carTime.push_back(temp);
         }
	}
	delete []car;
}


