/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : LCD_CONFIG.h        *****************/
/******** Date	     : 17/9/2022           *****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : Configuration file for LCD pins *****/
 /* and commands             *******************************/
/***********************************************************/
/***********************************************************/

#ifndef LCD_CONIG_H
#define LCD_CONFIG_H
/*LCD Connected Pins*/
#define LCD_PORT 2
#define LCD_RS 3,0
#define LCD_EN 3,1
#define LCD_DNUM 8/*Number of data pins used*/
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
/*Some LCD commands for initialization*/
#define LCD_CLEAR 0x01
#define LCD_CURSOR_LEFT 0x10
#define LCD_CURSOR_RIGHT 0x14
#define SHIFT_LEFT 0x18
#define SHIFT_RIGHT 0x1C
#define RETURN_HOME 0x02
#endif
