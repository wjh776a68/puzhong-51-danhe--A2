#include "config.h"



//*********Ö÷º¯Êý*************//
void main()
{
	TMOD&=0x0f;   
		  TMOD|=0x01;   
		  TH0=0xd8;TL0=0xef;   
		  IE=0x82;
	initTimer0();	
	while(1){
		startSnake();
	}
}