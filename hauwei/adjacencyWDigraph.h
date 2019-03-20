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


#endif