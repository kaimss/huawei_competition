#ifndef _ADJACENCYWDIGRAPH_
#define _ADJACENCYWDIGRAPH_

#include <iostream>

#include "edge.h"

#define UNKNOWN_PROBLEM 1

using namespace std;

class adjacencyWDigraph
{
public:
	adjacencyWDigraph(int numOfVertices = 3);
	~adjacencyWDigraph();
private:
	int numVertices;
	int numEdges;
	edge **edgesets;
};

adjacencyWDigraph::adjacencyWDigraph(int numOfVertices)
{
	//���캯��
	numVertices = numOfVertices;
	numEdges = 0;
	try {
		edgesets = new edge*[numVertices + 1];
		for (int i = 0; i <= numVertices; i++)
		{
			edgesets[i] = new edge[numVertices];
		}
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




#endif