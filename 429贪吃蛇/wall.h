
#pragma once 
#include <iostream>

using namespace std;

class Wall
{
public:
	//��Ϸ����Ŀ��
	enum {ROW= 26 , COL= 26};

	//��ʼ��״̬
	void initWall();

	//������Ϸ״̬
	void setWall(int x, int y, char c);

	//��ȡ��Ϸ��״̬
	char getWall(int x, int y);

	//��ʾ����
	void shouWall();

	//����  ������Ϸ״̬
	char wallArray[ROW][COL];
};