
#pragma once
#include <list>
#include <Windows.h>
#include "wall.h"
#include "food.h"
class Snake
{
public:
	//��ʼ�� ��״̬
	Snake(Wall & tmpWall,Food &tmpFood);

	enum { UP = 'w', LEFT = 'a', DOWN = 's', RIGHT = 'd' };

	//����������
	struct pos
	{
		int x;
		int y;
	};
	//������һ�κϷ��� ��������
	char preKey;

	//�ж� ���������Ƿ�Ϸ� 
	bool isGood(char &key);

	//�ƶ�  ����������
	bool moveSnake(char key);

	//���� ��ʾ�÷�  �͵ȼ�
	void showScore();

	//�����ٶ�
	double getSpeed();
private:
	//������
	list<pos> Point;
	
	//ɾ���ڵ�	β������
	void deleSnake();

	//��� �½ڵ�   ͷ�����
	void addSnake(int x, int y);
	
	//ǽ�Ķ���
	Wall &wall;

	//ʳ�����
	Food &food;
};