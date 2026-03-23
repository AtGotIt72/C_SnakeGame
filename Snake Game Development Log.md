### Snake Game Development Log

------

#### INSTRUTIONS

Development platform: Microsoft Visual Studio 2022

------

#### DEFINITION CODES

All definitions are included in header.h

##### Definition of functions

```c
void gotoxy(int x, int y);  //set cursor position
int color(int c); //font color
void HideCursor(); //hide cursor	
void welcome2game(); //welcome ui
void startGame();//start game

void createMap();//generate map
void scoreAndTips();//display score and tips
void initSnake(); //initialize snake
void createFood(); //create food on map
void biteSelf(); //judge if bite self
void hitWall(); //judge if hit wall

void speedUp(); //press F1 to speed up
void speedDown();//press F2 to speed down
void moveDir(); //direction of movement
void keyControl(); //keyboard control
void startTimer();//start timer when the game starts
int getTime(); //get time during the game

void lostGame(); //lost game ui
void choose(); //choice after the end
void xpl(); //explanation of the game
```

##### Definition of constant

```c
/*motion state*/
#define U 1
#define D 2
#define L 3
#define R 4

int score=0, f_score=10; //score, score for each food
int time_use;//time usage
int sleeptime;
int move=R;//motion state
int gameover = 0;//judge if lose the game
```

##### Definition of snake (using struct type)

```C
typedef struct snakeNode {
	int x;
	int y;
	struct snakeNode* next;
}snake;

snake* head; //head of the snake
snake* food; //food of the snake
snake* p;//temporary pointer
```

More details please read main.c

------

#### FEATURES

1. Including a Welcome page, a Game page and a Game Over page.

2. Options including start game, view instructions of the game and quit game are available on Welcome page.

3. Time usage of the game process and score count are added (On both the Game page and the Game Over page),  speed and the score for each food are related.

   

------

#### VERSION ITERATION NOTES

##### problem 1: Can't display lost game page after losing game

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

##### problem 2: The snake can't move the second time playing it

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

**reason**: 第一次把 `GetAsyncKeyState(...)` 直接当成布尔值判断的，例如：`if (GetAsyncKeyState(VK_UP))`。但这个函数返回值里不只有“当前是否按下”，还带有“自上次调用后是否按过”的状态。这样在**第一次游戏结束、回主界面、再进入第二次游戏**时，上一轮残留的按键状态很容易被误判，尤其是空格暂停这一段，会把程序卡在暂停逻辑里，所以看起来就像“蛇不会动了”。

change example:

```C
if (GetAsyncKeyState(VK_UP)&&move!=D)
```

alter to

```C
if ((GetAsyncKeyState(VK_UP) & 0x8000) && move != D)
```



##### problem 3: the game does not pause after pressing space

original codes

```c
else if(GetAsyncKeyState(VK_SPACE))
{
	while (!GetAsyncKeyState(VK_SPACE))
	{
		Sleep(100);
	}
	Sleep(100);
}
```

alter to

```C
else if (GetAsyncKeyState(VK_SPACE) & 0x8000)
{
	// waiting for releasing
	while (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		Sleep(50);
	}

	// waiting for the next press
	while (!(GetAsyncKeyState(VK_SPACE) & 0x8000))
	{
		Sleep(50);
	}

	// waiting for releasing
	while (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		Sleep(50);
	}
}
```



##### problem 4: Time display problem (remaining 0s)

solution: refresh time display in `scoreAndTips( )`

add

```C
if (!gameover)
{
    scoreAndTips();
}
```

after judging moving direction;

##### problem 5: uncleaned snake tail

add

```C
gotoxy(p->next->x, p->next->y);
printf("  ");           
```

before `free(p->next);` in `moveDir()`



##### problem 6: display welcome page instead of the lost game page after losing game

**reason**：`lostGame()` internally called in  `welcome2game()` , leading to the previous game to failed to exit

**solution**: define `int gameover` in `header.h()` to give sign of losing game (=1) or not (=0)

revise judging functions

```C
void hitWall()
{
    if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
    {
        gameover = 1;
        lostGame();
    }
}

void biteSelf()
{
    snake* self = head->next;
    while (self != NULL)
    {
        if ((head->x == self->x) && (head->y == self->y))
        {
            gameover = 1;
            lostGame();
            return;
        }
        self = self->next;
    }
}
```

use `gameover` to control loop in `KeyControl`

```C
void keyControl()
{
    while (!gameover)   // break until game end
    {
       ...//detect keys
    }
}
```

and other relative changes

##### problem 7: Timer not resetting for multiple playthroughs

add `startTimer()` in the `startGame()` function

#####  

##### problem 8: Windows console size unpleasing (Too long or Too small)

solution: add `system("mode con cols=110 lines=40")` in the `main()` function to initialize the size of console.

------

#### OPTIMIZATING OPTIONS

1. Add ending cases : for example, display endgame result on the endgame page (eg. Game Over: You've hit the wall ! )

2. Add game levels: levels for certain ranges of the score.

3. Set Font Size: beautify pages

   

