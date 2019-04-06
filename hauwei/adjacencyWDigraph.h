#ifndef _ADJACENCYWDIGRAPH_
#define _ADJACENCYWDIGRAPH_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "cross.h"
#include "car.h"
#include "carArray.h"
#include "edge.h"
#include "road.h"

#define UNKNOWN_PROBLEM 1

using namespace std;

class adjacencyWDigraph
{
public:
	//adjacencyWDigraph();	//增加默认的构造函数，以便使用 initRoad() 进行初始化
							//构造函数，输入四个文件名
	adjacencyWDigraph(const char* roadFilePath, const char* crossFilePath);
	//adjacencyWDigraph(int numOfVertices = 3);
	~adjacencyWDigraph();

	
	bool iniRoad(const char* fileName);	//初始化道路数据，参数为文件路径
	bool iniRoad2(const char* fileName);//初始化道路数据之二，参数为文件路径
	bool iniCross(const char* fileName);//初始化路口数据
	void output();//输出矩阵
	void allpairs(float **, int **);//任意两点之间的最短路径
	void shortestPaths(float** c, int sourceVertex, float* distanceFromSource, int* predecessor);//两点间最短路径

	edge& getEdge(int i, int j);//返回从i到j的路径
	//void floyid(char *, int **,int **);

	void dynamicselect(char* path, carArray& carsets);//通过pair中的排序更新边权重，
																						//然后再求最短路径
	void outputPathFile(char*, float **,int **,int,int,int,int,int&);//通过车的信息输出此车的路径至文件
	void outputPathFile(char*, int **, int, int, int);

	void output(char *, float **, int **, carArray &,int &);//输出所有车的路径至文件，调用了上上个函数

	int getNumber();//获取路口数量
private:
	int numVertices;	//路口数量
	int numEdges;		//道路数量
	int **carTime;		//车辆到达的时间（最短路径算法）
	ofstream out;
	edge **edgesets;	//边集

	vector<cross> *crossMap;		//路口集合
	vector<road> *roads;			//道路集合

	ofstream carstream;				//文件写入流（写入车的路径）
	ifstream crossAndroad;			//文件读取流（读取路口及道路信息）
	
	vector<int> projectCar;
	vector<int> projectRoad;
	vector<int> projectCross;

	int getCidp(int CrossId);		//通过路口id获取索引，如果没有返回-1

};
adjacencyWDigraph::adjacencyWDigraph(const char* roadFilePath, const char* crossFilePath)
{
	iniCross(crossFilePath);

	if (numVertices < 2)
		throw UNKNOWN_PROBLEM;
	//构造函数
	numEdges = 0;
	edge *insert = NULL;
	try {
		edgesets = new edge*[numVertices + 1];
		carTime = new int*[numVertices];
		for (int i = 0; i <= numVertices; i++)
		{
			edgesets[i] = new edge[numVertices + 1];
			carTime[i] = new int[3];
		}
	}
	catch (bad_alloc)
	{
		cout << "错误" << endl;
		throw UNKNOWN_PROBLEM;
	}
	iniRoad2(roadFilePath);
}
//adjacencyWDigraph::adjacencyWDigraph()
//{
//	//默认的构造函数
//	numVertices = 0;
//	numEdges = 0;
//	carTime = NULL;
//	edgesets = NULL;
//}
//
//adjacencyWDigraph::adjacencyWDigraph(int numOfVertices)
//{
//	if (numOfVertices < 2)
//		throw UNKNOWN_PROBLEM;
//	//构造函数
//	numVertices = numOfVertices;
//	numEdges = 0;
//	edge *insert = NULL;
//	try {
//		edgesets = new edge*[numVertices + 1];
//		carTime = new int*[numVertices];
//		for (int i = 0; i <= numVertices; i++)
//		{
//			edgesets[i] = new edge[numVertices + 1];
//			carTime[i] = new int[3];
//		}
//	}
//	catch (bad_alloc)
//	{
//		cout << "错误" << endl;
//		throw UNKNOWN_PROBLEM;
//	}
//}

adjacencyWDigraph::~adjacencyWDigraph()
{	//析构函数
	for (int i = 0; i <= numVertices; i++)
		delete[] edgesets[i];

	delete[] edgesets;
	edgesets = NULL;
}

bool adjacencyWDigraph::iniRoad(const char* fileName)
{	//初始化函数，将读入的文件填写到图中
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
		crossAndroad >> id >> length >> maxSpeed >> channel >> start >> dest >> single;

		//初始化边（道路）
		insert = &edgesets[start][dest];
		insert->id = id;
		insert->length = length;
		insert->maxSpeed = maxSpeed;
		insert->channel = channel;
		numEdges++;

		//初始化每条道路的二维数组
		vector<int> temp(length + 1, 0);
		for (int i = 0; i <= channel; i++)
		{
			insert->road.push_back(temp);
		}
		
		//如果是双向车道的道路
		if (single == 1)
		{
			insert = &edgesets[dest][start];
			insert->id = id;
			insert->length = length;
			insert->maxSpeed = maxSpeed;
			insert->channel = channel;
			numEdges++;

			vector<int> temp(length + 1, 0);
			for (int i = 0; i <= channel; i++)
			{
				insert->road.push_back(temp);
			}

		}
	}
	crossAndroad.close();
	return true;
}

bool adjacencyWDigraph::iniRoad2(const char* fileName)
{	//初始化函数，将读入的文件填写到图中
	string infile;
	char str[10], one;
	crossAndroad.open(fileName, ios::in | ios::out);
	if (!crossAndroad.is_open()) {
		cout << "文件打开错误" << endl;
		return false;
	}
	int id, channel, start, dest, length, maxSpeed, single;
	edge *insert;
	int index = 0;
	roads = new vector<road>();
	roads->resize(500);
	while (!crossAndroad.eof())
	{
		one = crossAndroad.get();//读掉左括号或者'#'
		if (one == '#')//如果读到的是'#'则忽略这一行
			getline(crossAndroad, infile);
		else//否则按格式读取
		{
			crossAndroad.getline(str, 10, ',');
			id = std::atoi(str);

			crossAndroad.getline(str, 10, ',');
			length = std::atoi(str);

			crossAndroad.getline(str, 10, ',');
			maxSpeed = std::atoi(str);

			crossAndroad.getline(str, 10, ',');
			channel = std::atoi(str);

			crossAndroad.getline(str, 10, ',');
			start = std::atoi(str);

			crossAndroad.getline(str, 10, ',');
			dest = std::atoi(str);

			crossAndroad.getline(str, 10, ')');
			single = std::atoi(str);

			one = crossAndroad.get();//读掉换行符
			
			//cout << id << length << maxSpeed << channel << start << dest << single << endl;

			
			insert = &edgesets[getCidp(start)][getCidp(dest)];///////根据实际出发结束点对应映射后的编号
			insert->id = id;
			insert->length = length;
			insert->maxSpeed = maxSpeed;
			insert->channel = channel;
			numEdges++;


			roads->at(index).id = id;
			roads->at(index).from = start;
			roads->at(index).to = dest;
			index++;


			vector<int> temp(length + 1, 0);
			for (int i = 0; i <= channel; i++)
			{
				insert->road.push_back(temp);
			}
			if (single == 1)
			{
				insert = &edgesets[getCidp(dest)][getCidp(start)];
				insert->id = id;
				insert->length = length;
				insert->maxSpeed = maxSpeed;
				insert->channel = channel;
				numEdges++;
				vector<int> temp(length + 1, 0);
				for (int i = 0; i <= channel; i++)
				{
					insert->road.push_back(temp);
				}
			}
			//cout << i++ << "\n";

		}
	}
	roads->resize(index);
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
bool adjacencyWDigraph::iniCross(const char* crossFilePath)
{
	crossMap = new vector<cross>();
	//初始化函数，将读入的文件填写路口
	string infile;
	char str[10], one;
	//pojectCross.resize
	crossMap->resize(200);	//初始化
	crossAndroad.open(crossFilePath, ios::in | ios::out);
	if (!crossAndroad.is_open()) {
		cout << "文件打开错误" << endl;
		//throw UNKNOWN_METHOD;
		return false;
	}
	int id, from, to, speed, planTime;
	int i = 0;//行计数器，用于重新调整vector容器大小
	while (!crossAndroad.eof())
	{
		int crossID = 0;
		one = crossAndroad.get();//读掉左括号或者'#'
		if (one == '#')//如果读到的是'#'则忽略这一行
			getline(crossAndroad, infile);
		else//否则按格式读取
		{
			crossAndroad.getline(str, 10, ',');
			crossID = std::atoi(str);
			crossMap->at(i + 1).id = crossID;

			crossAndroad.getline(str, 10, ',');
			crossMap->at(i + 1).adjaRoadID.push_back(std::atoi(str));

			crossAndroad.getline(str, 10, ',');
			crossMap->at(i + 1).adjaRoadID.push_back(std::atoi(str));

			crossAndroad.getline(str, 10, ',');
			crossMap->at(i + 1).adjaRoadID.push_back(std::atoi(str));

			crossAndroad.getline(str, 10, ')');
			crossMap->at(i + 1).adjaRoadID.push_back(std::atoi(str));

			//crossMap->at(crossID).disp();	debug ;
			one = crossAndroad.get();
			i++;
		}
	}
	cout << "all " << i << " crosses\n";
	numVertices = i;
	crossMap->resize(i + 1);//调整容器大小
	crossAndroad.close();
	return true;
}
bool adjacencyWDigraph::initPreset(const char* fileName, const char* fileName2)
{
	//初始化函数，将读入的预置车辆路径信息写入answer.txt文件
	string infile;
	char str[10], one;
	crossAndroad.open(fileName, ios::in | ios::out);
	if (!crossAndroad.is_open()) {
		cout << "文件打开错误" << endl;
		throw UNKNOWN_PROBLEM;
	}
	int id, scheduledTime;
	int sum = 0;
	int m = 0;

	while (!crossAndroad.eof())
	{
		one = crossAndroad.get();//读掉左括号或者'#'
		if (crossAndroad.eof())
			return true;
		if (one == '#')//如果读到的是'#'则忽略这一行
			getline(crossAndroad, infile);
		else//否则按格式读取
		{
			crossAndroad.getline(str, 10, ',');//读id
			id = std::atoi(str);

			crossAndroad.getline(str, 10, ',');//读scheduledTime
			scheduledTime = std::atoi(str);

			
			cout << m++ << "\t";

			while (1)
			{
				sum = 0;
				one = crossAndroad.get();
				while (one >= 48 && one <= 57)
				{
					sum = sum * 10 + (one - 48);
					one = crossAndroad.get();

				}
				//一些加权措施
				for (int i = 0; i < roads->size(); i++)
				{
					if (sum == roads->at(i).id)
					{
						edgesets[getCidp(roads->at(i).from)][getCidp(roads->at(i).to)].road[0][0]++;
						break;
					}
				}
	
				if (one == ')')
					break;
			}
			one = crossAndroad.get();//读掉换行符
			//m++;
		}
	}
	crossAndroad.close();

	//重新打开并且写入answer.txt
	crossAndroad.open(fileName, ios::in | ios::out);
	carstream.open(fileName2, ios::in | ios::out);
	while (!crossAndroad.eof())
	{
		getline(crossAndroad, infile);
		carstream << infile << "\n";
	}
	crossAndroad.close();
	carstream.close();
}
//动态寻找所有顶点对之间的最短路径
void adjacencyWDigraph::allpairs(float **c, int **kay)
{	//初始化c[i][j]
	for (int i = 1; i <= numVertices; i++)
	{
		for (int j = 1; j <= numVertices; j++)
		{
			c[i][j] = edgesets[i][j].depend();
			kay[i][j] = 0;
		}
	}
	for (int i = 1; i <= numVertices; i++)
	{
		c[i][i] = 0;
	}
	//计算c[o][j]=c(i,j,k)，即从i到j的路径长度等于从i到j经过k的路径长度
	for (int k = 1; k <= numVertices; k++)
		for (int i = 1; i <= numVertices; i++)
			for (int j = 1; j <= numVertices; j++)
			//找到c[i][j]的较小值
				if (c[i][k] != INF && c[k][j] != INF && (c[i][j] == INF || c[i][j] > c[i][k] + c[k][j]))
				{
					c[i][j] = c[i][k] + c[k][j];
					kay[i][j] = k;
				}
}

//暂时的动态调度
void adjacencyWDigraph::dynamicselect(char* path, carArray& carsets)
{
	float **c = new float*[numVertices +1];
	for (int i = 0; i <= numVertices; i++)	
	{
		c[i] = new float[numVertices + 1];
	}
	//初始化c[i][j]
	for (int i = 1; i <= numVertices; i++)
	{
		for (int j = 1; j <= numVertices; j++)
		{
			c[i][j] = edgesets[i][j].depend();
			if (edgesets[i][j].length != INF)
			{
				c[i][j] += edgesets[i][j].road[0][0];
			}
			
			//cout << edgesets[i][j].length << endl;
		}
	}

	float* distanceFromSource = new float[numVertices + 1];
	int* predecessor = new int[numVertices + 1];

	int id = 0;
	
	int pre = 0;
	int source, destination;
	//carstream.open(path, ios::out);
	//carstream.close();
	carstream.open(path, ios::app);
	//car tempcar;
	for (int m = carsets.getNumber() - 1; m >= 0; m--)
	{
		
		car &acar = carsets.getCar(m);//
		
		source = acar.from;
		destination = acar.to;

		//按照一定规则调整边权
		for (int i = 1; i <= numVertices; i++)
		{
			
			for (int j = 1; j <= numVertices; j++)
			{
				if (edgesets[i][j].maxSpeed != 0)
				{
					//添加车辆限速对路径的影响
					if (edgesets[i][j].maxSpeed < acar.maxSpeed)
						c[i][j] += (float)(acar.maxSpeed - edgesets[i][j].maxSpeed) / (float)(acar.maxSpeed);
					if (edgesets[i][j].maxSpeed != 0)
						c[i][j] += (edgesets[i][j].road[0][0]) / (edgesets[i][j].length * edgesets[i][j].channel);
				}
			}
		}

		//cout << "acar"<<acar.from << "\t";
		shortestPaths(c, acar.from, distanceFromSource, predecessor);//通过c就算两点间最短距离

		//恢复边权												
		for (int i = 1; i <= numVertices; i++)
		{
			for (int j = 1; j <= numVertices ; j++)
			{
				if (edgesets[i][j].maxSpeed < acar.maxSpeed)
					c[i][j] -= (float)(acar.maxSpeed - edgesets[i][j].maxSpeed) / (float)(acar.maxSpeed);
				if(edgesets[i][j].maxSpeed != 0)
					c[i][j] -= (edgesets[i][j].road[0][0]) / (edgesets[i][j].length * edgesets[i][j].channel);
			}
		}


		//if (distanceFromSource[destination] + 1 > INF)
		//{
		//	cout << "noreachable\n";
		//	throw UNKNOWN_PROBLEM;
		//	exit(1);
		//}

		//通过前驱数组计算点序列
		pre = getCidp(destination);
		while (pre != 0)
		{
			acar.dot.insert(acar.dot.begin(), pre);
			pre = predecessor[pre];
		}
		
		acar.path.clear();
		acar.path.resize(acar.dot.size() - 1);

		//通过点序列获得边序列
		for (int i = 0; i < acar.dot.size() - 1; i++)
		{
			
			acar.path[i] = edgesets[acar.dot[i]][acar.dot[i + 1]].id;

			//更新c[i][j]
			edge &tempedge = edgesets[acar.dot[i]][acar.dot[i + 1]];
			(tempedge.road[0][0])++;
			c[acar.dot[i]][acar.dot[i + 1]] += 0.1;

		}
		if (m > 8000 || m < 3000)
			carstream << "(" << acar.id << "," << acar.planTime + acar.id % 260 << ",";
		else if (m % 10 != 0)
			carstream << "(" << acar.id << "," << acar.planTime + acar.id % 280 << ",";
		else
			carstream << "(" << acar.id << "," << acar.planTime << ",";
		for (int j = 0; j < acar.path.size() - 1; j++)
		{
			carstream << acar.path[j] << ",";
		}
		carstream << acar.path[acar.path.size() - 1] << ")\n";
		//cout << xx++ << "\n";
	}

	delete [] distanceFromSource;
	delete [] predecessor;

	//carstream.open(path, ios::out);
	//carstream.close();
	//carstream.open(path, ios::app);
	//car tempcar;
	//int tempsize = 0;

	//for (int i = 0; i < carsets.getNumber(); i++)
	//{
	//	tempcar = carsets.getCar(i);
	//	tempsize = tempcar.path.size();
	//	if (tempsize < 2)
	//	{
	//		continue;
	//	}

	//	carstream << "(" << carsets.getCar(i).id << "," << carsets.getCar(i).planTime << ",";
	//	for (int j = 0; j < tempsize - 1; j++)
	//	{
	//		carstream << tempcar.path[j] << ",";
	//	}
	//	carstream << tempcar.path[tempsize - 1] << ")\n";

	//}
}

//
void adjacencyWDigraph::shortestPaths(float** c, int sourceVertex, float* distanceFromSource, int* predecessor)
{//寻找一条从sourceVertex到其他点的最短路径
 //在数组distanceFromSource中返回最短路径
 //在数组prdecessor中返回顶点在路径上的前驱的information
	vector<int> newReachableVertices;
	for (int i = 1; i <= numVertices; i++)
	{
		distanceFromSource[i] = c[getCidp(sourceVertex)][i];
		if (distanceFromSource[i] + 1 > INF)
			predecessor[i] = -1;
		else
		{
			predecessor[i] = getCidp(sourceVertex);
			newReachableVertices.insert(newReachableVertices.begin(), i);
		}
	}
	distanceFromSource[getCidp(sourceVertex)] = 0;
	predecessor[getCidp(sourceVertex)] = 0;  // source vertex has no predecessor

									// update distanceFromSource and predecessor
	while (!newReachableVertices.empty())
	{// more paths exist
	 // find unreached vertex v with least distanceFromSource
		vector<int>::iterator iNewReachableVertices
			= newReachableVertices.begin();
		vector<int>::iterator theEnd = newReachableVertices.end();
		int v = *iNewReachableVertices;
		iNewReachableVertices++;
		while (iNewReachableVertices != theEnd)
		{
			int w = *iNewReachableVertices;
			iNewReachableVertices++;
			if (distanceFromSource[w] < distanceFromSource[v])
				v = w;
		}

		// next shortest path is to vertex v, delete v from
		// newReachableVertices and update distanceFromSource
		for (int i = 0; i <= newReachableVertices.size(); i++)
		{
			if (newReachableVertices[i] == v)
			{
				newReachableVertices.erase(newReachableVertices.begin() + i);
				break;
			}
		}

		for (int j = 1; j <= numVertices; j++)
		{
			if (edgesets[v][j] != INF && (predecessor[j] == -1 ||
				distanceFromSource[j] > distanceFromSource[v] + c[v][j]))
			{
				// distanceFromSource[j] decreases
				distanceFromSource[j] = distanceFromSource[v] + c[v][j];
				// add j to newReachableVertices
				if (predecessor[j] == -1)
					// not reached before
					newReachableVertices.insert(newReachableVertices.begin(), j);
				predecessor[j] = v;
			}
		}
	}
}

//获取从i到j的边，如果不存在则返回负边
edge& adjacencyWDigraph::getEdge(int i, int j)
{
	if (edgesets[i][j].length != INF)
	{
		return edgesets[i][j];
	}
	else
	{
		edge temp(-1, -1, -1, -1);
		cout << "There is no edge from " << i << " to " << j << " through function adjacencyWDigraph::getEdge!\n";
		return temp;
	}
}


//
void adjacencyWDigraph::outputPathFile(char *path, int **kay, int i, int j,int k)
{
	if (i == j)
		return;
	if (out)
	{
		if (kay[i][j] == 0)
		{
			if (j == k)
				out << edgesets[i][j].id << ")";
			else
				out << edgesets[i][j].id << ",";
		}
		else
		{
			outputPathFile(path, kay, i, kay[i][j],k);
			outputPathFile(path, kay, kay[i][j], j,k);
		}
		//out.close();
	}
}
//
void adjacencyWDigraph::outputPathFile(char* path, float **c, int **kay, int k,int h,int i, int j,int &count)

{
	//参数分别为路径名称，最短路径数组，前驱数组，车辆id，车辆出发时间，车辆起始路口和目的路口
	if (out)
	{
		if (c[i][j] + 1 > INF)
			out << "there is  no path from " << i << "to" << j << endl;
		else
		{
			out <<"("<<k<<","<< h<<",";
			//carTime[k - 10000][0] = k;
			//carTime[k - 10000][1] = h;
			outputPathFile(path, kay, i, j,j);
			out << "\n";
		}
		count++;
	}
}


//
void adjacencyWDigraph::output(char* path, float **c, int **kay, carArray &cars,int &count)
{
	out.open(path, ios::out);
	out.close();
	out.open(path, ios::app);
	for (int i = 0; i < cars.getNumber(); i++)
	//for (int i = cars.getNumber()-1; i >=0; i--)
		if (out)
			outputPathFile(path, c, kay, cars.getCar(i).id, cars.getCar(i).planTime, cars.getCar(i).from, cars.getCar(i).to,count);
	out.close();
}

/*void adjacencyWDigraph::floyid(char* path, int **a,int **b)
{
	 out.open(path,ios::app);
	if (out)
	{
		//out << "This is a line.\n";
		//out << "This is another line.\n";
		for (int i = 1; i <= numVertices; i++)
		{
			for (int j = 1; j <= numVertices; j++)
			{
				outputPathFile(path, a, b, i, i, i, j);
				//out << a[i][j]<<" ";
			}
			out << "\n";
		}
		out.close();
		//cout << "保存成功";
    }
}*/

//输出路径的实际代码
void outputPath(int **kay, int i, int j)
{
	if (i == j)
		return;
	if (kay[i][j] == 0)//路径上没有中间顶点
		cout << j << " ";
	else
	{//kay[i][j]是路径上的一个中间顶点
		outputPath(kay, i, kay[i][j]);
		outputPath(kay, kay[i][j], j);
	}
}
//输出从i到j的最短路径至终端，输出的是顶点序列
void outputPath(int **c, int **kay, int i, int j)
{
	if (c[i][j] == INF)
		cout << "there is no path from " << i << "to" << j << endl;
	else
	{
		cout << "the path is" << i << " ";
		outputPath(kay, i, j);
		cout << endl;
	}
}

//实际输出路径至path中，path中将存储边的序列
void outputPath(int **kay, int i, int j, vector<int> &path, vector<int> &dot, adjacencyWDigraph &object)
{
	if (i == j)
		return;
	if (kay[i][j] == 0)//路径上没有中间顶点
	{
		dot.push_back(j);
		path.push_back(object.getEdge(i, j).id);
		//cout << j << " ";

	}
	else
	{//kay[i][j]是路径上的一个中间顶点
		outputPath(kay, i, kay[i][j], path, dot, object);
		outputPath(kay, kay[i][j], j, path, dot, object);
	}
}
//输出路径至car结构体的path中，path中将存储边的序列
//可以减少参数，通过结构体car
void outputPath(float **c, int **kay, int i, int j, vector<int> &path, vector<int> &dot, adjacencyWDigraph &object)
{
	if (c[i][j] == INF)
		cout << "there is no path from " << i << "to" << j << endl;
	else
	{
		//cout << "the path is" << i << " ";
		dot.push_back(i);
		outputPath(kay, i, j, path, dot, object);
		//cout << endl;
	}
}

int adjacencyWDigraph::getNumber()
{
	return numVertices;
}
int adjacencyWDigraph::getCidp(int CrossId)
{
	for (int i = 1; i <= numVertices; i++)
	{
		if (crossMap->at(i).id == CrossId)
		{
			return i;
		}
	}
	return -1;
}

#endif