#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include "adjacencyWDigraph.h"
using namespace std;
void readTxt(string file)
{//逐行读入
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

	string s;
	while (getline(infile, s))
	{
		cout << s << endl;
	}
	infile.close();             //关闭文件输入流 
}
void readTxt2(string file)
{//逐个字符读入（忽略空格与回车）
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

	char c;
	while (!infile.eof())
	{
		infile >> c;
		cout << c;

	}
	infile.close();             //关闭文件输入流 
}
void readTxt3(string file)
{//逐个字符读入（包括空格与回车）
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

	char c;
	infile >> noskipws;
	while (!infile.eof())
	{
		infile >> c;
		cout << c;

	}
	infile.close();             //关闭文件输入流 
}
int main()
{

	
	/*adjacencyWDigraph graph(64);
	graph.iniRoad("C:\\huawei\\data1\\road_process.txt");*/


	/*
	car.open("C:\\huawei\\data1\\car_process.txt", ios::in | ios::out|ios::binary);
	
	if (!car.is_open()) {
		cout << "文件打开错误" << endl;
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