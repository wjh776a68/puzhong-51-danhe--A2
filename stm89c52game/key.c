#include "config.h"

extern enum Dir{up, down, left, right};

//*********Key PIN**********//
/*sbit keyUp		= P3^1;
sbit keyDown 	= P3^0;
sbit keyLeft 	= P3^2;
sbit keyRight 	= P3^3; */
//**************************//

uchar keyVal=right;

 /*
uchar scanKey(void)
{
	
	if(!keyUp)		keyVal=up;
	if(!keyDown)	keyVal=down;
	if(!keyLeft)	keyVal=left;
	if(!keyRight)	keyVal=right;
	return keyVal;
}
 */	 

#define GPIO_KEY P1

sbit keyUp		= P3^1;
sbit keyDown 	= P3^0;
sbit keyLeft 	= P3^2;
sbit keyRight 	= P3^3;

void Delay10ms();   
void KeyDown();		 

unsigned char theKeyValue;
//
unsigned char KeyState;

extern unsigned char n;  
extern void delay (unsigned char m);   //¿ØÖÆÆµÂÊÑÓÊ±    




    
extern unsigned char code music_tab[] ;	 


uchar scanKey(void){
	int sure=1;
	

	
	KeyDown();
	if(KeyState)
	{
		KeyState=0;
		if(theKeyValue==1 || theKeyValue==2){//top
			keyVal=down;
		}
		else if(theKeyValue==4 || theKeyValue==8){ //left
			keyVal=right;
		}
		else if(theKeyValue==7 || theKeyValue==11){  //right
			keyVal=left;
		}
		else if(theKeyValue==13 || theKeyValue==14){ //down
			keyVal=up;
		} 
		else{
		  	sure=0;
		}
		 
		 if(sure){
			  	n=200;
	        	while(n--)    Beep=~Beep,delay(music_tab[keyVal]);     
		 }   
		   


	}
	return keyVal;
}



void KeyDown(void)
{
	char a;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)
	{
		Delay10ms();
		if(GPIO_KEY!=0x0f)
		{
			KeyState=1;
			//
			GPIO_KEY=0X0F;
// 			Delay10ms();
			switch(GPIO_KEY)
			{
				case(0X07):	theKeyValue=0;break;
				case(0X0b):	theKeyValue=1;break;
				case(0X0d): theKeyValue=2;break;
				case(0X0e):	theKeyValue=3;break;
//				default:	theKeyValue=17;	
			}
			//
			GPIO_KEY=0XF0;
			Delay10ms();
			switch(GPIO_KEY)
			{
				case(0X70):	theKeyValue=theKeyValue;break;
				case(0Xb0):	theKeyValue=theKeyValue+4;break;
				case(0Xd0): theKeyValue=theKeyValue+8;break;
				case(0Xe0):	theKeyValue=theKeyValue+12;break;
//				default:	KeyValue=17;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 
			{
				Delay10ms();
				a++;
			}
			a=0;
		}
	}
}

void Delay10ms(void)   // 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}
