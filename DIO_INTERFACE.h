/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : DIO_INTERFACE.h     *****************/
/******** Date	     : 17/9/2022           *****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/

#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H
#include"STD_TYPES.h"
/* For high logic output (1)*/
#define HIGH 1
/* For low logic output (0)*/
#define LOW 0

/* For making a pin direction output*/
#define OUTPUT 1
/* For making a pin direction input*/
#define INPUT 0
/*Function to set direction of a certain pin in a certain port*/
void DIO_VidSetPinDirection(u8 port, u8 pin, u8 dir);
/*Function to set direction of a port*/
void DIO_VidSetPortDirection(u8 port, u8 dir);
/*Function to set output value of a certain pin in a certain port*/

void DIO_VidSetPinValue(u8 port, u8 pin, u8 val);
/*Function to set value of output a port*/
void DIO_VidSetPortValue(u8 port,u8 val);
/*Function to get value a certain pin in a certain port*/
u8 DIO_U8GetPinValue(u8 port, u8 pin);
/*Function to toggle value of a certain pin in a certain port*/
void DIO_VidTogglePinValue(u8 port,u8 pin);

#endif
