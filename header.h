#pragma once
//define constant

/*motion state*/
#define U 1
#define D 2
#define L 3
#define R 4

int score=0, f_score=10; //score, score for each food
//int end;//ending cases ()
int time_use;//time usage
int sleeptime;
int move=R;//motion state
int gameover = 0;//judge if lose the game

/*struture variables*/
typedef struct snakeNode {
	int x;
	int y;
	struct snakeNode* next;
}snake;

snake* head; //head of the snake
snake* food; //food of the snake
snake* p;


void gotoxy(int x, int y);  //set cursor position
int color(int c); //font color
/*void setFontSize();//an opt:change font size*/
void HideCursor(); //hide cursor	
void welcome2game(); //welcome ui
void startGame();//start game
//void level(); an optimization 

void createMap();
void scoreAndTips();
void initSnake(); //initialize snake
void createFood(); 
void biteSelf(); //judge if bite self
void hitWall(); //judge if hit wall

void speedUp(); //press F1 to speed up
void speedDown();//press F2 to speed down
void moveDir(); //direction of movement
void keyControl(); //keyboard control
void startTimer();//start timer when the game starts
int getTime(); //get time during the game

void lostGame(); //lost game ui
//void endGame(); //end game reasons (an opt)
void choose(); //choice after the end
void xpl(); //explanation of the game