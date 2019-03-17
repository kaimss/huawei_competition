#include <iostream>
#include <fstream>

#include "adjacencyWDigraph.h"

using namespace std;

int main()
{
	//文件读取测试
	ifstream car;
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
	return 0;
}