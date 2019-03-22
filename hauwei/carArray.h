#pragma once
#ifndef _CARARRAY_
#define _CARARRAY_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
//#include <sstream>
#include "car.h"
using namespace std;

#define contianer 20000

class carArray
{
public:
	bool iniCar(const char* fileName);//��ʼ���������ݣ�����Ϊ�ļ�·��
	bool iniCar2(const char* fileName);//��ʼ����������֮��������Ϊ�ļ�·��

	car& getCar(int i);//���ص�i����

private:
	//vector<car> carsets(contianer);//��Ҫ����һ����ʼ��ֵ�Լ��ٺ���push_back�Ĵ���������ʱ��
						   //�д�������.h �ļ��в���ֱ�ӵ���vector�������������ֵ����Ҫ������������������С
	vector<car> carsets;
	ifstream carstream;
};
bool carArray::iniCar(const char* fileName)
{
	//��ʼ����������������ļ���д����������
	carsets.resize(contianer);//��ʼ����container��������������޸Ĵ�С
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
	carsets.resize(contianer);//��ʼ����container��������������޸Ĵ�С
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
			infile = str;
			id = std::stoi(infile);

			carstream.getline(str, 10, ',');
			infile = str;
			from = std::stoi(infile);

			carstream.getline(str, 10, ',');
			infile = str;
			to = std::stoi(infile);

			carstream.getline(str, 10, ',');
			infile = str;
			speed = std::stoi(infile);

			carstream.getline(str, 10, '\n');
			infile = str;
			planTime = std::stoi(infile);


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
#endif


