/*
 * APPLE.c
 *
 *  Created on: Sep 25, 2022
 *      Author: Omar Said
 *      Description: The source file of the snake game apple which the snake eats.
 */
#include"STD_TYPES.h"
#include"APPLE.h"
#include"DFS.h"
#include"LCD_INTERFACE.h"
#include"Game.h"
extern apple snk_apl;
u8 rd=0;
void APPL_VidInitialise()
{

	/*Initial Position of the apple*/
	snk_apl.col=5;
	snk_apl.row=1;
	snk_apl.pixc=2;
	snk_apl.pixlr=3;
}

void APPL_VidRndPosition()
{

	/*Randomizing Apple  position to a new position*/
	u8 mod=rd%4;
	switch(mod){
	case 0:snk_apl.col=(snk_apl.col+1)%16;
	case 1:snk_apl.row=(snk_apl.row+1)%2;
	case 2:snk_apl.pixc=(snk_apl.pixc+1)%5;
	case 3:snk_apl.pixlr=(snk_apl.pixlr+1)%7;
	break;
	}

	rd++;
}

