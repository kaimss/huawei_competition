#ifndef _ADJACENCYWDIGRAPH_
#define _ADJACENCYWDIGRAPH_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "edge.h"

#define UNKNOWN_PROBLEM 1

using namespace std;

class adjacencyWDigraph
{
public:
	adjacencyWDigraph(int numOfVertices = 3);
	~adjacencyWDigraph();

	//初始化道路数据，参数一为文件路径，参数二是读写长度
	bool iniRoad(const char* fileName);	
	void output();//输出矩阵的长度
	void allpairs(int **, int **);//任意两点之间的最短路径
private:
	int numVertices;
	int numEdges;
	
	edge **edgesets;

	ifstream car;	//车辆
	ifstream crossAndroad;
};

adjacencyWDigraph::adjacencyWDigraph(int numOfVertices)
{
	if (numOfVertices < 2)
		throw UNKNOWN_PROBLEM;
	//构造函数
	numVertices = numOfVertices;
	numEdges = 0;
	edge *insert = NULL;
	try {
		edgesets = new edge*[numVertices + 1];
		for (int i = 0; i <= numVertices; i++)
			edgesets[i] = new edge[numVertices + 1];
	}
	catch (bad_alloc)
	{
		cout << "错误" << endl;
		throw UNKNOWN_PROBLEM;
	}
}

adjacencyWDigraph::~adjacencyWDigraph()
{
	//析构函数
	
	for (int i = 0; i <= numVertices; i++)
		delete[] edgesets[i];

	delete[] edgesets;
	edgesets = NULL;
	
}

bool adjacencyWDigraph::iniRoad(const char* fileName)
{
	//初始化函数，将读入的文件填写到图中
	string infile;
	crossAndroad.open(fileName, ios::in | ios::out);
	if (!crossAndroad.is_open()) {
		cout << "文件打开错误" << endl;
		return false;
	}
	int id, channel, start, dest, length, maxSpeed, single;
	edge *insert;
	while (!crossAndroad.eof())
	{
		crossAndroad >> infile;
		id = std::stoi(infile);
		crossAndroad >> infile;
		length = std::stoi(infile);
		crossAndroad >> infile;
		maxSpeed = std::stoi(infile);
		crossAndroad >> infile;
		channel = std::stoi(infile);
		crossAndroad >> infile;
		start = std::stoi(infile);
		crossAndroad >> infile;
		dest = std::stoi(infile);
		crossAndroad >> infile;
		single = std::stoi(infile);

		insert = &edgesets[start][dest];
		insert->id = id;
		insert->length = length;
		insert->maxSpeed = maxSpeed;
		insert->channel = channel;

		numEdges++;
		if (single == 1)
		{
			insert = &edgesets[dest][start];
			insert->id = id;
			insert->length = length;
			insert->maxSpeed = maxSpeed;
			insert->channel = channel;
			numEdges++;
		}
	}
	crossAndroad.close();
	return true;
}
void adjacencyWDigraph::output()
{
	for (int i = 1; i <= numVertices; i++)
	{
		for (int j = 1; j <= numVertices; j++)
			cout << edgesets[i][j].length << " ";
		cout << endl;
	}
}
void adjacencyWDigraph::allpairs(int **c, int **kay)
{
	for (int i = 1; i <= numVertices; i++)
	{
		for (int j = 1; j <= numVertices; j++)
		{
			c[i][j] = edgesets[i][j].length;
			kay[i][j] = 0;
		}
	}
	for (int i = 1; i <= numVertices; i++)
	{
		c[i][i] = 0;
	}
	for (int k = 1; k <= numVertices; k++)
		for (int i = 1; i <= numVertices; i++)
			for (int j = 1; j <= numVertices; j++)
				if (c[i][k] != 1000 && c[k][j] != 1000 && (c[i][j] ==1000 || c[i][j] > c[i][k] + c[k][j]))
				{
					c[i][j] = c[i][k] + c[k][j];
					kay[i][j] = k;
				}

}
//int *adjacencyWDigraph::findPath(int theSource ,int theDestitination)
//{//寻找一条从theSource到theDestination的最短路径

//}
void outputPath(int **kay, int i, int j)
{
	if (i == j)
		return;
	if (kay[i][j] == 0)
		cout << j << " ";
	else
	{
		outputPath(kay, i, kay[i][j]);
		outputPath(kay, kay[i][j], j);
	}
}
void outputPath(int **c, int **kay, int i, int j)
{
	if (c[i][j] == 1000)
		cout << "there is  no path from " << i << "to" << j << endl;
	else
	{
		cout << "the path is" << i << " ";
		outputPath(kay, i, j);
		cout << endl;
	}
}


#endif