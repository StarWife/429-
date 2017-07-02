#include "snake.h"
#include "wall.h"
#include "food.h"
#include <conio.h>
#include <ctime>
int main()
{
	srand((unsigned int)time(NULL));
	//��ʼ�� ����
	Wall wall;
	wall.initWall();
	wall.shouWall();
	//ʳ�����
	Food food(wall);
	food.creatFood();
	//��ʼ����
	Snake snake(wall, food);
	
	char preKey = NULL;
	char key;
	bool isdead = false;
	while (!isdead)
	{
		key = _getch();
		do
		{
			//�ж� ������ �����ֵ 
			if (!snake.isGood(key))continue;

			isdead = snake.moveSnake(key);
			Sleep((int)snake.getSpeed());

		} while (!_kbhit() && !isdead);//��û�м�������ʱ ����0
	}

	system("pause");
	return EXIT_SUCCESS;
}