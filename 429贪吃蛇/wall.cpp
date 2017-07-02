
#include "wall.h"

void Wall::initWall()
{

	//��Ϸ����
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			//ǽ
			if (i == 0 || j == 0 || (i == ROW - 1 )|| (j == COL - 1))
			{
				wallArray[i][j] = '*';
			}
			//��������
			else
			{
				wallArray[i][j] = ' ';
			}
		}
	}
}
//�ı�״̬
void Wall::setWall(int  x, int y , char c)
{
	wallArray[x][y] = c;
}
//��ȡ״̬
char Wall::getWall(int x, int y)
{
	return wallArray[x][y];
}
//��ӡ����
void Wall::shouWall()
{
	system("title Snake Game _Sunday");
	int index = 6;
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			cout << wallArray[i][j] << " ";
		}
		if (index == i)
			cout << "by__Sunday";
		if (index + 2 == i)
			cout << "selet w: UP";
		if (index + 4 == i)
			cout << "selet a: LEFT";
		if (index + 6 == i)
			cout << "selet s: DOWN";
		if (index + 8 == i)
			cout << "selet d: RIGHT";
		cout << endl;
	}
}