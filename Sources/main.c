#include<reg51.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

sfr lcd_data_port=0xA0;		/* P1 port as data port */
sbit rs=P3^0;			/* Register select pin */
sbit rw=P3^1;			/* Read/Write pin */
sbit en=P3^2;			/* Enable pin */
sbit R0=P1^0;
sbit R1=P1^1;
sbit R2=P1^2;
sbit R3=P1^3;
sbit C0=P1^4;
sbit C1=P1^5;
sbit C2=P1^6;
sbit in1 = P3^3;
sbit in2 = P3^4;
sbit green = P0^0;
sbit red = P0^1;
sbit bt0 = P1^7;
sbit buzz = P0^2;
sbit sw0 = P3^5;

char systemcode[11] = "0000";
char usercode[11] = "";
char erase[10] = "";
int wrong = 0;
int longcode = 0;

void delay(unsigned int count)  /* Function to provide delay Approx 1ms */
{
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<112;j++);
}

void LCD_Command (unsigned char cmd)  /* LCD16x2 command funtion */
{
	lcd_data_port= cmd;
	rs=0;			/* command reg. */
	rw=0;			/* Write operation */
	en=1; 
	delay(1);
	en=0;
	delay(5);
}

void LCD_Char (unsigned char char_data)  /* LCD data write function */
{
	lcd_data_port=char_data;
	rs=1;			/* Data reg.*/
	rw=0;			/* Write operation*/
	en=1;   				
	delay(1);
	en=0;
	delay(5);
}

void LCD_String (unsigned char *str) /* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)  /* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);  /* Call LCD data write */
	}
}

void LCD_String_xy (char row, char pos, char *str)  /* Send string to LCD function */
{
	if (row == 0)
	LCD_Command((pos & 0x0F)|0x80);
	else if (row == 1)
	LCD_Command((pos & 0x0F)|0xC0);
	LCD_String(str);	/* Call LCD string function */
}

void LCD_Init (void)		/* LCD Initialize function */
{	
	delay(20);		/* LCD Power ON Initialization time >15ms */
	LCD_Command (0x38);	/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);	/* Display ON Cursor OFF */
	LCD_Command (0x06);	/* Auto Increment cursor */
	LCD_Command (0x01);	/* clear display */
	LCD_Command (0x80);	/* cursor at home position */
}

void HideChar(void)
{
	delay(500);
	LCD_Command (0x10);
	LCD_String("*");
}
void Open()
{
	in1 = 1;
	in2 = 0;
}
void Close()
{
	in1 = 0;
	in2 = 1;
}
void Stop()
{
	in1 = 0;
	in2 = 0;
}
void buzzer()
{
	if (wrong < 3)
	{
		buzz = 0;
		delay(500);
		buzz = 1;
	}
	else if (wrong < 5)
	{
		buzz = 0;
		delay(10000);
		buzz = 1;
	}
	else if (wrong >=5)
	{
		buzz = 0;
		delay(20000);
		buzz = 1;
	}
	else
	{
		buzz = 0;
		delay(400);
		buzz = 1;
	}
}
void Door()
{
	LCD_Command (0x01);	/* clear display */
	LCD_String("UNLOCKED");
	Open();
	delay(280);
	Stop();
	delay(5000);
	if (sw0!=0)
	{
		LCD_Command (0x01);	/* clear display */
		LCD_String("STILL OPEN");
		while (sw0!=0)
		{
			delay(400);
			buzzer();
		}
	}	
	Close();
	delay(280);
	Stop();
	LCD_Command (0x01);	/* clear display */
	LCD_String("LOCKED");
	delay(2000);
	LCD_Command (0x01);
}
void main()
{
	int mode = 0;
	int i = 1;
	LCD_Init();
	/* initialization of LCD*/

	LCD_String("CE103.N23.MTCL");  /* write string on 1st line of LCD*/
	LCD_Command(0xC0);
	LCD_String("DIGITAL LOCK");  /*write string on 2nd line*/
	delay(1000);
	LCD_Command (0x01);	/* clear display */
	LCD_String("ENTER PASSCODE");
	LCD_Command(0xC0);
	
	
	while(1)
	{
		R0=R1=R2=R3=1;
		R0=0;
		if(C0==0)
		{
			longcode++;
			LCD_String("1");
			Hidechar();
			strcat(usercode,"1");
			while(C0==0);
		}
		R0=R1=R2=R3=1;
		R0=0;
		if(C1==0)
		{
			longcode++;
			LCD_String("2");
			Hidechar();
			strcat(usercode,"2");
			while(C1==0);
		}
		R0=R1=R2=R3=1;
		R0=0;
		if(C2==0)
		{
			longcode++;
			LCD_String("3");
			Hidechar();
			strcat(usercode,"3");
			while(C2==0);
		}
		R0=R1=R2=R3=1;
		R1=0;
		if(C0==0)
		{
			longcode++;
			LCD_String("4");
			Hidechar();
			strcat(usercode,"4");
			while(C0==0);
		}
		R0=R1=R2=R3=1;
		R1=0;
		if(C1==0)
		{
			longcode++;
			LCD_String("5");
			Hidechar();
			strcat(usercode,"5");
			while(C1==0);
		}
		R0=R1=R2=R3=1;
		R1=0;
		if(C2==0)
		{
			longcode++;
			LCD_String("6");
			Hidechar();
			strcat(usercode,"6");
			while(C2==0);
		}
		R0=R1=R2=R3=1;
		R2=0;
		if(C0==0)
		{
			longcode++;
			LCD_String("7");
			Hidechar();
			strcat(usercode,"7");
			while(C0==0);
		}
		R0=R1=R2=R3=1;
		R2=0;
		if(C1==0)
		{
			longcode++;
			LCD_String("8");
			Hidechar();
			strcat(usercode,"8");
			while(C1==0);
		}
		R0=R1=R2=R3=1;
		R2=0;
		if(C2==0)
		{
			longcode++;
			LCD_String("9");
			Hidechar();
			strcat(usercode,"9");
			while(C2==0);
		}
		R0=R1=R2=R3=1;
		R3=0;
		if(C1==0)
		{
			longcode++;
			LCD_String("0");
			Hidechar();
			strcat(usercode,"0");
			while(C1==0);
		}
		if(bt0 == 0)
		{
			mode = 1;
			strcpy(usercode, erase);
			LCD_Command (0x01);	/* clear display */
			LCD_String("LAST PASSCODE");
			LCD_Command(0xC0);
			while (bt0 == 0);
		}
		R0=R1=R2=R3=1;
		R3=0;
		if(C2==0)
		{
			mode = 0;
			longcode = 0;
			strcpy(usercode, erase);
			LCD_Command (0x01);	/* clear display */
			LCD_String("ENTER PASSCODE");
			LCD_Command(0xC0);
			while(C2==0);
		}
		R0=R1=R2=R3=1;
		R3=0;
		if(C0==0)
		{
			if(mode == 0)
			{
				if (strcmp(systemcode,usercode)==0)
				{
					longcode = 0;
					wrong = 0;
					strcpy(usercode, erase);
					LCD_Command (0x01);	/* clear display */
					LCD_String("ACCESS GRANTED");
					green = 0;
					Door();
					green = 1;
					//LCD_Command (0x01);
				}
				else if(strcmp(systemcode,usercode) != 0)
				{
					if (wrong < 5)
					{
						longcode = 0;
						strcpy(usercode, erase);
						wrong = wrong + 1;
						LCD_Command (0x01);	/* clear display */
						LCD_String("ACCESS DENIED");
						buzzer();
						red = 0;
						delay(2000);
						red = 1;
						LCD_Command (0x01);
					}
					else
					{
						longcode = 0;
						strcpy(usercode, erase);
						LCD_Command (0x01);	/* clear display */
						LCD_String("LOCKER DISABLED");
						buzzer();
						red = 0;
						PCON = 0x02;
					}
					
				}
			}
			else if (mode == 1)
			{
				if (strcmp(systemcode,usercode)==0)
				{
					longcode = 0;
					mode = 2;
					strcpy(usercode, erase);
					LCD_Command (0x01);	/* clear display */
					LCD_String("NEW PASSCODE");
					LCD_Command(0xC0);
				}
				else if (strcmp(systemcode,usercode)!=0)
				{
					if(wrong <5)
					{
						longcode = 0;
						wrong = wrong +1;
						strcpy(usercode, erase);
						LCD_Command (0x01);	/* clear display */
						LCD_String("WRONG PASSCODE");
						mode = 0;
						buzzer();
						red = 0;
						delay(2000);
						red = 1;
						LCD_Command (0x01);
					}
					else
					{
						longcode = 0;
						strcpy(usercode, erase);
						LCD_Command (0x01);	/* clear display */
						LCD_String("LOCKER DISABLED");
						buzzer();
						red = 0;
						PCON = 0x02;
					}				
				}
			}
			else if (mode == 2)
			{
				if(strcmp(usercode,erase) ==0)
				{
					longcode = 0;
					strcpy(usercode, erase);
					LCD_Command (0x01);	/* clear display */
					LCD_String("CAN'T BLANK");
					mode = 0;
					red = 0;
					delay(2000);
					red = 1;
					LCD_Command (0x01);
				}
				else if(longcode > 10)
				{
					longcode = 0;
					strcpy(usercode, erase);
					LCD_Command (0x01);	/* clear display */
					LCD_String("MUSTLESSTHAN10");
					mode = 0;
					red = 0;
					delay(2000);
					red = 1;
					LCD_Command (0x01);
				}
				else if (strcmp(usercode,erase) !=0)
				{
					longcode = 0;
					strcpy (systemcode, usercode);
					strcpy (usercode,erase);
					LCD_Command (0x01);	/* clear display */
					LCD_String("SUCCESSFULLY");
					mode = 0;
					green = 0;
					delay(2000);
					green = 1;
					LCD_Command (0x01);
				}
			}
			while(C0==0);
		}
	}
}
