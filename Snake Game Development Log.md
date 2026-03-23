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

1. Windows console size unpleasing. (Too long or too small)

   solution: add `system("mode con cols=110 lines=40")` to initialize the size of console.

2. Uncleaned node of the snake.

   solution: print blanks before deleting tail

   ```C
   gotoxy(p->next->x, p->next->y);
   printf("  "); 
   ```

3. 
