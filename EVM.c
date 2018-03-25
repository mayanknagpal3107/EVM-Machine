#include<avr/io.h>
#include<avr/interrupt.h>
#include"uart.h"
#include"uart.c"
#include<util/delay.h>
#include<compat/deprecated.h>
#include"lcd.h"
#include"lcd.c"
unsigned char EEPROMread(unsigned int iadress)
	{ 
		while(EECR & (1<<EEWE));//for checking *previous data *is stored or not
		EEAR=iadress;// adress from 0 to 511
		EECR |= (1<<EERE);//enable read mode
		return EEDR;// data to read
	}
void EEPROMwrite(unsigned int iadress,unsigned char data)
	{		
		while(EECR & (1<<EEWE));//for checking *previous data *is stored or not
		EEAR=iadress;// adress from 0 to 511
		EEDR=data; // data only in 8 bits i.e from 0-255
		EECR |=(1<<EEMWE);//set EEMWE to one for enabling write
		EECR |=(1<<EEWE);//set EEWE to one
		
	}
void decleration()
	{
		cbi(DDRC,4);
		cbi(DDRC,5);
		cbi(DDRC,6);
		cbi(DDRC,7);
		sbi(DDRC,0);//leds
		sbi(DDRC,1);
		sbi(DDRC,2);
		sbi(DDRC,3);
		sbi(PORTC,4);//switches
		sbi(PORTC,5);
		sbi(PORTC,6);
		sbi(PORTC,7);
		cbi(PORTA,0);
		sbi(PORTA,0);
	}
void main()
	{ 
		unsigned char a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,buff[10]={0},buff1[10]={0},buff2[10]={0},buff3[10]={0};
		uart_init(UART_BAUD_SELECT(9600,F_CPU));
		sei();
		decleration();
		e=EEPROMread(2);
		f=EEPROMread(3);
		g=EEPROMread(4);
		h=EEPROMread(5);
		a=e;
		b=f;
		c=g;
		d=h;
		uart_puts("EVM MACHINE");
		uart_puts("\n\r");
		while(1)
		{ 
		  
			if(bit_is_clear(PINC,4))
			{ 
				a++;
				sbi(PORTC,0);
				uart_puts("BJP=");
				EEPROMwrite(2,a);
				_delay_ms(300);
				e=EEPROMread(2);
				itoa(e,buff,10);
				uart_puts(buff);
				uart_puts("\n\r");
			}
			if(bit_is_clear(PINC,5))
			{ 	
				b++;
				sbi(PORTC,1);
				uart_puts("BSP=");
				EEPROMwrite(3,b);
				_delay_ms(300);
				f=EEPROMread(3);
				itoa(f,buff1,10);
				uart_puts(buff1);
				uart_puts("\n\r");
			}
			if(bit_is_clear(PINC,6))
			{ 
				c++;
				sbi(PORTC,2);
				uart_puts("AAP=");
				EEPROMwrite(4,c);
				_delay_ms(300);
				g=EEPROMread(4);
				itoa(g,buff2,10);
				uart_puts(buff2);
				uart_puts("\n\r");
			}
			if(bit_is_clear(PINC,7))
			{ 
				d++;
				sbi(PORTC,3);
				uart_puts("CONG=");
				EEPROMwrite(5,d);
				_delay_ms(300);
				h=EEPROMread(5);
				itoa(h,buff3,10);
				uart_puts(buff3);
				uart_puts("\n\r");
			}
		 if(bit_is_clear(PINA,0))
			{
				a=0;
				b=0;
				c=0;
				d=0;
				EEPROMwrite(2,a);//reset
				EEPROMwrite(3,b);
				EEPROMwrite(4,c);
				EEPROMwrite(5,d);
				
			}	
		}
	}