

#include "snake.h"
//��snake�У��ȶ�����޸Ĺ��Ĵ���
void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;             //������
	pos.Y = y;             //������
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//������ʾ���������
Snake::Snake(Wall & tmpWall, Food & tmpFood) :wall(tmpWall), food(tmpFood),preKey(NULL)
{
	//��ʼ�������ڵ�
	int  x = 5, y = 5;

	addSnake(x, y);
	addSnake(x, ++y);
	addSnake(x, ++y);
}
//ɾ���ڵ�
void Snake::deleSnake()
{
	//�ж�ֻ�������ڵ�Ͳ�ɾ
	if (Point.size() <= 3)
	{
		return;
	}
	//�Ƚ� ��βԪ�ص����� �ϵ�����ĳɿհ�
	pos p = Point.back();
	//��  ��βԪ������ �н�����Ϣ ����Ϊ��
	wall.setWall(p.x, p.y, ' ');
	//��β�����
	gotoxy(hOut, p.y * 2, p.x);
	cout << " ";

	//����list ����βԪ��
	Point.pop_back();
}
//��ӽڵ�
void Snake::addSnake(int x , int y)
{
	pos p;
	//�ж��Ƿ��ǵ�һ��
	if (0 != Point.size())
	{
		//�Ȼ�ȡlist ���� ͷԪ��
		p = Point.front();
		//����ǰͷԪ�� �������
		wall.setWall(p.x, p.y, '=');
		//���½���λ��  �� ���� ���
		gotoxy(hOut, p.y *2, p.x);
		cout << "=";
	}
	
	
	//����µĽڵ�
	p.x = x; p.y = y;
	//���½ڵ����� ���ó�ͷ
	wall.setWall(p.x, p.y, '@');
	//�����»���ͷ��
	gotoxy(hOut,  p.y * 2, p.x);
	cout << "@";

	//���µ�ͷ�� ѹ��list ����
	Point.push_front(p);
}
bool Snake::moveSnake(char key)
{
	//�Ȼ�ȡ���� ͷ��Ԫ��
	pos p = Point.front();
	//�ж� ����
	switch (key)
	{
	case UP:
		--p.x;
		break;
	case DOWN:
		++p.x;
		break;
	case LEFT:
		--p.y;
		break;
	case RIGHT:
		++p.y;
		break;
	}
	//�ж��Ƿ����  �Ƿ� �Ե�����
	char c = wall.getWall(p.x, p.y);
	if (c == '*' || c == '=')
	{
		//����ǳ� ��ǽ Ӧ����ǰ��һ��  Ȼ����ʾ ����״̬
		if ('*' == c)
		{
			//������  һ�� �ڵ�
			addSnake(p.x, p.y);
			//Ȼ��ɾ�� β�ڵ�
			deleSnake();
		}
		if ('=' == c)
		{
			//��ȡ  �������һ��Ԫ�� 
			pos backpos = Point.back();
			//�ж� ��ǰ �Ƿ���β��
			if (backpos.x == p.x && backpos.y == p.y)
			{
				//��� �½ڵ�
				addSnake(p.x, p.y);
				//ɾ�� β�ڵ�
				deleSnake();
				//���»��� ͷ��
				gotoxy(hOut, p.y * 2, p.x);
				cout << "@";

				return false;
			}

		}
		gotoxy(hOut, wall.ROW /2, wall.ROW/2);
		cout << " GAME  OVER!!!";
		showScore();
		cout << endl;
		//�Ƿ� ����   ��
		return true;
	}
	//Ӧ�� ������һ��ͷ���
	addSnake(p.x, p.y);
	//�ж��Ƿ�Ե� ʳ��
	if (c == '#')
	{
		//���� ��������ʳ��
		food.creatFood();
	}
	else
	{
		//û�Ե� ɾ��β�ڵ�
		deleSnake();
	}
	//��ʾ�÷� �͵ȼ�
	showScore();

	//û��
	return false;
}
//����÷�
void Snake::showScore()
{
	//�ȼ��� �Ե����ٸ�ʳ�� ������ʼ״̬3��
	int foodsize = Point.size() - 3;

	//ÿ��ʳ�� 50 ��	//��ʾ����

	gotoxy(hOut, 0, wall.ROW);
	cout << "�÷� " << foodsize * 50;
	//��ʾ�ȼ�
	gotoxy(hOut, wall.COL, wall.ROW);
	cout << "�ȼ� " << foodsize / 10 + 1;
}
//�����ٶ�
double Snake::getSpeed()
{
	double speed = 300;
	//�ȼ��� �Ե����ٸ�ʳ�� ������ʼ״̬3��
	int foodsize = Point.size() - 3;
	//���� �� ÿ�Ե�10��ʳ�� �ٶ����� 1.2��
	switch (foodsize / 10)
	{
	case 0:
		speed *= 0.8;
		break;
	case 1:
		speed *= 0.6;
		break;
	case 2:
		speed *= 0.4;
		break;
	case 3:
		speed *= 0.2;
		break;
	default:
		speed *= 0.1;
		break;
	}
	return speed;
}
bool Snake::isGood(char &key)
{
	//���ж� �Ƿ� �ǿ�ʼ״̬ ����� ����������
	if (preKey == NULL && key == LEFT)
	{
		return false;
	}
	//������Ϸʱ �ж��Ƿ�������ȷ   ���� �����ϴεķ���  
	if (UP == key || DOWN == key || LEFT == key || RIGHT == key)
	{
		//�ж� ����ķ��� �Ƿ���ϴεķ��� �෴  ��������ϴεķ���
		if ((UP == key && DOWN == preKey) ||
			(DOWN == key && UP == preKey) ||
			(LEFT == key && RIGHT == preKey) ||
			(RIGHT == key && LEFT == preKey))
		{
			key = preKey;
		}
		else
		{
			preKey = key;
		}
	}
	else
	{
		key = preKey;
	}

	return true;
}