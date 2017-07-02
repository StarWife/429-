
#pragma once 
#include <iostream>

using namespace std;

class Wall
{
public:
	//游戏界面的宽高
	enum {ROW= 26 , COL= 26};

	//初始化状态
	void initWall();

	//设置游戏状态
	void setWall(int x, int y, char c);

	//获取游戏内状态
	char getWall(int x, int y);

	//显示界面
	void shouWall();

	//界面  及其游戏状态
	char wallArray[ROW][COL];
};