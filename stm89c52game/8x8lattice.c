#include "8x8lattice.h"
/*
void hc595Write(unsigned char writeVal)
{
	unsigned char i;
	ST_CP=0;
	for(i=0; i<8; i++)
	{
		SH_CP=0;
		DS=((writeVal<<i)&0x80)?1:0;
		SH_CP=1;
	}
	ST_CP=1;
}*/

void hc595Write(unsigned char dat)
{
	unsigned char a;
	SRCLK=0;
	reRCLK=0;
	for(a=0;a<8;a++)
	{
		SER=dat>>7;
		dat<<=1;

		SRCLK=1;
		_nop_();
		_nop_();
		SRCLK=0;	
	}

	reRCLK=1;
	_nop_();
	_nop_();
	reRCLK=0;
}

//--定义要使用的IO口--//
#define COMMONPORTS		P0

//--列选通控制--//
unsigned char code TAB[8]  = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

void hc238Write(unsigned char writeVal)
{
	COMMONPORTS	= TAB[writeVal];
	/*switch(writeVal)
	{
		case 0: hc238EN=1;hc238A=0;hc238B=0;hc238C=0;break;
		case 1: hc238EN=1;hc238A=1;hc238B=0;hc238C=0;break;
		case 2: hc238EN=1;hc238A=0;hc238B=1;hc238C=0;break;
		case 3: hc238EN=1;hc238A=1;hc238B=1;hc238C=0;break;
		case 4: hc238EN=1;hc238A=0;hc238B=0;hc238C=1;break;
		case 5: hc238EN=1;hc238A=1;hc238B=0;hc238C=1;break;
		case 6: hc238EN=1;hc238A=0;hc238B=1;hc238C=1;break;
		case 7: hc238EN=1;hc238A=1;hc238B=1;hc238C=1;break;
		default: hc238EN=0; break;	
	}*/

}

void drawPoint(unsigned char x, unsigned char y)
{  	
	hc238Write(y);
	hc595Write(0x00);
	hc595Write((1<<x));
	
	
}

void scanDisplay(unsigned char *pbuff)
{
	unsigned char i=0;
	hc595Write(0x00);
	for(i=0; i<8; i++)
	{	
		hc238Write(i);
		hc595Write(pbuff[i]);
		
		hc595Write(0x00);
	}
}


