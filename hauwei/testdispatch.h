#pragma once
#ifndef _TESTDISPATCH_
#define _TESTDISPATCH_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <string>
#include "adjacencyWDigraph.h"
#include "carArray.h"
using namespace std;

#define maxsecond 200//������ʱ��
int min(int &a, int &b)
{
	return a > b ? b : a;
}

//����ת��
int qualifyturn(int a, int b)
{
	int x = b - a;
	if (x == 0)
	{//ֱ��
		return 1;
	}
	else if (x == 7)
	{
		if (a == 1)
		{//��ת
			return 3;
		}
		else if (a == -8)
		{//��ת
			return 2;
		}
	}
	else if (x == -7)
	{
		if (a == 8)
			return 2;
		else if (a == -1)
			return 3;
	}
	else if (x == 9)
	{
		if (a == -8)
			return 3;
		else if (a == -1)
			return 2;
	}
	else if (x == -9)
	{
		if (a == 1)
			return 2;
		else if (a == 8)
			return 3;
	}


}
//������ת��תΪ����ת��
string itd(int turn)
{
	if (turn == 1)
		return "ֱ��";
	else if (turn == 2)
		return "��ת";
	else if (turn == 3)
		return "��ת";

}

//������
void dispatch(adjacencyWDigraph &graph, car &acar)
{
	int second;

	for (second = 0; second <= maxsecond; second++)
	{
		
		if (second == acar.planTime)
		{//�������ʱ��

			//cout << "��" << second << "�복����ʼ����\n";

			acar.second = 0;//ÿ�����ļ�ʱ��
			acar.cchannel = 1;//����ѡ��1
			acar.cfrom = acar.dot[acar.i];//Ŀǰ��cfrom·����ʻ��cto·��
			acar.cto = acar.dot[acar.i + 1];
			acar.direction = acar.cto - acar.cfrom;//Ŀǰ��ʻ����
			acar.turn = 1;//Ŀǰ��ֱ��״̬
			acar.cdistance = 0;//Ŀǰ��ʻ����Ϊ0
			

			
			edge &droad = graph.getEdge(acar.cfrom, acar.cto);//��ȡ��ǰ��Ҫ��ʻ�ĵ�·
			acar.croad = droad.id;//Ŀǰ��ʻ��·���
			acar.cspeed = min(droad.maxSpeed, acar.maxSpeed);//��õ�ǰ�ٶ�
			droad.road[acar.cchannel][acar.cdistance] = acar.id;//���˳�����ڵ�·��
		}
		else if (second > acar.planTime)
		{//��ʻ��
			acar.second++;
			edge &droad = graph.getEdge(acar.cfrom, acar.cto);
			if (acar.cdistance + acar.cspeed >= droad.length)
			{//��һ��ᵽ��·��
				if (acar.cto == acar.to)
				{//�����յ�
					acar.cdistance = droad.length;
					//cout << "��" << second << "�복�������յ�\n";
					//cout << acar;
					return;
				}
				else
				{//·�ڵ���
					int S1 = droad.length - acar.cdistance;
					edge &ndroad = graph.getEdge(acar.cto, acar.dot[acar.i + 2]);
					int S2 = min(acar.maxSpeed, ndroad.maxSpeed);
				
					if (S2 <= S1)
					{//�޷�ͨ��·��
						//cout << "��" << second << "�복������·��" << acar.dot[acar.i + 1] << "��δͨ��\n";

						droad.road[acar.cchannel][acar.cdistance] = 0;//�����һ��λ��
						acar.cdistance = droad.length;//���µ�ǰ��ʻ����
						droad.road[acar.cchannel][acar.cdistance] = acar.id;//���µ�ǰλ��
					}
					else
					{//����ͨ��·��




					   //���³�����Ϣ���·��Ϣ
						acar.i++;//����·��������
						acar.cfrom = acar.dot[acar.i];//������ʻ·�����У�Ŀǰ��cfrom·����ʻ��cto·��
						acar.cto = acar.dot[acar.i + 1];
						acar.turn = qualifyturn(acar.direction, acar.cto - acar.cfrom);//ȷ��ת��
						acar.direction = acar.cto - acar.cfrom;//������ʻ����
						acar.croad = ndroad.id;//������ʻ��·���

						//cout << "��" << second << "�복��" << itd(acar.turn) << "����·��" << acar.dot[acar.i] << "�ҵ����·" << ndroad.id << "\n";

						droad.road[acar.cchannel][acar.cdistance] = 0;//�������һ����·����Ϣ
						acar.cdistance = S2 - S1;//Ŀǰ��ʻ����ΪS2-S1
						acar.cspeed = min(ndroad.maxSpeed, acar.maxSpeed);//��������ٶ�
						ndroad.road[acar.cchannel][acar.cdistance] = acar.id;//��������һ����·��λ��
					}
				}


			}
			else
			{//��һ��δ����·��
				//cout << "��" << second << "�복���ڵ�·" << droad.id << "����ʻ\n";
				droad.road[acar.cchannel][acar.cdistance] = 0;//�����һ��λ��
				acar.cdistance += acar.cspeed;//���µ�ǰ��ʻ����
				droad.road[acar.cchannel][acar.cdistance] = acar.id;//���µ�ǰλ��

			}

			
			//cout << acar << "\n";

		}
		else
		{//δ�������ʱ��

		}




		//����ǰ���ж����Ƿ��ӻ���������ѡ�񳵵���

		//��ʻ��·ʱ���ж�����ʻ����ǰ���Ƿ��г����Ƿ����٣�

		//����·��ʱ���ж���������ת����ʻ���ȼ����Ƿ�ɹ�·�ڣ���һ·�ڵĳ���ѡ��

		//����Ŀ�ĵص��ж�
		
	}
}
#endif
