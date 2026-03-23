#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

//方向  上下左右
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


//链表节点类型声明
typedef struct _snake_t {
	//数据域
	int x;
	int y;

	struct _snake_t *next;//指针域
}snake_t;

//设置文本的颜色
int setColor(int c);

//设置光标的位置
int gotoXY(int x, int y);

//绘制字符画 --蛇
int printSnake(void);

//欢迎界面
int  welcomGame(void);

//游戏帮助界面
int aboutGame(void);

//绘制游戏地图
int printMap(void);

//显示分数和提示信息
int showScoreTips(void);

//从文件中读取最高分  ALT + Enter 
int readFile(void);

//初始化蛇
int initSnake(void);

//随机食物
int randFood(void);

//蛇的移动
int moveSnake(void);

//通过按键控制蛇的移动
int moveKeyControl(void);

//加速蛇的移动
int speedUp(void);

//减速蛇的移动
int speedDown(void);

//判断是否撞到墙壁 撞墙了就返回1 否则返回0
int isHitWall(void);

//判断是否咬到自己 咬到自己就返回1 否则返回0
int isBitSelf(void);

//游戏失败界面边框
void failGameUi(void);

//结束游戏
int endGame(void);

//将最高分写入文件中
int writeFile(int score);

//销毁蛇
int destroySnake(void);
