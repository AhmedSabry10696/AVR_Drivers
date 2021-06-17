/**
 * @file LCD.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief LCD driver implementation
 * @version 0.1
 * @date 16-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "LCD_Interface.h"

#if ( 8 == DATA_BITS_MODE)

	static void LCD_SendCommand(u8 command)
	{
		/* out the required command to the data bus D0:D7 */
		DIO_WritePort(LCD_DATA_PORT,command);
	
		/* Instruction Mode RS = 0 */
		DIO_WritePin(RS,LOW);
		
		/* write data to LCD so RW = 0 */
		DIO_WritePin(RW,LOW);
	
		/* Enable LCD E = 1 */
		DIO_WritePin(E,HIGH);
		_delay_ms(1);

		/* Disable LCD E = 0 */
		DIO_WritePin(E,LOW);
		_delay_ms(1);
	}

	static void LCD_SendData(u8 data)
	{
		/* out the required command to the data bus D0:D7 */
		DIO_WritePort(LCD_DATA_PORT,data);
	
		/* Data Mode RS = 1 */
		DIO_WritePin(RS,HIGH);
	
		/* write data to LCD so RW = 0 */
		DIO_WritePin(RW,LOW);
	
		/* Enable LCD E = 1 */
		DIO_WritePin(E,HIGH);
		_delay_ms(1);

		/* Disable LCD E = 0 */
		DIO_WritePin(E,LOW);
		_delay_ms(1);
	}

	void LCD_Init(void)
	{
		/* wait 20ms after vdd reaches 4.5 volt */
		_delay_ms(20);

		/* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
		LCD_SendCommand(TWO_LINE_LCD_Eight_BIT_MODE);
	
		/* Cursor Off */
		LCD_SendCommand(CURSOR_OFF);
	
		/* Clear Screen */
		LCD_SendCommand(CLEAR_COMMAND);

		_delay_ms(2);
	}

#elif (4 == DATA_BITS_MODE)
	
	static void LCD_SendCommand(u8 command)
	{
		/* write Most significant four bits on D4:D7 */
		DIO_WritePin(D7,READ_BIT(command,7));
		DIO_WritePin(D6,READ_BIT(command,6));
		DIO_WritePin(D5,READ_BIT(command,5));
		DIO_WritePin(D4,READ_BIT(command,4));
		
		/* Command mode RS = 0 */
		DIO_WritePin(RS,LOW);

		/* Write mode RW = 0 */
		DIO_WritePin(RW,LOW);

		/* LCD Enable E = 1 */
		DIO_WritePin(E,HIGH);
		_delay_ms(1);
		
		/* LCD disable E = 0 */
		DIO_WritePin(E,LOW);
		_delay_ms(1);
		
		/* write LOW significant four bits on D4:D7 */
		DIO_WritePin(D7,READ_BIT(command,3));
		DIO_WritePin(D6,READ_BIT(command,2));
		DIO_WritePin(D5,READ_BIT(command,1));
		DIO_WritePin(D4,READ_BIT(command,0));
		
		/* LCD Enable E = 1 */
		DIO_WritePin(E,HIGH);
		_delay_ms(1);
		
		/* LCD Disable E = 0 */
		DIO_WritePin(E,LOW);
		_delay_ms(1);
	}

	static void LCD_SendData(u8 data)
	{
		/* Write most significant 4 bits on D4:D7 */
		DIO_WritePin(D7,READ_BIT(data,7));
		DIO_WritePin(D6,READ_BIT(data,6));
		DIO_WritePin(D5,READ_BIT(data,5));
		DIO_WritePin(D4,READ_BIT(data,4));

		/* Data mode RS = 1 */
		DIO_WritePin(RS,HIGH);

		/* LCD enable E = 1 */
		DIO_WritePin(E,HIGH);
		_delay_ms(1);
		
		/* LCD disable E = 0 */
		DIO_WritePin(E,LOW);
		_delay_ms(1);

		/* write LOW significant 4 bits on D4:D7 */
		DIO_WritePin(D7,READ_BIT(data,3));
		DIO_WritePin(D6,READ_BIT(data,2));
		DIO_WritePin(D5,READ_BIT(data,1));
		DIO_WritePin(D4,READ_BIT(data,0));

		/* LCD Enable E = 1 */ 
		DIO_WritePin(E,HIGH);
		_delay_ms(1);

		/* LCD disable E = 0 */
		DIO_WritePin(E,LOW);
		_delay_ms(1);
	}

	void LCD_Init(void)
	{	
		/* wait for 15ms after vdd goes to 4.5 volt */
		_delay_ms(15);

		/* initialize LCD in 4-bit mode */
		LCD_SendCommand(FOUR_BITS_DATA_MODE);
		
		/* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
		LCD_SendCommand(TWO_LINE_LCD_Four_BIT_MODE);
		
		/* cursor off */
		LCD_SendCommand(CURSOR_OFF);
		
		/* clear screen */
		LCD_SendCommand(CLEAR_COMMAND);
		
		_delay_ms(2);
	}
#endif

void LCD_WriteChar(u8 ch)
{
	LCD_SendData(ch);	
}

void LCD_WriteString(u8 *str)
{
	u8 i = 0;

	/* loop till null */
	while (0 != str[i])
	{
		LCD_WriteChar(str[i]);
		i++;
	}
}

void LCD_GoTo(u8 row,u8 col)
{
	u8 Address = 0;
	
	/* first of all calculate the required address */
	switch(row)
	{	
		/* row 0 */
		case 0: 
			Address=col;
			break;
		
		/* row 1 */
		case 1:
			Address=col+0x40;
			break;

		/* row 2 */
		case 2:
			Address=col+0x14;
			break;
		
		/* row 3 */
		case 3:
			Address=col+0x54;
			break;
	}					
	/* to write to a specific address in the LCD 
	 * command 0b10000000+Address */
	LCD_SendCommand(Address | SET_CURSOR_LOCATION); 
}

void LCD_WriteStringRowCol(u8 row,u8 col,u8 *str)
{
	/* go to to the required LCD position */
	LCD_GoTo(row,col);
	
	/* display the string */
	LCD_WriteString(str); 
}

void LCD_WriteNum(s64 num)
{
	u8 i=0,j,digit,str[10];
	
	/* if number 0 */
    if(0 == num)
	{
		LCD_WriteNum('0');
		return;
	}
	
	/* if the number is negative */
	if (num<0)
	{
		LCD_WriteChar('-');
		
		/* convert to positive form */
		num = num * -1;
	}
	
	while(num>0)
	{
		digit  = (num%10)+'0';
		str[i] =  digit;
		num /= 10;
		i++;
	}
	
	/* print str */
	for (j=i;j>0;j--)
	{
		LCD_WriteChar(str[j-1]);
	}
}
	
void LCD_WriteBinary(u8 num)
{
	s8 i;
	for (i=7;i>=0;i--)
	{
		/* check if the bit is 1 or 0 */
		if (1 == ((num>>i)&0x01) )
		{
			LCD_WriteChar('1');
		}
		else
		{
			LCD_WriteChar('0');
		}
	}
}

void LCD_Create_Char(u8 *Pattern,u8 Location)
{
	u8 i=0;

	/* send address format of GCRAM */
	LCD_SendCommand(0x40+(Location*8));
	
	for(i=0;i<8;i++)
	{
		LCD_SendData(Pattern[i]);
	}
	
	LCD_SendCommand(SET_CURSOR_LOCATION);
}

void LCD_Clear(void)
{
	LCD_SendCommand(CLEAR_COMMAND);
}