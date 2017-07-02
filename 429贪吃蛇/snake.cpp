

#include "snake.h"
//在snake中，先定义出修改光标的代码
void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;             //横坐标
	pos.Y = y;             //纵坐标
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量
Snake::Snake(Wall & tmpWall, Food & tmpFood) :wall(tmpWall), food(tmpFood),preKey(NULL)
{
	//初始化三个节点
	int  x = 5, y = 5;

	addSnake(x, y);
	addSnake(x, ++y);
	addSnake(x, ++y);
}
//删除节点
void Snake::deleSnake()
{
	//判断只有三个节点就不删
	if (Point.size() <= 3)
	{
		return;
	}
	//先将 队尾元素的坐标 上的身体改成空白
	pos p = Point.back();
	//将  队尾元素坐标 中界面信息 设置为空
	wall.setWall(p.x, p.y, ' ');
	//将尾部清空
	gotoxy(hOut, p.y * 2, p.x);
	cout << " ";

	//弹出list 容器尾元素
	Point.pop_back();
}
//添加节点
void Snake::addSnake(int x , int y)
{
	pos p;
	//判断是否是第一次
	if (0 != Point.size())
	{
		//先获取list 容器 头元素
		p = Point.front();
		//将以前头元素 变成身体
		wall.setWall(p.x, p.y, '=');
		//从新将此位置  用 身体 填充
		gotoxy(hOut, p.y *2, p.x);
		cout << "=";
	}
	
	
	//添加新的节点
	p.x = x; p.y = y;
	//将新节点坐标 设置成头
	wall.setWall(p.x, p.y, '@');
	//并重新画出头部
	gotoxy(hOut,  p.y * 2, p.x);
	cout << "@";

	//将新的头部 压入list 容器
	Point.push_front(p);
}
bool Snake::moveSnake(char key)
{
	//先获取容器 头部元素
	pos p = Point.front();
	//判断 方向
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
	//判断是否出界  是否 吃到身体
	char c = wall.getWall(p.x, p.y);
	if (c == '*' || c == '=')
	{
		//如果是吃 到墙 应该向前进一步  然后显示 死亡状态
		if ('*' == c)
		{
			//先增加  一个 节点
			addSnake(p.x, p.y);
			//然后删除 尾节点
			deleSnake();
		}
		if ('=' == c)
		{
			//获取  容器最后一个元素 
			pos backpos = Point.back();
			//判断 当前 是否是尾部
			if (backpos.x == p.x && backpos.y == p.y)
			{
				//添加 新节点
				addSnake(p.x, p.y);
				//删除 尾节点
				deleSnake();
				//重新绘制 头部
				gotoxy(hOut, p.y * 2, p.x);
				cout << "@";

				return false;
			}

		}
		gotoxy(hOut, wall.ROW /2, wall.ROW/2);
		cout << " GAME  OVER!!!";
		showScore();
		cout << endl;
		//是否 死亡   是
		return true;
	}
	//应该 新增加一个头结点
	addSnake(p.x, p.y);
	//判断是否吃到 食物
	if (c == '#')
	{
		//并且 重新生成食物
		food.creatFood();
	}
	else
	{
		//没吃到 删除尾节点
		deleSnake();
	}
	//显示得分 和等级
	showScore();

	//没死
	return false;
}
//计算得分
void Snake::showScore()
{
	//先计算 吃到多少个食物 减掉初始状态3个
	int foodsize = Point.size() - 3;

	//每个食物 50 分	//显示分数

	gotoxy(hOut, 0, wall.ROW);
	cout << "得分 " << foodsize * 50;
	//显示等级
	gotoxy(hOut, wall.COL, wall.ROW);
	cout << "等级 " << foodsize / 10 + 1;
}
//计算速度
double Snake::getSpeed()
{
	double speed = 300;
	//先计算 吃到多少个食物 减掉初始状态3个
	int foodsize = Point.size() - 3;
	//规则 是 每吃到10个食物 速度提升 1.2倍
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
	//先判断 是否 是开始状态 如果是 则不能向左走
	if (preKey == NULL && key == LEFT)
	{
		return false;
	}
	//进入游戏时 判断是否输入正确   否则 进行上次的方向  
	if (UP == key || DOWN == key || LEFT == key || RIGHT == key)
	{
		//判断 输入的方向 是否跟上次的方向 相反  是则进行上次的方向
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