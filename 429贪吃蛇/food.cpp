
#include "food.h"
#include <Windows.h>
//��snake�У��ȶ�����޸Ĺ��Ĵ���
void gotofoodxy(HANDLE hOutfood, int x, int y)
{
	COORD pos;
	pos.X = x;             //������
	pos.Y = y;             //������
	SetConsoleCursorPosition(hOutfood, pos);
}
HANDLE hOutfood = GetStdHandle(STD_OUTPUT_HANDLE);//������ʾ���������
Food::Food(Wall & tmpWall) :wall(tmpWall)
{

}

void Food::creatFood()
{
	while (true)
	{
		//���λ��
		x = rand() % (wall.ROW - 2) + 1;
		y = rand() % (wall.COL - 2) + 1;

		if ((wall.getWall(x, y) != '=') && (wall.getWall(x, y) != '@'))
		{
			//���ʳ��
			wall.setWall(x, y, '#');
			//����ʳ��
			gotofoodxy(hOutfood, y * 2, x);
			cout << "#";
			break;
		}

	}
}