
#pragma once
#include "wall.h"
#include <Windows.h>
class Food
{
public:

	Food(Wall &tmpWall);

	//ʳ������
	int x;
	int y;

	//������� ʳ��
	void creatFood();

	//ǽ����
	Wall &wall;
};