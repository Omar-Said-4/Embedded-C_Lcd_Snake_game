/*
 * Buttons.h
 *
 *  Created on: Sep 25, 2022
 *      Author: Omar Said
 *      Description: The header file of the buttons pressed to move the snake.
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_
#include"STD_TYPES.h"
/*Function to initialize the buttons pins*/
void BUT_VidInitialise_Buttons();

/*Function to check if the move_right button is pressed*/
bool BUT_BolMoveRight();

/*Function to check if the move_left button is pressed*/
bool BUT_BolMoveLeft();

/*Function to check if the move_up button is pressed*/
bool BUT_BolMoveUp();

/*Function to check if the move_down button is pressed*/
bool BUT_BolMoveDown();
#endif /* BUTTONS_H_ */
