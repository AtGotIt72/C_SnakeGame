
#include "snake.h"
#include <time.h>

int main(void)
{
	int choice = 0;

	//设置控制台的宽高
	system("mode con cols=100 lines=30");

	//设置随机种子
	srand(time(NULL));

	//循环接受用户的选择
	while (1)
	{
		//显示欢迎界面
		choice = welcomGame();

		switch (choice)
		{
			//开始游戏
		case 1:
			//printf("开始游戏");
			printMap();
			showScoreTips();

			//初始化蛇
			initSnake();

			//随机食物
			randFood();

			//通过方向键控制蛇的移动
			moveKeyControl();

			break;

			//游戏说明
		case 2:
			//printf("游戏说明");
			aboutGame();
			break;

			//退出游戏
		case 3:
			//printf("退出游戏");
			//系统提供的函数 结束程序
			exit(0);
			break;

			//输入非法 重新输入
		default:
			//printf("选择非法");
			setColor(12);
			gotoXY(45, 28);
			printf("非法的选择,按下回车键继续");
			//getchar();
		}

		//按下回车键继续
		getchar();
	}

	system("pause");

	return 0;
}


