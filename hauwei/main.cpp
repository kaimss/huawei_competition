#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include "adjacencyWDigraph.h"
using namespace std;
void readTxt(string file)
{//���ж���
	ifstream infile;
	infile.open(file.data());   //���ļ����������ļ��������� 
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

	string s;
	while (getline(infile, s))
	{
		cout << s << endl;
	}
	infile.close();             //�ر��ļ������� 
}
void readTxt2(string file)
{//����ַ����루���Կո���س���
	ifstream infile;
	infile.open(file.data());   //���ļ����������ļ��������� 
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

	char c;
	while (!infile.eof())
	{
		infile >> c;
		cout << c;

	}
	infile.close();             //�ر��ļ������� 
}
void readTxt3(string file)
{//����ַ����루�����ո���س���
	ifstream infile;
	infile.open(file.data());   //���ļ����������ļ��������� 
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

	char c;
	infile >> noskipws;
	while (!infile.eof())
	{
		infile >> c;
		cout << c;

	}
	infile.close();             //�ر��ļ������� 
}
int main()
{

	
	/*adjacencyWDigraph graph(64);
	graph.iniRoad("C:\\huawei\\data1\\road_process.txt");*/


	/*
	car.open("C:\\huawei\\data1\\car_process.txt", ios::in | ios::out|ios::binary);
	
	if (!car.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		exit(0);
	}
	char buffer[256];
	int i = 0;
	while (!car.eof())
	{
		car.getline(buffer, 100);
		cout << buffer << endl;
	}
	car.close();
	*/

	/*string file = "C:\\huawei\\data1\\road_process.txt";
	readTxt2(file);*/

	//edge(int theId, int theChannel, int theLength, int topSpeed)
	/*edge a(1, 2, 3, 4);
	edge b(2, 3, 4, 5);
	edge c(3, 4, 5, 6);
	if (c <= (b + a))
	{
		cout << a;
	}
		
	cout << endl;*/

	return 0;
}