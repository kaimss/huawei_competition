#include "map.h"
#include "dependencies.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 5)
	{
		cout << "usage: ./CodeCraft-2019 ../config/car.txt ../config/road.txt ../config/cross.txt ../config/answer.txt" << endl;
		exit(0);
	}

	string car_path(argv[1]);		//���복���ļ�·��
	string roads_path(argv[2]);		//�����·�ļ�·��
	string crosses_path(argv[3]);	//����·���ļ�·��
	string answer_path(argv[4]);	//���ɽ���ļ�·��

	cout << "car file path: " << argv[1] << endl;
	cout << "road file path: " << argv[2] << endl;
	cout << "cross file path: " << argv[3] << endl;
	cout << "result file path: " << argv[4] << endl;

	map *theMap = new map(argv[2], argv[3], argv[1], argv[4]);
	theMap->iniRoad(argv[2]);

	return 0;
}
