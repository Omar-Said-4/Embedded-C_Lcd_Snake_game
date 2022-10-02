/*
 * main.c
 *
 *  Created on: Sep 24, 2022
 *      Author: Omar Said
 *      Description: the main source file of the game
 */
#include"STD_TYPES.h"
#include"LCD_INTERFACE.h"
#include<avr/delay.h>
#include"DFS.h"
#include"Game.h"
#include"Snake.h"
#include"Buttons.h"
extern u8 dl; /*Dely depending on game mode*/

void main()
{
	/*Initializing the LCD*/
	LCD_VidInitialise();
	/*Initializing the buttons*/
	BUT_VidInitialise_Buttons();
	/*Initializing the game*/
	GM_VidInitialise();
	while(1)
	{

		/*Checking if the snake has eaten an apple*/
  	 Gm_Videat();
  	 /*Updating the LCD*/
	Gm_VidUpdate();
 	/*Checking if the game is over*/
 	GM_vidGameOver();
 	/*Checking if the game is won*/
  	GM_vidGameWin();
    _delay_ms(dl);
	}
}
