/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : LCD_INTERFACE.h     *****************/
/******** Date	     : 17/9/2022           *****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H
#include"STD_TYPES.h"
#include"BIT_MATH.h"
/*Function to write a string to the LCD*/
void LCD_VidWrite(string entry);
/*Function to initialize the LCD*/
void LCD_VidInitialise();
/*Function to send a command to the LCD*/
void LCD_VidSendCommand(u8 cmd);
/*Function to clear the LCD*/
void LCD_VidClear(void);
/*Function to shift the LCD cursor to the right*/
void LCD_VidCursorRight();
/*Function to shift the LCD cursor to the left*/
void LCD_VidCursorLeft();
/*Function to shift the LCD to the right*/
void LCD_VidShiftRight();
/*Function to clear a certain cgram location*/
void LCD_VidCgRamInit(u8 i);
/*Function to shift the LCD to the left*/
void LCD_VidShiftLeft();
/*Function to return the lcd to home mode (command description is in data sheet)*/
void LCD_VidReturnHome();
/*Function to send a character to the LCD or its Ascii code*/
void LCD_VidSendNumber(u16 num);
/*Function to send the cursor position of the LCD*/
void LCD_VidSetCursorPosition(u8 row, u8 coloumn);
/*Function to display a created drawing in a certain cgram index to the LCD specified row and column*/
void LCD_DisplayCreatedChar(u8 cgram_index,u8 row,u8 coloumn);
/*Function to create a certain draw a given pattern in a cgram index */
void LCD_VidCreateChar(u8*pattern, u8 cgram_index);
#endif
