#include "map.h"
#include "dependencies.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 5)
	{
		cout << "usage: ./CodeCraft-2019 ../config/car.txt ";
		cout << "../config/road.txt ../config/cross.txt ";
		cout << "../config/answer.txt" << endl;
		exit(0);
	}

	string car_path(argv[1]);		//读入车辆文件路径
	string roads_path(argv[2]);		//读入道路文件路径
	string crosses_path(argv[3]);	//读入路口文件路径
	string answer_path(argv[4]);	//生成结果文件路径

	cout << "car file path: " << argv[1] << endl;
	cout << "road file path: " << argv[2] << endl;
	cout << "cross file path: " << argv[3] << endl;
	cout << "result file path: " << argv[4] << endl;

	theMap *thetheMap = new theMap(argv[2], argv[3], argv[1], argv[4]);
	//thetheMap->PriorityQueue();
	//thetheMap->sortCars(100);

	int totalTimes = 0;
	int finishingTime = 0;
	bool deadLock = thetheMap->simulate(totalTimes, finishingTime);

	return 0;
}
