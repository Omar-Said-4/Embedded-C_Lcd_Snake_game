/*
 * Game.c
 *
 *  Created on: Sep 26, 2022
 *      Author: Omar Said
 *      Description: The source file of the Game.
 */

#include"SNAKE.h"
#include"LCD_INTERFACE.h"
#include"APPLE.h"
#include"Game.h"
#include"BIT_MATH.h"
#include"Buttons.h"
#include<stdlib.h>
#include"DFS.h"
snake snk; /*Game Snake*/
apple snk_apl; /*Game Apple*/
body *snk_body[36]; /*Array of pointer to snake bodies with six extra slots*/
/*patterns of a certain cgram index*/
ptun p0;
ptun p1;
ptun p2;
ptun p3;
ptun p4;
ptun p5;
ptun p6;
ptun p7;
/*variable to check if game is over*/
static bool Game_Over=false;
/*variable to check if game is won*/
static bool win=false;
/*variable to check if apple is eaten and needs to be removed */
static bool remove_apl=false;
/*delay variable depending on delay*/
u8 dl;
/*used to prevent multipe drawing of an apple*/
bool once=false;
/*directions of snake movement*/
directions dir=right;
/*Array of pointer to a certain cgram index 8 patterns*/
ptun *patt2[]={&p0,&p1,&p2,&p3,&p4,&p5,&p6,&p7};
void GM_VidChooseMode()
{
	/*Initial messages*/
	LCD_VidSetCursorPosition(0,0);
	LCD_VidWrite("R4 Easy,L4 Hard");
	LCD_VidSetCursorPosition(1,0);
	LCD_VidWrite("Score 30 to win");
	bool ok=false;
	/*choose mode using right and left buttons*/
	while(!ok)
	{
		if(BUT_BolMoveLeft())
		{
			dl=5;
			ok=true;
		}
		else if(BUT_BolMoveRight())
		{
			dl=200;
			ok=true;
		}
	}
	LCD_VidClear();
}
void GM_VidDrawSnake()
{
	if(!Game_Over){
		bool vis[36]={0}; /*to reduce the inner loop number of execution times*/
		for(int i=0;i<snk.length;i++)
		{
			u8 currr=snk_body[i]->row; /*current row of body part*/
			u8 currc=snk_body[i]->col; /*current column of body part*/
			/*No pattern is initially set yet*/
			p0.pt=0x00;
			p1.pt=0x00;
			p2.pt=0x00;
			p3.pt=0x00;
			p4.pt=0x00;
			p5.pt=0x00;
			p6.pt=0x00;
			p7.pt=0x00;
			if(!vis[i]){
				/*draw all body parts in the same cell*/
				for(int j=0;j<snk.length;j++){
					if(snk_body[j]->row==currr&&snk_body[j]->col==currc){
						/*if this body part moves to anew column or row cell clear he previous cell*/
						if(snk_body[j]->newcola)
						{
							vis[j]=true;
							snk_body[j]->newcola=false;
							LCD_VidSetCursorPosition((u8)snk_body[j]->row,(u8)snk_body[j]->col-1);
							LCD_VidSendData(' ');
						}
						else if(snk_body[j]->newcolb)
						{
							snk_body[j]->newcolb=false;
							LCD_VidSetCursorPosition((u8)snk_body[j]->row,(u8)snk_body[j]->col+1);
							LCD_VidSendData(' ');
						}
						else if(snk_body[j]->newcolu)
						{
							snk_body[j]->newcolu=false;
							LCD_VidSetCursorPosition((u8)snk_body[j]->row+1,(u8)snk_body[j]->col);
							LCD_VidSendData(' ');

						}
						else if(snk_body[j]->newcold)
						{
							snk_body[j]->newcold=false;
							LCD_VidSetCursorPosition((u8)snk_body[j]->row-1,(u8)snk_body[j]->col);
							LCD_VidSendData(' ');
						}

						SET_BIT(patt2[snk_body[j]->pixlr]->pt,snk_body[j]->pixlc);
					}
				}
				/*if the snake and apple are in the same location draw  it*/
				if(snk_apl.col==snk_body[i]->col&&snk_apl.row==snk_body[i]->row&&!remove_apl)
				{
					SET_BIT(patt2[snk_apl.pixlr+1]->pt,snk_apl.pixc);
					once=true;
				}
				/*if snake leaves the common ell with apple without eating it*/
				else if(!remove_apl&&!(snk_apl.col==snk_body[i]->col&&snk_apl.row==snk_body[i]->row))
				{
					once=false;

				}
				/*if apple needs to be removed after being eaten by a snake remove it an randomize its position*/
				else if(remove_apl)
				{
					remove_apl=false;
					APPL_VidRndPosition();

				}
				/*create specific cell pattern and draw it*/
				u8 patt[]={p0.pt,p1.pt,p2.pt,p3.pt,p4.pt,p5.pt,p6.pt,p7.pt};
				LCD_VidCreateChar(patt,snk_body[i]->pti);

				LCD_DisplayCreatedChar(snk_body[i]->pti,snk_body[i]->row,snk_body[i]->col);

			}
		}//of vis[i]
	}
}
void GM_VidInitialise()
{
	/*Initialization sequence is important*/
	GM_VidChooseMode();
	SNK_VidInitialise();
	APPL_VidInitialise();
	GM_VidDrawApple();
}
void GM_vidGameOver()
{

	/*checking if snake has eaten itself
	 * when snake head pixel column is equal to 6 it's a flag that game is over
	 as there is no sixth index.
	 * */
	for(int i=1;i<snk.length;i++)
	{
		if(snk.head.col==snk_body[i]->col&&snk.head.row==snk_body[i]->row&&snk.head.pixlc==snk_body[i]->pixlc&&snk.head.pixlr==snk_body[i]->pixlr)
		{
			snk.head.pixlc=6;
		}
	}
	if(snk.head.pixlc==6&&!Game_Over)
	{
		/*if game is over do the following commands*/
		LCD_VidClear();
		LCD_VidWrite("GAME OVER");
		Gm_VidClearSnake();
		Game_Over=true;
		LCD_VidSetCursorPosition(1,0);
		LCD_VidWrite("Score: ");
		LCD_VidSendNumber(snk.length);
	}
}
void GM_vidGameWin()
{
	/*checking if max_score is reached*/
	if(snk.length==MAX_SCORE&&!Game_Over&&!win)
	{
		LCD_VidClear();
		LCD_VidWrite("Congratulations");
		//_delay_ms(1000);
		Gm_VidClearSnake();
		Game_Over=true;
		win=true;
	}
}
void GM_VidDrawApple()
{
	/*illuminate the apple certain pixel in the cell and draw it*/
	if(!Game_Over){
		u8 patt[]={0,0,0,0,0,0,0,0};
		SET_BIT(patt[snk_apl.pixlr+1],snk_apl.pixc);
		LCD_VidCreateChar(patt,0);
		LCD_DisplayCreatedChar(0,(u8)snk_apl.row,(u8)snk_apl.col);
	}
}
void Gm_VidUpdate()
{

	if(!Game_Over){
		/*Display the snake length*/
		LCD_VidSetCursorPosition(1,0);
		LCD_VidSendNumber(snk.length);
		/*checking if a button is pressed to change snake direction*/
		if(BUT_BolMoveRight())
		{
			dir=right;
		}
		else if(BUT_BolMoveLeft())
		{
			dir=left;;
		}
		else if(BUT_BolMoveUp())
		{
			dir=up;
		}
		else if(BUT_BolMoveDown())
		{
			dir=down;
		}
		/*update each snake body part location and checking if any part passed through a new cell
		 different from the previous one
		 */
		for(int i=snk.length-1;i>0;i--)
		{
			snk_body[i]->pti=snk_body[i-1]->pti;
			u8 prev=snk_body[i]->col;
			snk_body[i]->col=snk_body[i-1]->col;
			if(snk_body[i]->col>prev)
			{
				snk_body[i]->newcola=true;
				snk_body[i]->newcolb=false;
			}
			else if(snk_body[i]->col<prev)
			{
				snk_body[i]->newcolb=true;
				snk_body[i]->newcola=false;
			}
			else
			{
				snk_body[i]->newcolb=false;
				snk_body[i]->newcola=false;
			}
			prev=snk_body[i]->row;
			snk_body[i]->row=snk_body[i-1]->row;
			if(snk_body[i]->row>prev)
			{
				snk_body[i]->newcolu=false;
				snk_body[i]->newcold=true;
			}
			else if(snk_body[i]->row<prev)
			{
				snk_body[i]->newcolu=true;

			}
			else
			{
				snk_body[i]->newcolu=false;
				snk_body[i]->newcold=false;
			}
			snk_body[i]->pixlr=snk_body[i-1]->pixlr;
			snk_body[i]->pixlc=snk_body[i-1]->pixlc;
		}
		/*Moving snake based on the button pressed*/
		switch(dir)
		{
		case right:SNK_VidMoveHeadRight(); break;
		case left:SNK_VidMoveHeadLeft(); break;
		case up: SNK_VidMoveHeadUp();break;
		case down: SNK_VidMoveHeadDown();break;
		}
		/*Drawing the new snake and the apple in the new position if not already drawn*/
		GM_VidDrawSnake();
		if(!once)
			GM_VidDrawApple();
	}
}

void Gm_Videat()
{

	if(!Game_Over){
		/*Check if the snake has eaten the apple*/
		if(snk_apl.col==snk.head.col&&snk_apl.row==snk.head.row&&snk_apl.pixc==snk.head.pixlc&&snk_apl.pixlr+1==snk.head.pixlr)
		{
			/*Remove the apple
			 * Allocate a new body part dynamically
			 * add it to the top of the body parts array*/
			remove_apl=true;
			snk_body[snk.length++]=(body*)malloc(sizeof(body));
			snk.tail=(snk_body[snk.length-1]);
			snk.tail->newcola=false;
			snk.tail->newcolb=false;
			snk.tail->newcolu=false;
			snk.tail->newcold=false;
			/*if the snake has only the head draw the tail in the same cell*/
			if(snk.length-1==1)
			{
				snk.tail->pti=snk.head.pti;
				switch(dir)
				{
				case right:
					if(snk.head.pixlc==4)
					{
						snk.tail->pixlc=snk.head.pixlc;
						if(snk.head.pixlr==0)
						{
							snk.tail->pixlr=snk.head.pixlr+1;
						}
						else
						{
							snk.tail->pixlr=snk.head.pixlr-1;
						}

					}
					else
					{
						snk.tail->pixlc=snk.head.pixlc+1;
						snk.tail->pixlr=snk.head.pixlr;
					}
					snk.tail->col=snk.head.col;
					snk.tail->row=snk.head.row;

					break;
				case left:
					if(snk.head.pixlc==0)
					{
						snk.tail->pixlc=snk.head.pixlc;
						if(snk.head.pixlr==0)
						{
							snk.tail->pixlr=snk.head.pixlr+1;
						}
						else
						{
							snk.tail->pixlr=snk.head.pixlr-1;
						}
					}
					else
					{
						snk.tail->pixlc=snk.head.pixlc-1;
						snk.tail->pixlr=snk.head.pixlr;
					}
					snk.tail->col=snk.head.col;
					snk.tail->row=snk.head.row;
					break;
				case up:
					if(snk.head.pixlr==7)
					{
						snk.tail->pixlr=snk.head.pixlr;

						if(snk.head.pixlc==0)
						{
							snk.tail->pixlc=snk.head.pixlc+1;
						}
						else
						{
							snk.tail->pixlc=snk.head.pixlc-1;
						}
					}
					else
					{
						snk.tail->pixlr=snk.head.pixlr+1;
						snk.tail->pixlc=snk.head.pixlc;
					}
					snk.tail->col=snk.head.col;
					snk.tail->row=snk.head.row;
					break;
				case down:
					if(snk.head.pixlr==0)
					{
						snk.tail->pixlr=snk.head.pixlr;
						if(snk.head.pixlc==0)
						{
							snk.tail->pixlc=snk.head.pixlc+1;
						}
						else
						{
							snk.tail->pixlc=snk.head.pixlc-1;
						}
					}
					else
					{
						snk.tail->pixlr=snk.head.pixlr-1;
						snk.tail->pixlc=snk.head.pixlc;
					}
					snk.tail->row=snk.head.row;
					snk.tail->col=snk.head.col;
					break;
				}

			}
			else
			{
				/*Drawing the snake in the smae cell of the tail*/
				u8 rdiff,cdiff;
				rdiff = snk_body[snk.length-2]->pixlr-snk_body[snk.length-3]->pixlr;
				cdiff = snk_body[snk.length-2]->pixlr-snk_body[snk.length-3]->pixlc;
				snk.tail->pti=snk_body[snk.length-2]->pti;
				if(rdiff==0)
				{

					if(snk_body[snk.length-2]->pixlr==0)
					{
						snk.tail->pixlr=1;
					}
					else if(snk_body[snk.length-2]->pixlr==7)
					{
						snk.tail->pixlr=6;
					}
					else
					{
						snk.tail->pixlr=snk_body[snk.length-2]->pixlr+1;
					}
					snk.tail->pixlc=snk_body[snk.length-2]->pixlc;

					snk.tail->col=snk_body[snk.length-2]->col;
					snk.tail->row=snk_body[snk.length-2]->row;
				}
				else if(cdiff==0)
				{
					if(snk_body[snk.length-2]->pixlc==0)
					{
						snk.tail->pixlc=1;
					}
					else if(snk_body[snk.length-2]->pixlc==4)
					{
						snk.tail->pixlc=3;
					}
					else
					{
						snk.tail->pixlc=snk_body[snk.length-2]->pixlc+1;
					}
					snk.tail->pixlr=snk_body[snk.length-2]->pixlr;
					snk.tail->col=snk_body[snk.length-2]->col;
					snk.tail->row=snk_body[snk.length-2]->row;
				}
			}
		}

	}

}

void Gm_VidClearSnake()
{
	/*Delete all the dynamically allocated snake body parts*/
	for(int i=1;i<snk.length;i++)
	{
		free(snk_body[i]);
	}
}


