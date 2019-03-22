#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include<cstdio
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


	adjacencyWDigraph graph(64);
	graph.iniRoad("data1//road_process.txt");
  
	//graph.output();

	int **a, **b;
	a = new int*[65];
	b = new int*[65];
	for (int i = 0; i <= 64; i++)
		{
			a[i] = new int[65];
			b[i] = new int[65];
		}
	int car[10240][5];
	int count = 0;
	//for (int);
	string buffer;
	ifstream in;
	in.open("data1/car_process.txt",ios::in|ios::out);
	if (!in.is_open())
	{
		cout << "Error opening file"; 
		exit(1);
	}
	while (!in.eof())
	{
		in>>buffer;
		 car[count][0]= std::stoi(buffer);
		 in >> buffer;
		 car[count][1] = std::stoi(buffer);
		 in >> buffer;
		 car[count][2] = std::stoi(buffer);
		 in >> buffer;
		 car[count][3] = std::stoi(buffer);
		 in >> buffer;
		 car[count][4] = std::stoi(buffer);
		 count++;
		//cout << buffer << endl;
	}
	/*for (int i = 0; i < 10240; i++)
	{
		for (int j = 0; j < 10240; j++)
			cout << car[i][j] << " ";
		cout << "\n";
	}*/
    graph.allpairs(a,b); 
	for (int i = 0; i < 10240; i++)
		graph.outputPathFile(a,b,car[i][0],car[i][4],car[i][1],car[i][2]);
	
	//outputPath(a, b, 39, 18);
	//cout << a[39][18];
	//graph.floyid(a,b);
	 system("Pause");
	return 0;
}