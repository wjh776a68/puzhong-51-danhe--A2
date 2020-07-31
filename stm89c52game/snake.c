/*********************************************************************
			贪吃蛇源码snake.c
**********************************************************************/
#include "config.h"

/******与蛇相关的结构体定义*************/
static struct Food
{
	unsigned char x;	// 食物的横坐标
	unsigned char y;	// 食物的纵坐标
//	unsigned char yes;
}food;	// 食物结构体

struct Snake
{
	char x[SNAKE_Max_Long];
	char y[SNAKE_Max_Long];
	unsigned char Long;		// 蛇的长度
	unsigned char Life;		// 蛇的生命
//	unsigned char Score;	// 蛇的分数，本例中没使用
	unsigned char Level;	// 蛇的等级
	unsigned char Dir;		// 蛇移动方向
}snake;	// 蛇结构体
/****************************************/

enum Dir{up, down, left, right}; //方向枚举


/***********变量声明***************/
unsigned char DispRAM[8]={0}; // 蛇坐标缓存
unsigned char tCount,n;
unsigned char keyValue=right;
unsigned char speedLevel=25;
extern uchar keyVal; // 来源于key.c

unsigned char code music_tab[] ={   
0x20, 0x18, 0x1C, 0x30, 0x10, 0x40, 0x80, 0x2B //格式为: 操作1，操作2，操作3，操作4，吃豆，撞墙，撞身，    
} ;
/**********************************/

void delay (unsigned char m)   //控制频率延时    
{   
 unsigned i=3*m;   
 while(--i);   
}  

// 用此函数来产生食物最好使蛇的长度不要那么长，蛇越长，点越难找，递归越深
static void createFood()
{
	unsigned char i;
	food.x = rand()%WIDTH;
	food.y = rand()%LENGTH;
	for(i=0; i<snake.Long; i++)
	{
		if(food.x==snake.x[i] && food.y==snake.y[i])
		createFood();	
	}
}

/****************初始化蛇的位置等***********************/
static void initSnake()
{
	/********清除内存数据**********/
	unsigned char i;
	for(i=0; i<SNAKE_Max_Long; i++)
	{
		snake.x[i]=-1;
		snake.y[i]=-1;
	}
	
	/********初始化蛇参数**********/
	snake.Long=2;	// 初始化蛇的长度为两节
	snake.Life=1;	//初始化蛇活着
	snake.Dir=right;
	snake.x[1]=0;
	snake.y[1]=2;
	snake.x[0]=1;
	snake.y[0]=2;
	createFood();
}

/********************刷新界面*******************/
static void drawSnake()
{
	unsigned char i=0;
	for(i=0; i<8; i++) DispRAM[i]=0;
	for(i=0; i<snake.Long; i++)
		DispRAM[snake.y[i]] |= 1<<snake.x[i];
	scanDisplay(DispRAM);
	drawPoint(food.x, food.y);
}

/********************蛇运动坐标刷新*******************/
static void runSnake()
{

	unsigned char i;
	
	// 蛇身体坐标移动，蛇头方向坐标逐渐向蛇尾方向移动
	for(i=snake.Long; i>0; i--)
	{	
		snake.y[i]=snake.y[i-1];
		snake.x[i]=snake.x[i-1];
	}
	
	// 重新获得蛇的头部位置
	switch(snake.Dir)
	{	
		case up:	snake.y[0]-=1; break;
		case down:	snake.y[0]+=1; break;
		case left:	snake.x[0]-=1; break;
		case right: snake.x[0]+=1; break;
		default: break;
	}
	
	// 蛇吃到食物
	if(snake.x[0]==food.x && snake.y[0]==food.y)
	{  	
   		
		n=200;
		while(n--)    Beep=~Beep,delay(music_tab[4]); 


		snake.Long++;
		createFood();
	}
	

}

/*******************方向按键处理***********************/
static void changeDir(unsigned char key)
{
	// 方向按键的规则
	switch(key)
	{
		case up:	if(snake.Dir != down)	snake.Dir=up; 		break;
		case down: 	if(snake.Dir != up)		snake.Dir=down; 	break;
		case left: 	if(snake.Dir != right) 	snake.Dir=left; 	break;
		case right: if(snake.Dir != left) 	snake.Dir=right;	break;
		default: break;
	}
}

/********************启动贪吃蛇游戏（主函数）*********************/
void startSnake()
{
	
	uchar i=0;
	initSnake();
	n=200;
	while(n--)    Beep=~Beep,delay(music_tab[5]); 
	while(snake.Life)
	{
		changeDir(keyValue);
		
		// 蛇运行的速度，由speedLevel决定
		if(tCount >= speedLevel)
		{
			tCount=0;
			runSnake();
		}
			
		/**********************蛇之dead***************************/
		// 限定蛇活动范围，超范围就dead
		if((snake.x[0]>(WIDTH-1)) || (snake.x[0]<0) || (snake.y[0]>(LENGTH-1)) || (snake.y[0]<0))
		{
			
			snake.Life=0;	
			snake.Level=1;
			speedLevel=25;
			keyVal=right;	
		}
		// 蛇自杀检测
		for(i=4; i<=snake.Long; i++)
		{
			
			if(snake.x[i-1]==snake.x[0] && snake.y[i-1]==snake.y[0])
			{  	
				n=200;
			 	while(n--)    Beep=~Beep,delay(music_tab[6]); 
				snake.Life=0;
				snake.Level=1;
				speedLevel=25;
				keyVal=right;	
			}
		}
		/***********************************************************/
		
		// 等级越高速度越快
		if(snake.Long >= SNAKE_Max_Long)
		{
			delayMs(500); // 延一下时
			initSnake();
			speedLevel-=5;
			keyVal=right;			
			if(++snake.Level > 5)
			{
				// 大神，你已经打爆机了，现在从头再来。。。
				n=200;
			 	while(n--)    Beep=~Beep,delay(music_tab[7]);
				snake.Level=1;
				speedLevel=25;						
			}
			tCount=0;
		}
		drawSnake();
	}
}
