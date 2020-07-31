#ifndef __8X8LATTICE_H
#define __8X8LATTICE_H
#include <reg52.h>
#include <intrins.h>
//=====hc595 引脚定义========
/*sbit DS = P3^3;
sbit SH_CP = P3^4;
sbit ST_CP = P3^5;	  */

sbit SRCLK=P3^6;
sbit reRCLK=P3^5;
sbit SER=P3^4;

//=====hc238 引脚定义========
/*sbit hc238A = P2^0;
sbit hc238B = P2^1;
sbit hc238C = P2^2;
sbit hc238EN = P2^6;   */


void hc595Write(unsigned char writeVal);
void hc238Write(unsigned char writeVal);
void drawPoint(unsigned char x, unsigned char y);
void scanDisplay(unsigned char *pbuff);


#endif
