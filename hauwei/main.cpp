#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdio.h>
#include <vector>
#include "adjacencyWDigraph.h"
#include "carArray.h"
using namespace std;

#define maxsecond 200//������ʱ��

void dispatch(adjacencyWDigraph&, car&);//��ʱ�ĵ��Ⱥ���

int main()
{
	adjacencyWDigraph graph(64);
	graph.iniRoad("data1//road_process.txt");
	//graph.iniRoad2("data2//road.txt");
	//graph.output();

	carArray cars;
	cars.iniCar("data1//car_process.txt");
	//cars.iniCar2("data2//car.txt");
	

	int **a, **b;
	a = new int*[65];
	b = new int*[65];
	for (int i = 0; i <= 64; i++)
	{
		a[i] = new int[65];
		b[i] = new int[65];
	}
	graph.allpairs(a,b);
	//outputPath(a, b, 1, 36);
	//cout << a[1][36];

	//����0�ų������·����������·�����к͵�·����
	outputPath(a, b, cars.getCar(0).from, cars.getCar(0).to, cars.getCar(0).path, cars.getCar(0).dot, graph);

	


	dispatch(graph, cars.getCar(0));




	cout << "hello\n";



	return 0;
}

int min(int &a, int &b)
{
	return a > b ? b : a;
}


void dispatch(adjacencyWDigraph &graph, car &acar)
{
	int second;

	for (second = 0; second <= maxsecond; second++)
	{
		//����ǰ���ж����Ƿ��ӻ���������ѡ�񳵵���
		if (second == acar.planTime)
		{//�������ʱ��

			cout << "��" << second << "�복����ʼ����\n";

			acar.second = 0;//ÿ�����ļ�ʱ��
			acar.cchannel = 1;//����ѡ��1
			acar.cfrom = acar.dot[acar.i];//Ŀǰ��cfrom·����ʻ��cto·��
			acar.cto = acar.dot[acar.i + 1];
			acar.direction = acar.cto - acar.cfrom;//Ŀǰ��ʻ����
			acar.turn = 1;//Ŀǰ��ֱ��״̬
			acar.cdistance = 0;//Ŀǰ��ʻ����Ϊ0

			//��ʻ��·ʱ���ж�����ʻ����ǰ���Ƿ��г����Ƿ����٣�
			edge &droad = graph.getEdge(acar.cfrom, acar.cto);
			//acar.cspeed = droad.maxSpeed > acar.maxSpeed ? acar.maxSpeed : droad.maxSpeed;
			acar.cspeed = min(droad.maxSpeed, acar.maxSpeed);
			droad.road[acar.cchannel][acar.cdistance] = acar.id;
		}
		else if (second > acar.planTime)
		{//��ʻ��
			acar.second++;
			edge &droad = graph.getEdge(acar.cfrom, acar.cto);
			if (acar.cdistance + acar.cspeed >= droad.length)
			{//��һ��ᵽ��·��
				if (acar.cto == acar.to)
				{//�����յ�

					//һЩ����
					cout << "��" << second << "�복�������յ�\n";

					
					
					return;
				}
				else
				{//·�ڵ���
					int S1 = droad.length - acar.cdistance;
					edge &ndroad = graph.getEdge(acar.cto, acar.dot[acar.i+2]);
					int S2 = min(acar.maxSpeed, ndroad.maxSpeed);
					if (S2 <= S1)
					{//�޷�ͨ��·��
						cout << "��" << second << "�복������·��"<<acar.dot[acar.i+1]<<"��δͨ��\n";

						droad.road[acar.cchannel][acar.cdistance] = 0;//�����һ��λ��
						acar.cdistance = droad.length;//���µ�ǰ��ʻ����
						droad.road[acar.cchannel][acar.cdistance] = acar.id;//���µ�ǰλ��
					}
					else
					{//����ͨ��·��

						cout << "��" << second << "�복������·��" << acar.dot[acar.i + 2] << "�ҵ����·" << droad.id << "\n";

						//���³�����Ϣ���·��Ϣ
						acar.i++;//����·��������
						acar.cfrom = acar.dot[acar.i];//Ŀǰ��cfrom·����ʻ��cto·��
						acar.cto = acar.dot[acar.i + 1];
						acar.direction = acar.cto - acar.cfrom;//Ŀǰ��ʻ����

						droad.road[acar.cchannel][acar.cdistance] = 0;//�������һ����·����Ϣ
						acar.cdistance = S2 - S1;//Ŀǰ��ʻ����ΪS2-S1
						acar.cspeed = min(ndroad.maxSpeed, acar.maxSpeed);//��������ٶ�
						ndroad.road[acar.cchannel][acar.cdistance] = acar.id;//��������һ����·��λ��
					}
				}
				

			}
			else
			{//��һ��δ����·��
				cout << "��" << second << "�복���ڵ�·" << droad.id << "����ʻ\n";
				//һЩ����
				droad.road[acar.cchannel][acar.cdistance] = 0;//�����һ��λ��
				acar.cdistance += acar.cspeed;//���µ�ǰ��ʻ����
				droad.road[acar.cchannel][acar.cdistance] = acar.id;//���µ�ǰλ��

			}
		    //��ʻ��·ʱ���ж�����ʻ����ǰ���Ƿ��г����Ƿ����٣�

		}
		else
		{//δ�������ʱ��

		}
		


		




		//����·��ʱ���ж���������ת����ʻ���ȼ����Ƿ�ɹ�·�ڣ���һ·�ڵĳ���ѡ��

		//����Ŀ�ĵص��ж�
		cout << acar << "\n";
	}
}