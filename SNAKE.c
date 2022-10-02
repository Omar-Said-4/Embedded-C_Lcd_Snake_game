/*
 * SNAKE.c
 *
 *  Created on: Sep 25, 2022
 *      Author: Omar Said
 *      Description: The source file of the Snake.
 */
#include"STD_TYPES.h"
#include"SNAKE.h"
#include"DFS.h"
#include"LCD_INTERFACE.h"
extern snake snk;
extern body *snk_body[36];


void SNK_VidInitialise()
{
	/*Initializing the snake position and length*/
	snk.length=1;
	snk.head.col=1;
	snk.head.row=0;
	snk.head.pixlr=3;
	snk.head.pixlc=3;
	snk.tail='\0';
	snk_body[0]=&(snk.head);
    snk.head.newcola=false;
    snk.head.newcolb=false;
    snk.head.newcolu=false;
	snk.head.newcold=false;
	snk.head.pti=1;
}

void SNK_VidMoveHeadRight()
{

	/*Moving snake head to the right and checking if it passed by a new column different from the previous one*/
	 if(snk_body[0]->pixlc==0)
	 {
		 if(snk_body[0]->col<15){
		 snk_body[0]->pixlc=4;
		 snk_body[0]->col++;
		 snk.head.newcola=true;
		 snk.head.newcolb=false;
		 snk.head.newcolu=false;
		 snk.head.newcold=false;
		 snk.head.pti=(snk.head.pti+1)%8;
		 if(snk.head.pti==0)
			 snk.head.pti=1;
		 }
		 else
			 snk_body[0]->pixlc=6;
	 }
	 else
	 {
		 snk_body[0]->pixlc--;
	 }

 }
void SNK_VidMoveHeadLeft()
{

	/*Moving snake head to the left and checking if it passed by a new column different from the previous one*/
	 if(snk_body[0]->pixlc==4)
	 {
		 if(snk_body[0]->col>0){
		 snk_body[0]->pixlc=0;
		 snk_body[0]->col--;
		 snk.head.pti=(snk.head.pti+1)%8;
		 if(snk.head.pti==0)
		   snk.head.pti=1;
		 snk.head.newcolb=true;
		 snk.head.newcola=false;
		 snk.head.newcolu=false;
		 snk.head.newcold=false;
		 }
		 else
			 snk_body[0]->pixlc=6;
	 }
	 else
	 {
		 snk_body[0]->pixlc++;
	 }

 }
void SNK_VidMoveHeadUp()
{
	/*Moving snake head to the right and checking if it passed by a new row different from the previous one*/

	 if(snk_body[0]->pixlr==0)
	 {
		 if(snk_body[0]->row==1){
		 snk_body[0]->pixlr=7;
		 snk_body[0]->row--;
		 snk.head.pti=(snk.head.pti+1)%8;
		 if(snk.head.pti==0)
		   snk.head.pti=1;
		 snk.head.newcolu=true;
		 snk.head.newcold=false;
		 snk.head.newcola=false;
		 snk.head.newcolb=false;
		 }
		 else
			 snk_body[0]->pixlc=6;
	 }
	 else
	 {
		 snk_body[0]->pixlr--;
	 }

 }
void SNK_VidMoveHeadDown()
{
	/*Moving snake head to the right and checking if it passed by a new row different from the previous one*/

	 if(snk_body[0]->pixlr==7)
	 {
		 if(snk_body[0]->row==0){
		 snk_body[0]->pixlr=0;
		 snk_body[0]->row++;
		 snk.head.pti=(snk.head.pti+1)%8;
		 if(snk.head.pti==0)
		 snk.head.pti=1;
		 snk.head.newcold=true;
		 snk.head.newcola=false;
		 snk.head.newcolb=false;
		 snk.head.newcolu=false;
		 }
		 else
			 snk_body[0]->pixlc=6;
	 }
	 else
	 {
		 snk_body[0]->pixlr++;
	 }

 }
