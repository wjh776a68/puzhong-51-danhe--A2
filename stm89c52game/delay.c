#include "config.h"
/**************************************************************************
******	下面所有延时函数均从软件STC-ISP中获得，以12MHz晶振为时钟源
******	STC-ISP软件下载地址：WWW.STCMCU.COM
**************************************************************************/

//void delayUs(unsigned int i)
//{
//	while(i--)
//		_nop_();
//}

void delay1Ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void delayMs(unsigned int i)
{
	while(i--)
	{
		delay1Ms();
	}
}
