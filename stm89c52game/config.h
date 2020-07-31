#ifndef __CONFIG_H
#define __CONFIG_H

#include <reg52.h>
#include <stdlib.h>
#include <intrins.h>
#include "delay.h"
#include "key.h"
#include "8x8lattice.h"
#include "snake.h"
#include "interrupt.h"


typedef unsigned char uchar;
typedef unsigned int uint;
#define FOSC 12000000L


sbit Beep =  P1^5; 


#endif
