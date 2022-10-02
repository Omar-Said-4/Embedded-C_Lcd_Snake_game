/*
 * DFS.c
 *
 *  Created on: Sep 25, 2022
 *      Author: Omar Said
 *      Description: header file containing the definitions for the basic structures and enums in the game.
 */

#ifndef DFS_H
#define DFS_H
#include"STD_TYPES.h"
/* Defining buttons (port,pin) */
#define BUT_R  1,0
#define BUT_L  1,1
#define BUT_U  1,2
#define BUT_D  1,3
/*max snake length*/
#define MAX_SCORE 30
/* A struct with access for each bit of the pattern of each cgram index*/
typedef struct 
{
	u8 b0 :1;
	u8 b1 :1;
	u8 b2 :1;
	u8 b3 :1;
	u8 b4 :1;
	u8 b5 :1;
	u8 b6 :1;
	u8 b7 :1;
}pattern;
/* A defined enum for directions*/
typedef enum{
	right,
	left,
	up,
	down
}directions;
/*A defined union with access for each bit and the whole8-bits together of the pattern of each cgram index*/
typedef union
{
	pattern ptst;
	u8 pt;
}ptun;
/*a defined enum for the index of each row in each cgram index*/
typedef enum
{
	zero,
	one,
	two,
	three,
	four,
	five,
	six,
	seven
}ptindex;
/*a defined struct for each snake body part*/
typedef struct
{
	u8 row :4;    /*Snake body part row of 4 bits only*/
	u8 col :4;    /*Snake body part column of 4 bits only*/
	u8 pixlr :4;  /*Snake body part row of pixel in position of 4 bits only*/
	u8 pixlc :4;  /*Snake body part column of pixel in position of 4 bits only*/
	bool newcola; /*check if the body part passed by a new column on the right to its previous position*/
	bool newcolb; /*check if the body part passed by a new column on the left to its previous position*/
	bool newcolu; /*check if the body part passed by a new row above its previous position*/
	bool newcold; /*check if the body part passed by a new column below its previous position*/
	ptindex pti;  /*cgram index to draw the body part into*/
}body;
/*a struct for the snake*/
typedef struct 
{
     u8 length;  /*Snake body length*/
	 body head;  /*Snake head*/
	 body* tail; /*Pointer to the snake tail*/
}snake;
/*a struct for the apple*/
typedef struct
{
	u8 row :4;    /*Apple row of 4 bits only*/
	u8 col :4;    /*Apple column of 4 bits only*/
	u8 pixlr :4;  /*Apple row of pixel in position of 4 bits only*/
	u8 pixc :4;   /*Apple column of pixel in position of 4 bits only*/
}apple;
#endif
