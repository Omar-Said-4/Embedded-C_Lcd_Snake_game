/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : DIO_PRIVATE.h       *****************/
/******** Date	     : 17/9/2022           *****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/

#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H
/*Memory locations for the register the of direction of ports*/
#define   DDRA		*((u8*)0x3A)
#define   DDRB		*((u8*)0x37)
#define   DDRC		*((u8*)0x34)
#define   DDRD		*((u8*)0x31)

/*Memory locations for the register of the output values of ports*/
#define   PORTA     *((u8*)0x3B)
#define   PORTB     *((u8*)0x38)
#define   PORTC     *((u8*)0x35)
#define   PORTD     *((u8*)0x32)

/*Memory locations for the register of the input values of ports*/
#define   PINA      *((volatile u8*)0x39) 
#define   PINB      *((volatile u8*)0x36) 
#define   PINC      *((volatile u8*)0x33) 
#define   PIND      *((volatile u8*)0x30)
#endif 
// volatile keyword prevents processor from caching a value in its register files
