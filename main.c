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
	food_growth = 1;
	grow_pending = 0;
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
		gotoxy(20, 12);
		printf("1.Start Game");

		gotoxy(40, 12);
		printf("2.Instructions");

		gotoxy(60, 12);
		printf("3.Rank List");

		gotoxy(80, 12);
		printf("4.Quit Game");

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
			showRank();
			break;
		case 4:
			system("cls");
			exit(0);
			break;
		default:
			gotoxy(40, 28);
			color(12);
			printf("please input a number between 1-4");
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
	gotoxy(65,6);
	printf("Growth for each food:%d",food_growth);
	
	gotoxy(65,10);
	printf("Use arrows to move");
	gotoxy(65,12);
	printf("F1:Speed Up");
	gotoxy(65,14);
	printf("F2:Speed Down");
	
	gotoxy(65,18);
	printf("Press space to pause");
	gotoxy(65,20);
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
	tail->type = -1;
	tail->next = NULL;
	int i;

	for (i = 0; i < 3; i++)
	{
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = tail->y;
		head->type = -1;
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

/*get food type*/
char getFoodType(int type)
{
	if (type == 0) return '$';
	if (type == 1) return '&';
	return '*';
}

/*get food color*/
int getFoodColor(int type)
{
	if (type == 0) return 12;
	if (type == 1) return 11;
	return 14;
}

/*apply food effect*/
void applyFoodEffect(int type)
{
	if (type == 0)
	{
		f_score = 10;
		food_growth = 1;
	}
	else if (type == 1)
	{
		f_score = 20;
		food_growth = 2;
	}
	else
	{
		f_score = 30;
		food_growth = 3;
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
			applyFoodEffect(food->type = rand() % 3);
			gotoxy(food->x, food->y);
			color(getFoodColor(food->type));
			printf("%c", getFoodType(food->type));
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
		grow_pending += food_growth;
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
		if (grow_pending > 0)
		{
			grow_pending--;
		}
		else
		{
			p = head;
			while (p->next->next != NULL)
			{
				p = p->next;
			}
			gotoxy(p->next->x, p->next->y);
			printf("  ");//clear old tail
			free(p->next);
			p->next = NULL;
		}
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
	saveScore(score);

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

	gotoxy(30, 8);
	color(12);
	printf("Instructions:");
	gotoxy(30, 12);
	color(15);
	printf("1. Use the arrow keys to control the snake's movement.");
	gotoxy(30, 14);
	printf("2. Eat different food to grow different lengths.");
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

/*save current score*/
void saveScore(int newScore)
{
	int rank[RANK_SIZE + 1] = {0};
	int i, j, count = 0;
	FILE* fp = NULL;
	fopen_s(&fp,RANK_FILE,"r");
	if (fp != NULL)
	{
		while (count < RANK_SIZE && fscanf_s(fp, "%d", &rank[count]) == 1)
		{
			count++;
		}
		fclose(fp);
	}

	rank[count++] = newScore;
	for (i = 0; i < count - 1; i++)//sorting scores
	{
		for (j = i + 1; j < count; j++)
		{
			if (rank[j] > rank[i])
			{
				int temp = rank[i];
				rank[i] = rank[j];
				rank[j] = temp;
			}
		}
	}

	if (count > RANK_SIZE)
	{
		count = RANK_SIZE;
	}

	fopen_s(&fp,RANK_FILE, "w");
	if (fp != NULL)
	{
		for (i = 0; i < count; i++)
		{
			fprintf(fp,"%d\n",rank[i]);
		}
		fclose(fp);
	}
	
}

/*show rank*/
void showRank()
{
	FILE* fp = NULL;
	fopen_s(&fp,RANK_FILE,"r+");
	int s, i = 1;

	system("cls");
	gotoxy(42,6);
	color(11);
	printf("Rank List");

	if (fp == NULL)
	{
		gotoxy(35,12);
		color(12);
		printf("No ranking data yet.");
	}
	else
	{
		while (fscanf_s(fp, "%d", &s) == 1)
		{
			gotoxy(35, 8 + i * 2);
			color(14);
			printf("No.%d    %d",i,s);
			i++;
		}
		fclose(fp);
	}

	gotoxy(28,32);
	color(15);
	printf("Press any key to return");
	_getch();
	system("cls");
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
