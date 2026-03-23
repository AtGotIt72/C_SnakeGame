```C

void welcome2game()
{
	int n;
	
	gotoxy(45,8);
	color(11);
	printf("Snake Game");

	color(12);
	gotoxy(25,12);
	printf("1.Start Game");

	gotoxy(45,12);
	printf("2.Instructions");

	gotoxy(65,12);
	printf("3.Quit Game");
	
	gotoxy(65,20);
	color(15);
	printf("input option:");
	gotoxy(80,20);
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
			exit(0);
			break;
		default:
			gotoxy(40,28);
			color(12);
			printf("please input a number between 1-3");
			_getch();//press any key
			system("cls");
			welcome2game();
	}
}

```

```c
void xpl()
{
    ...
    welcome2game();
}

void lostGame()
{
    ...
    welcome2game();
}
```

##### above: problem 1: can't go back to welcome page after pressing keys at instruction page



##### problem 2: Can't display lost game page after losing game

```c
int gameover; //gameover=0 default; =1 game lost
```

```C
void moveDir()
{
    ...
    hitWall();
    biteSelf();

    if (gameover)
    {
        return;
    }

    p = head;
    if (food->x == newHead->x && food->y == newHead->y)
    {
        ...
    }
    else
    {
        ...
    }
}
```

##### problem 3: The snake can't move the second time playing it

```C
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
	p = NULL;//free old snake nodes
	...
	...
}
```

