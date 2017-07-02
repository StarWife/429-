
#include "food.h"
#include <Windows.h>
//在snake中，先定义出修改光标的代码
void gotofoodxy(HANDLE hOutfood, int x, int y)
{
	COORD pos;
	pos.X = x;             //横坐标
	pos.Y = y;             //纵坐标
	SetConsoleCursorPosition(hOutfood, pos);
}
HANDLE hOutfood = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量
Food::Food(Wall & tmpWall) :wall(tmpWall)
{

}

void Food::creatFood()
{
	while (true)
	{
		//随机位置
		x = rand() % (wall.ROW - 2) + 1;
		y = rand() % (wall.COL - 2) + 1;

		if ((wall.getWall(x, y) != '=') && (wall.getWall(x, y) != '@'))
		{
			//添加食物
			wall.setWall(x, y, '#');
			//画出食物
			gotofoodxy(hOutfood, y * 2, x);
			cout << "#";
			break;
		}

	}
}