/*
 * Game.h
 *
 *  Created on: Sep 26, 2022
 *      Author: Omar Said
 *      Description: The header file of the Game.
 */

#ifndef GAME_H_
#define GAME_H_
/*Function to choose game mode*/
void GM_VidChooseMode();
/*Function to draw the snake in a specific position*/
void GM_VidDrawSnake();
/*Function to draw the apple in a specific position*/
void GM_VidDrawApple();
/*Function to initialize the game*/
void GM_VidInitialise();
/*Function to check if the game is over*/
void GM_vidGameOver();
/*Function to update the LCD with the new drawings  of snake and apple*/
void Gm_VidUpdate();
/*Function to check if the player has won the game*/
void GM_vidGameWin();
/*Function to check if the snake has eaten an apple*/
void Gm_Videat();
/*Function to delete any dynamically allocated memory for the snake body parts*/
void Gm_VidClearSnake();
#endif /* GAME_H_ */
