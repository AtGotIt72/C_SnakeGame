
#define _CRT_SECURE_NO_WARNINGS
#include "snake.h"


//得分
int score = 0;

//吃掉每一个食物的得分
int add = 1;

//蛇的移动方向
int direction = RIGHT;

//睡眠时间
int sleepTime = 350;

//结束的标志
int endStatus = 0;

//链表的头指针
snake_t *head = NULL;

//食物的节点指针
snake_t *foodNode = NULL;

//设置文本的颜色  c就是颜色值
int setColor(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 0;
}

//设置光标的坐标  
int gotoXY(int x, int y)
{
	//坐标结构体类型
	COORD c;

	//横坐标
	c.X = x;
	//纵坐标
	c.Y = y;

	//STD_OUTPUT_HANDLE 表示标准输出
	//c 坐标值
	//GetStdHandle(STD_OUTPUT_HANDLE) 获取当前标准输出句柄
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

	return 0;
}


//绘制字符画 --蛇
int printSnake(void)
{
	//清屏
	system("cls");

	gotoXY(35, 1);
	setColor(6);
	printf("/^\\/^\\");      //蛇眼睛

	gotoXY(34, 2);
	printf("|__|  O|");      //蛇眼睛

	gotoXY(33, 2);
	setColor(2);
	printf("_");

	gotoXY(25, 3);
	setColor(12);
	printf("\\/");      	//蛇信

	gotoXY(31, 3);
	setColor(2);
	printf("/");

	gotoXY(37, 3);
	setColor(6);
	printf(" \\_/");     	//蛇眼睛

	gotoXY(41, 3);
	setColor(10);
	printf(" \\");

	gotoXY(26, 4);
	setColor(12);
	printf("\\____");   	//舌头

	gotoXY(32, 4);
	printf("_________/");

	gotoXY(31, 4);
	setColor(2);
	printf("|");

	gotoXY(43, 4);
	setColor(10);
	printf("\\");

	gotoXY(32, 5);
	setColor(2);
	printf("\\_______");    //蛇嘴

	gotoXY(44, 5);
	setColor(10);
	printf("\\");

	gotoXY(39, 6);
	printf("|     |                  \\");  //下面都是画蛇身

	gotoXY(38, 7);
	printf("/      /                   \\");

	gotoXY(37, 8);
	printf("/      /                    \\ \\");

	gotoXY(35, 9);
	printf("/      /                       \\ \\");

	gotoXY(34, 10);
	printf("/     /                          \\  \\");

	gotoXY(33, 11);
	printf("/     /             _----_         \\   \\");

	gotoXY(32, 12);
	printf("/     /           _-~      ~-_         |  |");

	gotoXY(31, 13);
	printf("(      (        _-~    _--_    ~-_     _/  |");

	gotoXY(32, 14);
	printf("\\     ~-____-~    _-~    ~-_    ~-_-~    /");

	gotoXY(33, 15);
	printf("~-_           _-~          ~-_       _-~");

	gotoXY(35, 16);
	printf("~--______-~                ~-___-~");

	return 0;
}

//欢迎界面
int welcomGame(void)
{
	int choice;


	int i = 0;
	int j = 0;

	//绘制字符画蛇
	printSnake();

	//输出标题
	//设置文本颜色 11
	setColor(11);
	//设置光标位置(45, 18)
	gotoXY(45, 18);
	printf("贪吃蛇游戏");

	//绘制边框
	setColor(14);
	//控制行
	for (i = 20; i <= 26; i++)
	{
		//控制列
		for (j = 27; j <= 74; j++)
		{
			//输出上下边框
			if (i == 20 || i == 26)
			{
				gotoXY(j, i);
				printf("-");
			}
			else if (j == 27 || j == 74)
			{
				//输出左右边框
				gotoXY(j, i);
				printf("|");
			}
			else
			{
				//注意：空格字符
				printf(" ");
			}
		}
	}

	//输出菜单选项
	//设置文本的属性
	setColor(12);
	
	//开始游戏
	gotoXY(35, 22);
	printf("1. 开始游戏");

	//游戏说明
	gotoXY(55, 22);
	printf("2. 游戏说明");

	//退出游戏
	gotoXY(35, 24);
	printf("3. 退出游戏");

	//输出提示信息
	gotoXY(27, 27);
	printf("请选择[1 2 3]: ");

	scanf("%d", &choice);

	//清除换行符  3 \n
	getchar();

	return choice;
}

//游戏说明界面
int aboutGame(void)
{
	int i = 0;
	int j = 0;

	//清屏
	system("cls");

	//输出标题
	setColor(13);
	gotoXY(44, 3);
	printf("游戏说明");

	//绘制上下左右边框
	//控制行
	for (i = 6; i <= 22; i++)
	{
		//控制列
		for (j = 20; j <= 75; j++)
		{
			//上下边框 =
			if (i == 6 || i == 22)
			{
				gotoXY(j, i);
				printf("=");
			}
			else if (j == 20 || j == 75)
			{
				gotoXY(j, i);
				printf("|");
			}
			else
			{

			}
		}
	}

	//输出菜单选项
	setColor(3);
	gotoXY(30, 8);
	printf("★ 1. 不能撞到墙，不能咬到自己");

	setColor(5);
	gotoXY(30, 11);
	printf("★ 2. F1加速前进，F2减速前进");

	setColor(11);
	gotoXY(30, 14);
	printf("★ 3. 使用空格暂停游戏或者继续游戏");

	setColor(13);
	gotoXY(30, 17);
	printf("★ 4. 使用方向键控制前进的方向");

	setColor(14);
	gotoXY(30, 20);
	printf("★ 5. 按下ESC键退出游戏");

	//输出提示信息
	setColor(12);
	gotoXY(20, 24);
	printf("按下回车键返回主界面");

	return 0;
}


//绘制游戏地图
int printMap(void)
{
	int i = 0;
	int j = 0;

	//清屏
	system("cls");

	//控制行
	for (i = 0; i <= 26; i++)
	{
		//控制列
		for (j = 0; j <= 56; j = j + 2)
		{
			//定位光标
			gotoXY(j, i);
			if (0 == i || 26 == i || 0 == j || 56 == j)
			{
				setColor(5);
				printf("□");
			}
			else
			{
				setColor(3);
				printf("■");
			}
		}
	}

	return 0;
}

//显示分数和提示信息
int showScoreTips(void)
{
	int highScore = 0;

	//从文件中读取最高分
	highScore = readFile();


	//显示最高分
	setColor(3);
	gotoXY(64, 4);
	printf("☆☆最高分记录☆☆: %d", highScore);

	//显示当前得分
	setColor(14);
	gotoXY(64, 8);
	printf("得分: %d", score);

	//显示温馨提示
	setColor(12);
	gotoXY(72, 11);
	printf("温 馨 提 示");

	//绘制上下边框
	setColor(10);
	gotoXY(60, 13);
	printf("==================================");

	gotoXY(60, 25);
	printf("==================================");

	//输出提示信息
	setColor(13);
	gotoXY(64, 14);
	printf("※ 吃掉每个食物得分: %d", add);

	gotoXY(64, 16);
	printf("※ 不能撞到墙壁，不能咬到自己");

	gotoXY(64, 18);
	printf("※ F1加速前进，F2减速前进");

	gotoXY(64, 20);
	printf("※ 使用空格暂停游戏或者继续游戏");

	gotoXY(64, 22);
	printf("※ 使用↓↑→←控制前进的方向");

	gotoXY(64, 24);
	printf("※ 按下ESC退出游戏");

	return 0;
}

//读取文件中最高分  最高分保存在sava.txt文件中
int readFile(void)
{
	int ret = -1;
	char buf[32];

	FILE *fp = NULL;

	//1. 以只读的方式打开文件
	fp = fopen("save.txt", "r");
	if (NULL == fp)
	{
		printf("fopen failed...\n");
		return 0;
	}

	//2. 读取文件内容
	memset(buf, 0, sizeof(buf));
	ret = fread(buf, sizeof(char), sizeof(buf), fp);
	if (ret <= 0)
	{
		printf("fread failed...\n");
		return 0;
	}
	

	//3. 关闭文件
	fclose(fp);

	//atoi --> 将字符串的数字转化为数字  "123" --> 123
	return atoi(buf);
}

//初始化蛇身和蛇头
int initSnake(void)
{
	int i = 0;

	snake_t *new = NULL;
	snake_t *tmp = NULL;


	//循环创建四个节点
	for (i = 0; i < 4; i++)
	{
		//分配空间
		new = malloc(sizeof(snake_t));
		if (NULL == new)
		{
			printf("malloc Snake failed....\n");
			return -1;
		}
		memset(new, 0, sizeof(snake_t));

		//赋值
		new->x = 24 + i * 2;
		new->y = 5;

		//头插法
		new->next = head;
		head = new;
	}

	//遍历链表
	tmp = head;
	while (NULL != tmp)
	{
		//设置蛇的颜色 14 黄色
		setColor(14);
		//定位光标
		gotoXY(tmp->x, tmp->y);

		//第一个节点就是我们的蛇头节点
		if (head == tmp)
		{
			printf("●");
		}
		else
		{
			printf("★");
		}

		tmp = tmp->next;
	}


	return 0;
}

//随机食物
int randFood(void)
{
	snake_t *tmp = NULL;

	//随机的食物不能够出现在墙壁上
	//随机的食物不能够出现在蛇身上
	//随机的食物x坐标一定是偶数

	//分配空间
	foodNode = malloc(sizeof(snake_t));
	if (NULL == foodNode)
	{
		gotoXY(1, 28);
		printf("malloc failed...\n");
		return -1;
	}
	memset(foodNode, 0, sizeof(snake_t));

	while (1)
	{
		while (1)
		{
			//保证X坐标是偶数 同时不应该出现在墙上(2, 54)
			foodNode->x = rand() % 53 + 2;

			if (0 == foodNode->x % 2)
			{
				break;
			}
		}

		//y坐标是（1,25）
		foodNode->y = rand() % 25 + 1;  //(0,24) --> (1, 25)

		//判断食物不能够在蛇身上
		tmp = head;

		while (NULL != tmp)
		{
			if ((foodNode->x == tmp->x) && (foodNode->y == tmp->y))
			{
				break;
			}

			tmp = tmp->next;
		}

		//食物没有在蛇的身上
		if (NULL == tmp)
		{
			gotoXY(foodNode->x, foodNode->y);
			setColor(12);
			printf("●");
			break;
		}
		else
		{
			continue;
		}

	}

	return 0;
}

//控制蛇的移动
int moveSnake(void)
{
	snake_t *new = NULL;
	snake_t *tmp = NULL;
	snake_t *save = NULL;

	//分配新的节点
	new = malloc(sizeof(snake_t));
	if (NULL == new)
	{
		printf("malloc failed...\n");
		return -1;
	}
	memset(new, 0, sizeof(snake_t));

	//向上
	if (UP == direction)
	{
		new->x = head->x;
		new->y = head->y - 1;
	}

	//向下
	if (DOWN == direction)
	{
		new->x = head->x;
		new->y = head->y + 1;
	}

	//向左
	if (LEFT == direction)
	{
		new->x = head->x - 2;
		new->y = head->y;
	}

	//向右
	if (RIGHT == direction)
	{
		new->x = head->x + 2;
		new->y = head->y;
	}

	//头插法
	new->next = head;
	head = new;

	tmp = head;
	setColor(14);

	//判断是否为食物
	if ((new->x == foodNode->x) && (foodNode->y == new->y))
	{
		//循环画出蛇
		while (NULL != tmp)
		{
			gotoXY(tmp->x, tmp->y);
			if (head == tmp)
			{
				printf("●");
			}
			else
			{
				printf("★");
			}

			tmp = tmp->next;
		}

		//吃掉一个食物 增加分数
		score = score + add;

		//随机食物
		randFood();
	}
	else
	{
		while (NULL != tmp->next)
		{
			gotoXY(tmp->x, tmp->y);
			if (head == tmp)
			{
				printf("●");
			}
			else
			{
				printf("★");
			}

			save = tmp;
			tmp = tmp->next;
		}

		//将最后一个节点释放
		gotoXY(tmp->x, tmp->y);
		setColor(3);
		printf("■");

		save->next = NULL;
		free(tmp);
	}

	return 0;
}

//通过方向键控制蛇的移动
int moveKeyControl(void)
{
	//默认方向就是向右
	direction = RIGHT;

	while (1)
	{
		//显示右侧的小提示
		showScoreTips();

		//向上
		if (GetAsyncKeyState(VK_UP) && direction != DOWN)
		{
			direction = UP;
		}

		//向下
		if (GetAsyncKeyState(VK_DOWN) && direction != UP)
		{
			direction = DOWN;
		}


		//向左
		if (GetAsyncKeyState(VK_LEFT) && direction != RIGHT)
		{
			direction = LEFT;
		}

		//向右
		if (GetAsyncKeyState(VK_RIGHT) && direction != LEFT)
		{
			direction = RIGHT;
		}

		//按下空格暂停游戏或者继续游戏
		if (GetAsyncKeyState(VK_SPACE))
		{
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(VK_SPACE))
				{
					break;
				}
			}
		}

		//按下F8加速
		if (GetAsyncKeyState(VK_F8))
		{
			//减少睡眠时间  但是睡眠的时间不能小于50ms
			speedUp();
		}

		//按下F9减速
		if (GetAsyncKeyState(VK_F9))
		{
			//增加睡眠的时间
			speedDown();
		}

		//按下ESC键 结束游戏
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			//表示用户按下ESC键结束游戏
			endStatus = 3;

			endGame();

			//exit(1);
			break;
		}
		

		Sleep(sleepTime);

		moveSnake();

		//判断是否撞到墙壁
		if (isHitWall())
		{
			endStatus = 1;
			endGame();
			break;
		}

		//判断是否咬到自己
		if (isBitSelf())
		{
			endStatus = 2;
			endGame();
			break;
		}
	}

	return 0;
}

//加速蛇的移动
int speedUp(void)
{
	//最快的速度 睡眠时间50ms
	if (sleepTime > 50)
	{
		sleepTime = sleepTime - 20;
		add = add + 2;
	}

	return 0;
}


//减速蛇的移动  增加睡眠的时间
int speedDown(void)
{
	if (sleepTime < 350)
	{
		sleepTime = sleepTime + 20;

		//减少增加的分数
		add = add - 2;
	}

	if (add <= 0)
	{
		add = 1;
	}

	return 0;
}

//判断是否撞到墙壁
int isHitWall(void)
{
	//表示撞到墙壁
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		return 1;
	}

	//表示没有撞到墙壁
	return 0;
}

//判断是否咬到自己
int isBitSelf(void)
{
	snake_t *tmp = NULL;

	//从第二个节点开始算
	tmp = head->next;

	while (NULL != tmp)
	{
		if ((head->x == tmp->x) && (head->y == tmp->y))
		{
			return 1;
		}

		//指向下一个节点
		tmp = tmp->next;
	}

	return 0;
}

//游戏失败界面边框
void failGameUi(void)
{
	int i = 0;

	//清屏
	system("cls");

	//显示游戏失败提示
	setColor(12);
	gotoXY(44, 3);
	printf("游 戏 失 败!!!");

	//设置边框的颜色
	setColor(11);
	gotoXY(17, 5);

	//绘制上边框
	printf("+----------------------------------------------------------------+");
	
	//绘制下边框
	gotoXY(17, 20);
	printf("+----------------------------------------------------------------+");

	//绘制左右边框
	for (i = 6; i < 20; i++)
	{
		gotoXY(17, i);
		printf("|");

		gotoXY(82, i);
		printf("|");
	}
}

//结束游戏
int endGame(void)
{
	int n = 0;
	int highScore = 0;

	while (1)
	{
		//显示游戏失败界面
		failGameUi();

		setColor(12);
		gotoXY(38, 9);

		//不同的状态 显示不同失败提示 endStatus
		switch (endStatus)
		{
			//撞到墙壁
		case 1:
			printf("您撞到墙了，游戏结束!!!");
			break;

			//咬到自己
		case 2:
			printf("您咬到蛇身了，游戏结束!!!");
			break;

			//用户按下ESC
		case 3:
			printf("您已经结束了游戏，游戏结束!!!");
			break;

		default:
			;
		}

		//显示您的得分
		setColor(13);
		gotoXY(43, 12);
		printf("您的得分: %d", score);

		//显示最高分
		//从文件中读取最高分
		highScore = readFile();

		if (score > highScore)
		{
			setColor(10);
			gotoXY(38, 16);
			printf("恭喜你，您已经破纪录了。");

			//将最高分写入文件
			writeFile(score);
		}
		else
		{
			setColor(10);
			gotoXY(38, 16);
			printf("加油哦， 离最高分还差%d分", highScore - score);
		}

		//输出用户选择的信息
		gotoXY(25, 23);
		setColor(12);
		printf("再玩一局请输入：1");

		gotoXY(52, 23);
		printf("直接退出请输入：2");

		gotoXY(46, 25);
		setColor(11);
		printf("请选择: ");

		scanf("%d", &n);
		getchar();

		if (1 == n)
		{
			score = 0;
			sleepTime = 350;
			add = 1;

			//销毁蛇
			destroySnake();

			break;
		}
		else if (2 == n)
		{
			exit(0);
		}
		else
		{
			gotoXY(30, 27);
			setColor(12);
			printf("您的输入有误，请重新输入，按下回车键继续");
			getchar();
		}
	}
	return 0;
}


//将最高分写入文件中
int writeFile(int score)
{
	FILE *fp = NULL;

	//打开文件
	fp = fopen("save.txt", "w+");
	if (NULL == fp)
	{
		printf("打开文件失败\n");
		return -1;
	}

	//将最高分写入文件中
	fprintf(fp, "%d", score);

	//关闭文件
	fclose(fp);

	return 0;
}

//销毁蛇
int destroySnake(void)
{
	snake_t *tmp = NULL;
	snake_t *save = NULL;

	tmp = head;
	while (NULL != tmp)
	{
		save = tmp->next;
		free(tmp);

		tmp = save;
	}

	head = NULL;

	return 0;
}
