#include <at89c5131.h>
#include "lcd.h"		//Header file with LCD interfacing functions
#include "serial.c"	//C file with UART interfacing functions
#include <stdio.h>

unsigned int thous = 20;
unsigned int five = 30;
unsigned int two = 10;
unsigned int one = 10;
unsigned int thous2 = 20;
unsigned int five2 = 30;
unsigned int two2 = 10;
unsigned int one2 = 10;
char str[11] = "";

//Test function definitions

/************************************************
   lcd_test():
	LCD test function that gets called when
	'1' is received from UART
	Prints "LCD Ok" on LCD. After 4 seconds
	LCD is cleared
************************************************/
void print_leftcount (unsigned int cursor,unsigned int left)	
{
	lcd_cmd(cursor);
	//unsigned char strcount[2];
	//sprintf(strcount,"%d",left);
	//lcd_write_string(strcount);
	//unsigned char strcount[2];
	//char strcount[3]={0,0,'\0'};
	int_to_string(left);
		return;
}




void denominations(void)
{
	
	unsigned int cursor2 = 0x80;
	
	transmit_string("reacheddenom");
	lcd_cmd(0x01);
	
	if (thous>0){
			lcd_cmd(cursor2);
		lcd_write_string("2000");
		cursor2=cursor2+5;
	}
	
	
	if (five>0)
		{
			
			if (cursor2>0x80)
			{lcd_write_string(",");}
			
			
			lcd_cmd(cursor2);
			lcd_write_string("500");
			cursor2=cursor2+4;
		}
	
	else 	1;
		if (two>0){
			
			if (cursor2>0x80)
			{lcd_write_string(",");}
			
			
			lcd_cmd(cursor2);
			lcd_write_string("200");
			cursor2=cursor2+4;
	}
	else 		1;
	
	
	if (one>0){
		
					if (cursor2>0x80)
			{lcd_write_string(",");}
			else 1;
		
				lcd_cmd(cursor2);
		lcd_write_string("100");
	}
	else		1;
	
}






void available_count(void)
{
	lcd_cmd(0x01);
	
	transmit_string("dinitiated");
	 lcd_cmd(0x80);
	lcd_write_string("2000:");
	int_to_string(thous, str);
	lcd_write_string(str);
	
	lcd_write_string(" 500:");
	int_to_string(five, str);
	lcd_write_string(str);
	
	lcd_cmd(0xc1);
	lcd_write_string("200:");
	int_to_string(two, str);
	lcd_write_string(str);
	
	lcd_write_string(" 100:");
	int_to_string(one, str);
	lcd_write_string(str);
	
	 msdelay(3000);
	 lcd_cmd(0x01);
		denominations();
	return;
}	 



	
	
	
	
	
	

/************************************************
   led_test():
	LED test code. Update this function
	to test LEDs on P1.7-P1.4 by blinking
	them for a few times.
************************************************/


//Main function
void main(void)
{
	
		unsigned int check =0;
	unsigned int num;
	unsigned int num2;
	unsigned int withdraw;
	unsigned char ch2;
	unsigned char ch1;
	unsigned int tobewithdrawn = 0;
	unsigned char ch=0;
	unsigned int cursor3=0xc0;
	unsigned int trial1;
	unsigned int trial2;
	unsigned int trial3;
	unsigned int trial4;
	unsigned int fivecheck;
	unsigned int thouscheck;

	
	//Call initialization functions
	lcd_init();
	uart_init();
	denominations();
	//These strings will be printed in terminal software
	//transmit_string("************************\r\n");
	//transmit_string("******8051 Tests********\r\n");
	//transmit_string("************************\r\n");
	//transmit_string("Press 1 for LCD test\r\n");
	//transmit_string("Press 2 for LED test\r\n");
	
	while(1)
	{
					check =0;
					tobewithdrawn = 0;
					cursor3=0xc0;
					ch1 = receive_char();		
					num	= ch1 - 48;
					if (ch1=='d')
						{
							available_count();
							//lcd_cmd(0xc1);
							//lcd_write_string("d");
							continue;
						}
					else if (num<=9 && num >=1)
						{
							tobewithdrawn=num;
							lcd_cmd(cursor3);
							lcd_write_char(ch1);
						}
					else 
						{
		
							lcd_cmd(0xc0);
							lcd_write_string(" Invalid input");
							msdelay(2000);
							lcd_cmd(0x01);
							denominations();
							continue;
						}
			
			while(1)
			{
					transmit_string("secondwhile");
					
					cursor3++;
				
					ch2 = receive_char();
				transmit_char(ch2);
					 num2 = ch2 - 48;
				if(ch2==13)
						break;
				
				else if (ch2<='9' && ch2 >='0')
						{
							tobewithdrawn*=10;
							tobewithdrawn=tobewithdrawn+num2;
							lcd_cmd(cursor3);
							lcd_write_char(ch2);
						}
				else 
						{
							check=1;
							lcd_cmd(0xc0);
							lcd_write_string(" Invalid input");
							msdelay(2000);
							lcd_cmd(0x01);
							denominations();
							break;
						}
	
	
			}
			if(check==1) continue;
			
		
			transmit_string("secondwhileend");
			if (tobewithdrawn%100!=0)
				{
							lcd_cmd(0xc0);
							lcd_write_string(" Invalid input");
							msdelay(2000);
							lcd_cmd(0x01);
							denominations();
							continue;
					}
		
			
			
			withdraw=tobewithdrawn;
			//check with 2000
			trial1=withdraw/2000;
					thouscheck=thous;
			if (trial1<=thous)
			{
			thous=thous-trial1;
			withdraw=withdraw%2000;

			}
			else
			{withdraw= withdraw- (2000*thous);
			thous=0;
			}


			//check with 500
			trial2=withdraw/500;
			 fivecheck=five;
			if (trial2<=five)
			{
			five=five-trial2;
			withdraw=withdraw%500;

			}
			else
			{
			withdraw= withdraw- (500*five);
			five=0;}


			//check with 200
			trial3=withdraw/200;
			if (trial3<=two)
			{
			two=two-trial3;
			withdraw=withdraw%200;
			}
			else
			{
			withdraw= withdraw- (200*two);
			two=0;}


			//check with 100
			trial4=withdraw/100;
			if (trial4<=one)
			{
			one=one-trial4;
			withdraw=withdraw%100;

			}
			else
			{
			withdraw= withdraw- (100*one);
			one=0;
			}


			if (withdraw==100 && two>=3 && trial2>=1 && fivecheck>=1 ){
			five=five+1;
			two=two-3;
			withdraw=0;
			}
			if (withdraw==100 && two>=3 && five>=3 && trial1>=1 && thouscheck>=1 ){
			thous++;
			five=five-3;
			two=two-3;
			withdraw=0;
			}
			

			if (withdraw==0)
			{
				lcd_cmd(0xc0);
							lcd_write_string(" Collect Cash");
							msdelay(4000);
							lcd_cmd(0x01);
							denominations();
						thous2 = thous;
						 five2 = five;
						 two2 = two;
						one2 = one;	
			}
			else{
				lcd_cmd(0xc0);
							lcd_write_string(" Try Again");
							msdelay(2000);
							lcd_cmd(0x01);
							denominations();
						 thous = thous2;
						 five = five2;
						 two = two2;
						one = one2;	
			}
				

	
	
	
	}
	
}
