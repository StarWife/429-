
#pragma once
#include <list>
#include <Windows.h>
#include "wall.h"
#include "food.h"
class Snake
{
public:
	//初始化 蛇状态
	Snake(Wall & tmpWall,Food &tmpFood);

	enum { UP = 'w', LEFT = 'a', DOWN = 's', RIGHT = 'd' };

	//蛇身体坐标
	struct pos
	{
		int x;
		int y;
	};
	//保存上一次合法的 键盘输入
	char preKey;

	//判断 键盘输入是否合法 
	bool isGood(char &key);

	//移动  检测键盘输入
	bool moveSnake(char key);

	//计算 显示得分  和等级
	void showScore();

	//计算速度
	double getSpeed();
private:
	//蛇链表
	list<pos> Point;
	
	//删除节点	尾部弹出
	void deleSnake();

	//添加 新节点   头部添加
	void addSnake(int x, int y);
	
	//墙的对象
	Wall &wall;

	//食物对象
	Food &food;
};