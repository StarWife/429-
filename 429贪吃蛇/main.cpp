#include "snake.h"
#include "wall.h"
#include "food.h"
#include <conio.h>
#include <ctime>
int main()
{
	srand((unsigned int)time(NULL));
	//初始化 界面
	Wall wall;
	wall.initWall();
	wall.shouWall();
	//食物对象
	Food food(wall);
	food.creatFood();
	//初始化蛇
	Snake snake(wall, food);
	
	char preKey = NULL;
	char key;
	bool isdead = false;
	while (!isdead)
	{
		key = _getch();
		do
		{
			//判断 并处理 键入的值 
			if (!snake.isGood(key))continue;

			isdead = snake.moveSnake(key);
			Sleep((int)snake.getSpeed());

		} while (!_kbhit() && !isdead);//当没有键盘输入时 返回0
	}

	system("pause");
	return EXIT_SUCCESS;
}