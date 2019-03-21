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

	//��ʼ����·���ݣ�����һΪ�ļ�·�����������Ƕ�д����
	bool iniRoad(const char* fileName);	
	void output();//�������ĳ���
	void allpairs(int **, int **);//��������֮������·��
private:
	int numVertices;
	int numEdges;
	
	edge **edgesets;

	ifstream car;	//����
	ifstream crossAndroad;
};

adjacencyWDigraph::adjacencyWDigraph(int numOfVertices)
{
	if (numOfVertices < 2)
		throw UNKNOWN_PROBLEM;
	//���캯��
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
		cout << "����" << endl;
		throw UNKNOWN_PROBLEM;
	}
}

adjacencyWDigraph::~adjacencyWDigraph()
{
	//��������
	
	for (int i = 0; i <= numVertices; i++)
		delete[] edgesets[i];

	delete[] edgesets;
	edgesets = NULL;
	
}

bool adjacencyWDigraph::iniRoad(const char* fileName)
{
	//��ʼ����������������ļ���д��ͼ��
	string infile;
	crossAndroad.open(fileName, ios::in | ios::out);
	if (!crossAndroad.is_open()) {
		cout << "�ļ��򿪴���" << endl;
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
//{//Ѱ��һ����theSource��theDestination�����·��

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