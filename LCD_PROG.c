/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : LCD_PROG.c          *****************/
/******** Date	     : 17/9/2022           *****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_INTERFACE.h"
#include"LCD_CONFIG.h"
#include"LCD_INTERFACE.h"
#include<avr/delay.h>
void LCD_VidSendNumber(u16 num)
{
	u8 x=0;
	u16 rev =0;  /*For storing number in reversed order*/
	if(num==0)   /*Checking if number = 0 print it immediately*/
	{
		LCD_VidSendData(48);
		return;
	}
	while(num)
	{
		/*Reversing number and storing it in rev*/
		rev=(rev*10)+(num%10);
		num/=10;
		x++;
	}
	while(x)
	{
		/*Printing reversed number so that it is the correct num*/
		u8 p=rev%10+48;
		LCD_VidSendData(p);
		rev/=10;
		x--;
	}
}
/*Function to activate enable negative edge*/
void LCD_VidEdge()
{
	DIO_VidSetPinValue(LCD_EN,HIGH);
	_delay_us(2);
	DIO_VidSetPinValue(LCD_EN,LOW);
	_delay_us(5);
}
void LCD_VidInitialise()
{
	DIO_VidSetPinDirection(LCD_RS,OUTPUT);
	DIO_VidSetPinDirection(LCD_EN,OUTPUT);
	_delay_ms(40);
	/*For 8 pin mode*/
#if (LCD_DNUM==8)
	DIO_VidSetPortDirection(LCD_PORT,255);        /*Initialization order: 1-Function set 2-Display on/off 3-Display clear*/
	LCD_VidSendCommand(0x38);
	LCD_VidSendCommand(0x0C);
	/*For 4 pin mode*/
#elif (LCD_DNUM==4)
	DIO_VidSetPinDirection(LCD_PORT,LCD_D4,1);
	DIO_VidSetPinDirection(LCD_PORT,LCD_D5,1);
	DIO_VidSetPinDirection(LCD_PORT,LCD_D6,1);
	DIO_VidSetPinDirection(LCD_PORT,LCD_D7,1);
	LCD_VidSendCommand(0x02);
	LCD_VidSendCommand(0x28);
	//LCD_VidSendCommand(0x80);
	_delay_us(500);
	LCD_VidSendCommand(0x0C);
	//LCD_VidSendCommand(0xF0);
	_delay_us(500);
	//LCD_VidSendCommand(0x00);
	//initialise_once=true;
#endif
	LCD_VidClear();

}
void LCD_VidSendData(u8 val)
{
	/*RS=1*/
	DIO_VidSetPinValue(LCD_RS,1);
	/*RW=0 -> Write operation* or connect to ground/*/
	/*For 8 bits mode*/
#if (LCD_DNUM==8)
	/*Send Character Ascii Code*/
	DIO_VidSetPortValue(LCD_PORT,val);
	/* Enable Sequence */
	DIO_VidSetPinValue(LCD_EN,HIGH);
	_delay_us(2);
	DIO_VidSetPinValue(LCD_EN,LOW);
	_delay_us(5);
	//LCD_VidEdge();
	/*For 4 bits mode*/
#elif (LCD_DNUM==4)
	DIO_VidSetPinValue(LCD_PORT,LCD_D7,GET_BIT(val,7));
	DIO_VidSetPinValue(LCD_PORT,LCD_D6,GET_BIT(val,6));
	DIO_VidSetPinValue(LCD_PORT,LCD_D5,GET_BIT(val,5));
	DIO_VidSetPinValue(LCD_PORT,LCD_D4,GET_BIT(val,4));
	LCD_VidEdge();
	DIO_VidSetPinValue(LCD_PORT,LCD_D7,GET_BIT(val,3));
	DIO_VidSetPinValue(LCD_PORT,LCD_D6,GET_BIT(val,2));
	DIO_VidSetPinValue(LCD_PORT,LCD_D5,GET_BIT(val,1));
	DIO_VidSetPinValue(LCD_PORT,LCD_D4,GET_BIT(val,0));
	LCD_VidEdge();
#endif

}
void LCD_VidSendCommand(u8 cmd)
{
	/*RS=0*/
	DIO_VidSetPinValue(LCD_RS,0);
	/*RW=0 -> Write operation* or connect to ground*/
	/*For 8 bits mode*/
#if (LCD_DNUM==8)
	/*Send Character Ascii Code*/
	DIO_VidSetPortValue(LCD_PORT,cmd);
	/* Enable Sequence */
	DIO_VidSetPinValue(LCD_EN,HIGH);
	_delay_us(2);
	DIO_VidSetPinValue(LCD_EN,LOW);
	_delay_us(5);
	/*For 4 bits mode*/
#elif (LCD_DNUM==4)
	DIO_VidSetPinValue(LCD_PORT,LCD_D7,GET_BIT(cmd,7));
	DIO_VidSetPinValue(LCD_PORT,LCD_D6,GET_BIT(cmd,6));
	DIO_VidSetPinValue(LCD_PORT,LCD_D5,GET_BIT(cmd,5));
	DIO_VidSetPinValue(LCD_PORT,LCD_D4,GET_BIT(cmd,4));
	LCD_VidEdge();
	DIO_VidSetPinValue(LCD_PORT,LCD_D7,GET_BIT(cmd,3));
	DIO_VidSetPinValue(LCD_PORT,LCD_D6,GET_BIT(cmd,2));
	DIO_VidSetPinValue(LCD_PORT,LCD_D5,GET_BIT(cmd,1));
	DIO_VidSetPinValue(LCD_PORT,LCD_D4,GET_BIT(cmd,0));
	LCD_VidEdge();
#endif
}
void LCD_VidWrite(string entry)
{
	/*Sending string character by character to the LCD Display*/
	for (int i = 0; entry[i] != '\0'; ++i)
	{
		LCD_VidSendData(entry[i]);
	}

}
void LCD_VidClear(void)
{
	LCD_VidSendCommand(LCD_CLEAR);
	_delay_ms(2);
}
void LCD_VidCursorLeft()
{
	LCD_VidSendCommand(LCD_CURSOR_LEFT);
}
void LCD_VidCursorRight()
{
	LCD_VidSendCommand(LCD_CURSOR_RIGHT);
}

void LCD_VidShiftLeft()
{
	LCD_VidSendCommand(SHIFT_LEFT);
}
void LCD_VidShiftRight()
{
	LCD_VidSendCommand(SHIFT_RIGHT);
}
void LCD_VidSetCursorPosition(u8 row, u8 coloumn)
{
	u8 address=0x40;
	if(row<2&&row>=0&&coloumn<16&&coloumn>=0)
	{
		address*=row;
		address+=coloumn;
		SET_BIT(address,7);
		LCD_VidSendCommand(address);
	}

}
void LCD_VidCreateChar(u8*pattern, u8 cgram_index)
{
	u8 address=0b01000000;
	if(cgram_index<8)
	{
		address|=(cgram_index*8);
		LCD_VidSendCommand(address);
		for(int i=0;i<8;i++)
			LCD_VidSendData(pattern[i]);

	}
	//LCD_VidReturnHome();
}
void LCD_VidCgRamInit(u8 i)
{
	u8 patt[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	LCD_VidCreateChar(patt,i);

}
void LCD_DisplayCreatedChar(u8 cgram_index,u8 row,u8 coloumn)
{
	LCD_VidSetCursorPosition(row,coloumn);
	LCD_VidSendData(cgram_index);
}
void LCD_VidReturnHome()
{
	LCD_VidSendCommand(RETURN_HOME);
	_delay_ms(2);
}
