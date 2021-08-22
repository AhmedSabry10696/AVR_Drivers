/**
 * @file lcd.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief LCD driver implementation
 * @version 0.1
 * @date 16-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "LCD.h"

#if (8 == DATA_BITS_MODE)

static void LCD_sendCommand(u8 command)
{
	/* out the required command to the data bus D0:D7 */
	DIO_writePort(LCD_DATA_PORT, command);

	/* Instruction Mode RS = 0 */
	DIO_writePin(RS, LOW);

	/* write data to LCD so RW = 0 */
	DIO_writePin(RW, LOW);

	/* Enable LCD E = 1 */
	DIO_writePin(E, HIGH);
	_delay_ms(1);

	/* Disable LCD E = 0 */
	DIO_writePin(E, LOW);
	_delay_ms(1);
}

static void LCD_sendData(u8 data)
{
	/* out the required command to the data bus D0:D7 */
	DIO_writePort(LCD_DATA_PORT, data);

	/* Data Mode RS = 1 */
	DIO_writePin(RS, HIGH);

	/* write data to LCD so RW = 0 */
	DIO_writePin(RW, LOW);

	/* Enable LCD E = 1 */
	DIO_writePin(E, HIGH);
	_delay_ms(1);

	/* Disable LCD E = 0 */
	DIO_writePin(E, LOW);
	_delay_ms(1);
}

void LCD_init(void)
{
	/* wait 20ms after vdd reaches 4.5 volt */
	_delay_ms(20);

	/* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);

	/* Cursor Off */
	LCD_sendCommand(CURSOR_OFF);

	/* Clear Screen */
	LCD_sendCommand(CLEAR_COMMAND);

	_delay_ms(2);
}

#elif (4 == DATA_BITS_MODE)

static void LCD_sendCommand(u8 command)
{
	/* write Most significant four bits on D4:D7 */
	DIO_writePin(D7, READ_BIT(command, 7));
	DIO_writePin(D6, READ_BIT(command, 6));
	DIO_writePin(D5, READ_BIT(command, 5));
	DIO_writePin(D4, READ_BIT(command, 4));

	/* Command mode RS = 0 */
	DIO_writePin(RS, LOW);

	/* Write mode RW = 0 */
	DIO_writePin(RW, LOW);

	/* LCD Enable E = 1 */
	DIO_writePin(E, HIGH);
	_delay_ms(1);

	/* LCD disable E = 0 */
	DIO_writePin(E, LOW);
	_delay_ms(1);

	/* write LOW significant four bits on D4:D7 */
	DIO_writePin(D7, READ_BIT(command, 3));
	DIO_writePin(D6, READ_BIT(command, 2));
	DIO_writePin(D5, READ_BIT(command, 1));
	DIO_writePin(D4, READ_BIT(command, 0));

	/* LCD Enable E = 1 */
	DIO_writePin(E, HIGH);
	_delay_ms(1);

	/* LCD Disable E = 0 */
	DIO_writePin(E, LOW);
	_delay_ms(1);
}

static void LCD_sendData(u8 data)
{
	/* Write most significant 4 bits on D4:D7 */
	DIO_writePin(D7, READ_BIT(data, 7));
	DIO_writePin(D6, READ_BIT(data, 6));
	DIO_writePin(D5, READ_BIT(data, 5));
	DIO_writePin(D4, READ_BIT(data, 4));

	/* Data mode RS = 1 */
	DIO_writePin(RS, HIGH);

	/* LCD enable E = 1 */
	DIO_writePin(E, HIGH);
	_delay_ms(1);

	/* LCD disable E = 0 */
	DIO_writePin(E, LOW);
	_delay_ms(1);

	/* write LOW significant 4 bits on D4:D7 */
	DIO_writePin(D7, READ_BIT(data, 3));
	DIO_writePin(D6, READ_BIT(data, 2));
	DIO_writePin(D5, READ_BIT(data, 1));
	DIO_writePin(D4, READ_BIT(data, 0));

	/* LCD Enable E = 1 */
	DIO_writePin(E, HIGH);
	_delay_ms(1);

	/* LCD disable E = 0 */
	DIO_writePin(E, LOW);
	_delay_ms(1);
}

void LCD_init(void)
{
	/* wait for 15ms after vdd goes to 4.5 volt */
	_delay_ms(15);

	/* initialize LCD in 4-bit mode */
	LCD_sendCommand(FOUR_BITS_DATA_MODE);

	/* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);

	/* cursor off */
	LCD_sendCommand(CURSOR_OFF);

	/* clear screen */
	LCD_sendCommand(CLEAR_COMMAND);

	_delay_ms(2);
}
#endif

void LCD_writeChar(const u8 ch)
{
	LCD_sendData(ch);
}

void LCD_writeString(const u8 *str)
{
	u8 i = 0;

	/* loop till null */
	while (str[i] != 0)
	{
		LCD_writeChar(str[i]);
		i++;
	}
}

void LCD_goTo(u8 row, u8 col)
{
	u8 Address = 0;

	/* first of all calculate the required address */
	switch (row)
	{
	/* row 0 */
	case 0:
		Address = col;
		break;

	/* row 1 */
	case 1:
		Address = col + 0x40;
		break;

	/* row 2 */
	case 2:
		Address = col + 0x14;
		break;

	/* row 3 */
	case 3:
		Address = col + 0x54;
		break;
	}

	/* to set cursor location apply this operation 0x80|address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_writeStringRowCol(u8 row, u8 col, const u8 *str)
{
	/* go to to the required LCD position */
	LCD_goTo(row, col);

	/* display the string */
	LCD_writeString(str);
}

void LCD_writeNum(s32 num)
{
	u8 i = 0, j, digit, str[10];

	/* if number 0 */
	if (0 == num)
	{
		LCD_writeChar('0');
		return;
	}

	/* if the number is negative */
	if (num < 0)
	{
		LCD_writeChar('-');

		/* convert to positive form */
		num = num * -1;
	}

	/* loop on digits of the number */
	while (num > 0)
	{
		digit = (num % 10) + '0';
		str[i] = digit;
		num /= 10;
		i++;
	}

	/* print str on lcd */
	for (j = i; j > 0; j--)
	{
		LCD_writeChar(str[j - 1]);
	}
}

void LCD_writeFloat(f32 num)
{
	s32 left = (s32)num;
	u8 right = (f32)(num - left) * 100;
	LCD_writeNum(left);
	LCD_writeChar('.');
	LCD_writeNum(right);
}

void LCD_writeBinary(u16 num)
{
	s8 i, flag = 0;
	for (i = 15; i >= 0; i--)
	{
		/* check if the bit is 1 or 0 */
		if (1 == ((num >> i) & 0x01))
		{
			LCD_writeChar('1');
			flag = 1;
		}

		/* ignore left side zero's */
		else if (flag == 1)
		{
			LCD_writeChar('0');
		}
	}
}

void LCD_writeHex(u16 num)
{
	u8 nibble4 = ((num & 0xF000) >> 12);
	u8 nibble3 = ((num & 0x0F00) >> 8);
	u8 nibble2 = ((num & 0x00F0) >> 4);
	u8 nibble1 = (num & 0x000F);

	if (nibble4 > 9)
	{
		LCD_writeChar(nibble4 - 10 + 'A');
	}
	else
	{
		LCD_writeChar(nibble4 + '0');
	}

	if (nibble3 > 9)
	{
		LCD_writeChar(nibble3 - 10 + 'A');
	}
	else
	{
		LCD_writeChar(nibble3 + '0');
	}

	if (nibble2 > 9)
	{
		LCD_writeChar(nibble2 - 10 + 'A');
	}
	else
	{
		LCD_writeChar(nibble2 + '0');
	}

	if (nibble1 > 9)
	{
		LCD_writeChar(nibble1 - 10 + 'A');
	}
	else
	{
		LCD_writeChar(nibble1 + '0');
	}
}

void LCD_createChar(const u8 *Pattern, const u8 Location)
{
	u8 i = 0;

	/* send address format of GCRAM */
	LCD_sendCommand(0x40 + (Location * 8));

	for (i = 0; i < 8; i++)
	{
		LCD_sendData(Pattern[i]);
	}

	/* set cursor location to the first index of lcd */
	LCD_sendCommand(SET_CURSOR_LOCATION);
}

void LCD_clear(void)
{
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_clearCells(u8 row, u8 col, u8 cell)
{
	LCD_goTo(row, col);
	for (u8 i = 0; i < cell; i++)
	{
		LCD_writeChar(' ');
	}
	LCD_goTo(row, col);
}
