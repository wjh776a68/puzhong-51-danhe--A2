#include "config.h"

extern unsigned char tCount;	//来源于snake.c文件
extern unsigned char keyValue;	//来源于snake.c文件
	   

//******定时器0初始化*************//
void initTimer0()
{
	TMOD |= 0x01;
	TL0 = TIMER;
	TH0 = TIMER>>8;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

//******定时器0中断服务处理*************//



void timer0Handle() interrupt 1
{	// 20ms中断



	TL0 = TIMER;
	TH0 = TIMER>>8;
	keyValue=scanKey();
	tCount++;
	
}