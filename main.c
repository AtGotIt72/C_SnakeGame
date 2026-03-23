#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

#include "header.h"

DWORD g_startTime = 0;
int g_gameTime = 0;

/*set timer*/
void startTimer()
{
	g_startTime = GetTickCount();
}
int getTime()
{
	g_gameTime = (GetTickCount() - g_startTime) / 1000;
	return g_gameTime;
} 

/*start game*/
void startGame()
{
	snake* temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
	if (food != NULL) {
		free(food);
		food = NULL;
	}

	head = NULL;
	food = NULL;
	p = NULL;
	
	startTimer();
	gameover = 0;
	score = 0;
	f_score = 10;
	sleeptime = 100;
	move = R;
	createMap();
	initSnake();
	createFood();
	keyControl();
}

/*set cursor xy*/
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle
	(STD_OUTPUT_HANDLE),c);
}

/*set font color*/
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle
	(STD_OUTPUT_HANDLE),c);
	return 0;
}

/*hide cursor*/
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

/*Welcome UI*/
void welcome2game()
{
	int n;
	
	while (1)
	{
		gotoxy(45, 8);
		color(11);
		printf("Snake Game");

		color(12);
		gotoxy(25, 12);
		printf("1.Start Game");

		gotoxy(45, 12);
		printf("2.Instructions");

		gotoxy(65, 12);
		printf("3.Quit Game");

		gotoxy(65, 20);
		color(15);
		printf("input option:");
		gotoxy(80, 20);
		/*color(15);
		printf("Thank u 4 playing");*/

		scanf_s("%d", &n);//input option
		switch (n)
		{
		case 1:
			system("cls"); //clear screen
			HideCursor();
			startGame();
			break;
		case 2:
			xpl();
			break;
		case 3:
			system("cls");
			exit(0);
			break;
		default:
			gotoxy(40, 28);
			color(12);
			printf("please input a number between 1-3");
			_getch();//press any key
			system("cls");
			welcome2game();
			break;
		}
	}
	
}

/*Generate map*/
void createMap()
{
	int i, j;
	system("cls");
	for (int i = 0; i <=56; i += 2)	//draw t/b borders
	{
		gotoxy(i,0);
		color(3);
		printf("# ");
		gotoxy(i,26);
		printf("# ");
	}
	for (int i = 0; i <=26; i++) //draw l/r borders
	{
		gotoxy(0,i);
		printf("# ");
		gotoxy(56,i);
		printf("# ");
	}
	scoreAndTips();
	/*for (i = 2; i < 56; i += 2)
	{
		for (j = 1; j < 26; j++)
		{
			gotoxy(i,j);
			printf("  ");
		}
	}*/
	/*gotoxy(80,20);*/
}

/*tips*/
void scoreAndTips()
{
	gotoxy(65,2);
	color(12);
	printf("Score:%d",score);
	gotoxy(65,4);
	printf("Score for each food:%d",f_score);
	
	gotoxy(65,8);
	printf("Use arrows to move");
	gotoxy(65,10);
	printf("F1:Speed Up");
	gotoxy(65,12);
	printf("F2:Speed Down");
	
	gotoxy(65,16);
	printf("Press space to pause");
	gotoxy(65,18);
	printf("Press ESC to quit");

	int seconds = getTime();
	time_use = seconds;

	gotoxy(65,22);
	color(11);
	printf("Time:%d s  ",seconds);

	gotoxy(0,60);

}

/*initialize snake*/
void initSnake()
{
	snake* tail = (snake*)malloc(sizeof(snake));
	tail->x = 24;
	tail->y = 5;//initial position of the snake
	tail->next = NULL;
	int i;

	for (i = 0; i < 3; i++)
	{
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = tail->y;
		tail = head;

		p = tail;
		while (NULL != p)
		{
			color(14);
			gotoxy(p->x, p->y);
			if (tail == p)
			{
				printf("@");
			}
			else
			{
				printf("o");
			}
			p = p->next;
		}
	}
}

/*create food*/
void createFood()
{
	food = malloc(sizeof(snake));
	snake* tmp = NULL;

	while (1)
	{
		while (1)
		{
			food->x = (rand() % 27 + 1) * 2;
			if (food->x % 2 == 0)
			{
				break;
			}
		}
		food->y = rand() % 23 + 1;
		tmp = head;
		while (tmp != NULL)
		{
			if ((food->x == tmp->x) && (food->y == tmp->y))
			{
				break;
			}

			tmp = tmp->next;

		}
		if (tmp == NULL)
		{
			gotoxy(food->x, food->y);
			color(12);
			printf("$");
			break;
		}
		else
		{
			continue;
		}
	}

}

/*judge whether bite snake itself*/
void biteSelf()
{
	snake* self = head->next;
	while (self != NULL)
	{
		if ((head->x == self->x) && (head->y == self->y))
		{
			gameover = 1;
			lostGame();
		}
		self = self->next;
	}
}

/*judge if hit the wall*/
void hitWall()
{
	if (head->x==0 || head->x==56 ||
		head->y==0 || head->y==26)
	{
		gameover = 1;
		lostGame();
	}

}

/*speed up*/
void speedUp()
{
	if (sleeptime > 50)
	{
		sleeptime -= 10;
		f_score = f_score + 2;
	}
}

/*speed down*/
void speedDown()
{
	if (sleeptime <= 350)
	{
		sleeptime += 10;
		f_score = f_score - 2;
	}
}

/*motion state*/
void moveDir()
{
	
	snake* newHead = (snake*)malloc(sizeof(snake));

	if (move == U)
	{
		newHead->x = head->x;
		newHead->y = head->y - 1;
	}
	else if (move == D)
	{
		newHead->x = head->x;
		newHead->y = head->y + 1;
	}
	else if (move == L)
	{
		newHead->x = head->x - 2;
		newHead->y = head->y;
	}
	else if (move == R)
	{
		newHead->x = head->x + 2;
		newHead->y = head->y;
	}
	newHead->next = head;
	head = newHead;

	hitWall();
	biteSelf();

	if (gameover)
	{
		return;
	}

	p = head;
	if (food->x == newHead->x && food->y == newHead->y)
	{
		color(14);
		while (p != NULL)
		{
			gotoxy(p->x,p->y);
			if (p == head)
			{
				printf("@");
			}
			else
			{
				printf("o");
			}
			p = p->next;
		}

		score += f_score;
		createFood();
	}

	else
	{
		while (p->next->next != NULL) //?
		{
			color(14);
			gotoxy(p->x, p->y);
			if (p == head)
			{
				printf("@");
			}
			else
			{
				printf("o");
			}
			p = p->next;
		}
		gotoxy(p->next->x,p->next->y);
		printf("  ");//clear old tail
		free(p->next);
		p->next = NULL;
	}
}

/*keyboard control*/
void keyControl()
{
	while (!gameover)
	{
		if ((GetAsyncKeyState(VK_UP)&0x8000)&&move!=D)
		{
			move = U;
		}
		else if ((GetAsyncKeyState(VK_DOWN)&0x8000) && move != U)
		{
			move = D;
		}
		else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && move != R)
		{
			move = L;
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && move != L)
		{
			move = R;
		}

		if (GetAsyncKeyState(VK_F1) & 0x8000)
		{
			speedUp();
		}
		else if (GetAsyncKeyState(VK_F2) & 0x8000)
		{
			speedDown();
		}
		else if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			while (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				Sleep(50);
			}

			while (!(GetAsyncKeyState(VK_SPACE) & 0x8000))
			{
				Sleep(50);
			}

			while (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				Sleep(50);
			}
		}
		
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			exit(0);
		}
		
		Sleep(sleeptime);
		moveDir();
		if (!gameover)
		{
			scoreAndTips();
		}
	}
}


/*gameover ui*/
void lostGame()
{
	system("cls");
	gotoxy(45,8);
	color(12);
	printf("Game Over!");

	gotoxy(40,12);
	color(11);
	printf("time use:%d s",time_use);

	gotoxy(40,14);
	printf("score:%d", score);

	gotoxy(40,18);
	color(15);
	printf("Press any key to continue...");

	while (_kbhit()) _getch();
	_getch();
	system("cls");
	//welcome2game();
}

/*Instructions*/
void xpl() 
{
	system("cls");
	int i, j = 1;

	gotoxy(30, 8);
	color(12);
	printf("Instructions:");
	gotoxy(30, 12);
	color(15);
	printf("1. Use the arrow keys to control the snake's movement.");
	gotoxy(30, 14);
	printf("2. Eat the food to grow longer and earn points.");
	gotoxy(30, 16);
	printf("3. Avoid colliding with the walls or biting yourself.");
	gotoxy(30, 18);
	printf("4. Press F1 to speed up the snake, and F2 to slow it down.");
	gotoxy(30, 20);
	printf("5. Press space to pause the game, and ESC to quit.");
	gotoxy(30, 22);
	printf("6. Press any key to go back");
	_getch();
	system("cls");
	//welcome2game();
}

int main()
{
	system("mode con cols=110 lines=40");
	welcome2game();
	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
