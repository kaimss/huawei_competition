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

	
	bool iniRoad(const char* fileName);	//��ʼ����·���ݣ�����Ϊ�ļ�·��
	bool iniRoad2(const char* fileName);//��ʼ����·����֮��������Ϊ�ļ�·��
	void output();//�������
	void allpairs(int **, int **);//��������֮������·��

	edge& getEdge(int i, int j);//���ش�i��j��·��
private:
	int numVertices;
	int numEdges;
	
	edge **edgesets;

	ifstream car;	
	ifstream crossAndroad;//�ļ���ȡ��
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
		crossAndroad >> id >> length >> maxSpeed >> channel >> start >> dest >> single;

		//��ʼ���ߣ���·��
		insert = &edgesets[start][dest];
		insert->id = id;
		insert->length = length;
		insert->maxSpeed = maxSpeed;
		insert->channel = channel;
		numEdges++;

		//��ʼ��ÿ����·�Ķ�ά����
		vector<int> temp(length + 1, 0);
		for (int i = 0; i <= channel; i++)
		{
			insert->road.push_back(temp);
		}
		

		//�����˫�򳵵��ĵ�·
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
bool adjacencyWDigraph::iniRoad2(const char* fileName)
{
	//��ʼ����������������ļ���д��ͼ��
	string infile;
	char str[10], one;
	crossAndroad.open(fileName, ios::in | ios::out);
	if (!crossAndroad.is_open()) {
		cout << "�ļ��򿪴���" << endl;
		return false;
	}
	int id, channel, start, dest, length, maxSpeed, single;
	edge *insert;
	while (!crossAndroad.eof())
	{
		one = crossAndroad.get();//���������Ż���'#'
		if (one == '#')//�����������'#'�������һ��
			getline(crossAndroad, infile);
		else//���򰴸�ʽ��ȡ
		{
			crossAndroad.getline(str, 10, ',');
			infile = str;
			id = std::stoi(infile);

			crossAndroad.getline(str, 10, ',');
			infile = str;
			length = std::stoi(infile);

			crossAndroad.getline(str, 10, ',');
			infile = str;
			maxSpeed = std::stoi(infile);

			crossAndroad.getline(str, 10, ',');
			infile = str;
			channel = std::stoi(infile);

			crossAndroad.getline(str, 10, ',');
			infile = str;
			start = std::stoi(infile);

			crossAndroad.getline(str, 10, ',');
			infile = str;
			dest = std::stoi(infile);

			crossAndroad.getline(str, 10, ')');
			infile = str;
			single = std::stoi(infile);

			one = crossAndroad.get();//�������з�
			
			//cout << id << length << maxSpeed << channel << start << dest << single << endl;

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

//��̬Ѱ�����ж����֮������·��
void adjacencyWDigraph::allpairs(int **c, int **kay)
{

	//��ʼ��c[i][j]
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
	//����c[o][j]=c(i,j,k)������i��j��·�����ȵ��ڴ�i��j����k��·������
	for (int k = 1; k <= numVertices; k++)
		for (int i = 1; i <= numVertices; i++)
			for (int j = 1; j <= numVertices; j++)
				if (c[i][k] != INF && c[k][j] != INF && (c[i][j] == INF || c[i][j] > c[i][k] + c[k][j]))
				{//�ҵ�c[i][j]�Ľ�Сֵ
					c[i][j] = c[i][k] + c[k][j];
					kay[i][j] = k;
				}

}
//int *adjacencyWDigraph::findPath(int theSource ,int theDestitination)
//{//Ѱ��һ����theSource��theDestination�����·��

//}

//��ȡ��i��j�ıߣ�����������򷵻ظ���
edge& adjacencyWDigraph::getEdge(int i, int j)
{
	if (edgesets[i][j].length != INF)
	{
		return edgesets[i][j];
	}
	else
	{
		edge temp(-1, -1, -1, -1);
		cout << "There is not edge from " << i << " to " << j << " through function adjacencyWDigraph::getEdge!\n";
		return temp;
	}
}



//���·����ʵ�ʴ���
void outputPath(int **kay, int i, int j)
{
	if (i == j)
		return;
	if (kay[i][j] == 0)//·����û���м䶥��
		cout << j << " ";
	else
	{//kay[i][j]��·���ϵ�һ���м䶥��
		outputPath(kay, i, kay[i][j]);
		outputPath(kay, kay[i][j], j);
	}
}
//�����i��j�����·����������Ƕ�������
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
//ʵ�����·����path�У�path�н��洢�ߵ�����
void outputPath(int **kay, int i, int j, vector<int> &path, vector<int> &dot, adjacencyWDigraph &object)
{
	if (i == j)
		return;
	if (kay[i][j] == 0)//·����û���м䶥��
	{
		dot.push_back(j);
		path.push_back(object.getEdge(i, j).id);
		cout << j << " ";

	}
	else
	{//kay[i][j]��·���ϵ�һ���м䶥��
		outputPath(kay, i, kay[i][j], path, dot, object);
		outputPath(kay, kay[i][j], j, path, dot, object);
	}
}
//���·����path�У�path�н��洢�ߵ�����
//���Լ��ٲ�����ͨ���ṹ��car
void outputPath(int **c, int **kay, int i, int j, vector<int> &path, vector<int> &dot, adjacencyWDigraph &object)
{
	if (c[i][j] == 1000)
		cout << "there is  no path from " << i << "to" << j << endl;
	else
	{
		cout << "the path is" << i << " ";
		dot.push_back(i);
		outputPath(kay, i, j, path, dot, object);
		cout << endl;
	}
}

#endif