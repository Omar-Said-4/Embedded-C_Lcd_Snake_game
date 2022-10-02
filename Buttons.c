/*
 * Buttons.c
 *
 *  Created on: Sep 25, 2022
 *      Author: Omar Said
 *      Description: The source file of the buttons pressed to move the snake.
 */

#include"Buttons.h"
#include"DIO_INTERFACE.h"
#include"DFS.h"

void BUT_VidInitialise_Buttons()
{
	/*Initializing the directions of the buttons pins and activating pull up resistors*/
	DIO_VidSetPinDirection(BUT_R,0);
	DIO_VidSetPinValue(BUT_R,1);
	DIO_VidSetPinDirection(BUT_L,0);
	DIO_VidSetPinValue(BUT_L,1);
	DIO_VidSetPinDirection(BUT_U,0);
	DIO_VidSetPinValue(BUT_U,1);
	DIO_VidSetPinDirection(BUT_D,0);
	DIO_VidSetPinValue(BUT_D,1);
	/*In pull up connection
	 * 0-> Button is pressed
	 * 1-> Button is not pressed
	 * */
}
bool BUT_BolMoveRight()
{
	return (DIO_U8GetPinValue(BUT_R)==0);
}
bool BUT_BolMoveLeft()
{
	return (DIO_U8GetPinValue(BUT_L)==0);
}
bool BUT_BolMoveUp()
{
	return (DIO_U8GetPinValue(BUT_U)==0);
}
bool BUT_BolMoveDown()
{
	return (DIO_U8GetPinValue(BUT_D)==0);
}
