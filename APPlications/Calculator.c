#define  F_CPU 8000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "LCD_Interface.h"
#include "Keypad.h"

int main(void)
{
	u8 key,op;
	s32 num1=0,num2=0,result=0;
	u8 num1_f=0,res_f = 0,num2_f=0,invalidop = 0,sign_f= 0,num2_st = 0;
	
	DIO_Init();
	LCD_Init();
	LCD_WriteStringRowCol(0,5,"Calculator");
	LCD_GoTo(1,0);

	while(1)
	{
		key = KEYPAD_GeyKey();

		/* if any key pressed */
		if (key != NO_KEY)
		{
			/* if the pressed key in number (res_f = 1 ignore any pressed numbers)*/
			if (key >='0' && key <='9' && res_f == 0)
			{
				/* display it */
				LCD_WriteChar(key);

				/* get the first operand */
				if (num1_f == 0)
				{
					num1 = num1*10 + key-'0';
				}
				
				/* get the second operand */
				else if (num1_f == 1)
				{
					num2_st = 1;
					num2 = num2*10 + key-'0';
				}
			}

			if(key == '-' && num2_st == 0 && num1_f == 1)
			{
				LCD_WriteChar('-');
				sign_f = 1;
				num2_st = 0;
			}

			/* if the pressed key is operation */
			if ((key == '+' || key == '-' || key == '*' || key == '/'))
			{				
				/* ignore signs while getting second number */
				if (num1_f == 1 || invalidop == 1)
				{
					
				}

				/* first operation */
				else if (res_f == 0)
				{
					op = key;

					/* already got op */
					LCD_WriteChar(key);
					num2_st = 0;
					num1_f = 1;
					num2 = 0;
				}

				/* second operation */ 
				else if (res_f == 1)
				{
					num1 = result;
					num2 = 0;
					/* store operation */	
					op = key;
					/* to get the second number */
					num2_st = 0;
					num1_f = 1;
					
					LCD_Clear();
					LCD_WriteStringRowCol(0,5,"Calculator");
					LCD_GoTo(1,0);
					LCD_WriteNum(num1);
					res_f = 0;

					/* display operation */
					LCD_WriteChar(key);
				}
			}
	
			/* if the pressed key is result */
			if (key == '=')
			{

				if (sign_f == 1)
				{
					num2 = num2 * -1;
					sign_f = 0;
				}
				if (num2_st == 0)
				{
					invalidop =1;
				}
				
				switch(op)
				{
					case '+':
						result = num1 + num2;
						break;
					case '-':
						result = num1 - num2;
						break;
					case '*':
						result = num1 * num2;
						break;
					case '/':
						if(num2 == 0)
							invalidop = 1;
						else
							result = num1/num2;
						break;
				}
				LCD_GoTo(2,0);
				if(invalidop == 1)
				{
					LCD_WriteStringRowCol(2,2,"Invalid Operation");
				}
				else
				{
					LCD_WriteNum(result);
				}
				num1_f = 0;
				res_f = 1;
			}
	
			if (key == 'C')
			{
				num1 = 0,num2=0,result= 0;
				num1_f =0;
				num2_st = 0;
				res_f = 0;
				invalidop = 0;
				sign_f = 0;
				LCD_Clear();
				LCD_WriteStringRowCol(0,5,"Calculator");
				LCD_GoTo(1,0);
			}
		}/* end of no key pressed */
	}/*  end of while 1 */
}/* end of main */