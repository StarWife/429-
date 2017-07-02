
#pragma once
#include "wall.h"
#include <Windows.h>
class Food
{
public:

	Food(Wall &tmpWall);

	//食物坐标
	int x;
	int y;

	//随机生成 食物
	void creatFood();

	//墙对象
	Wall &wall;
};