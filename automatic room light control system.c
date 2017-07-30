/*
Port 0: data pins of keypad column
Port 1: Data pins of keypad row
Port 2: data pins for lcd
Port 3: Selection pins for LCD (3.2, 3.6, 3.7) and Output
*/


#include<8051.h>

#define en P1_6
#define rw P1_5
#define rs P1_4
#define T0 P3_4
#define T1 P3_5


void delay(unsigned int);
void lcdinit(void);

void lcdcmd(unsigned char value1);
void lcddata(unsigned char value2);

void clearlcd(void);
unsigned char getchar(void);

void msgdisp(void);
void lcddisp(void);

void init_counter1(void);
void hextoascii(unsigned char convv);

void main()
{
	unsigned int value1=0,value2=0,value3=0,i=0;
	lcdinit();
	clearlcd();
	msgdisp();
	clearlcd();
	init_counter1();
	TR0=1;	
	TR1=1;	
	while(1)
	{
			lcddisp();
			value1=TL0;
			value2=TL1;
			value3=value1-value2;
			hextoascii(value3);
			delay(20);
			clearlcd();
			
		TF0=0;
		TF1=0;
		i++;
	}
}
	
	
void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<1275;j++);
}	
										/* lcd functions */	
void lcdinit(void)
{
	lcdcmd(0x38);
	delay(10);
	lcdcmd(0x0E);
	delay(10);
	lcdcmd(0x01);
	delay(10);
	lcdcmd(0x06);
	delay(10);
}

void lcdcmd(unsigned char value1)
{	
	P2=value1;
	rs = 0;
	rw = 0;
	en = 1;
	delay(1);
	en = 0;	
}

void lcddata(unsigned char value2)
{	
	P2=value2;
	rs = 1;
	rw = 0;
	en = 1;
	delay(1);
	en = 0;	
}
	
void clearlcd(void)
{
	lcdcmd(0x01);
	delay(10);
}													/* Output functions */
void msgdisp(void)
{
	unsigned char tmp[]="WELCOME TO";
	unsigned char tmp1[]="VISITOR COUNTER";
	unsigned char j;
	clearlcd();
	lcdcmd(0x06);
	lcdcmd(0x06);
	lcdcmd(0x06);
	for(j=0;j<=10;j++)
	{
		lcddata(tmp[j]);
		delay(25);
	}
	lcdcmd(0xC0);
	for(j=0;j<=15;j++)
	{
		lcddata(tmp1[j]);
		delay(25);
	}
}
void lcddisp(void)
{
	unsigned int j;
	unsigned char tmp[]="Total people:";
	for(j=0;j<=12;j++)
	{
		lcddata(tmp[j]);
		delay(25);
	}
}
void hextoascii(unsigned char convv)
{
	unsigned char x,d1,d2,d3,a1,a2,a3;
	x=convv/10;
	d1=convv%10;
	d2=x%10;
	d3=x/10;
	a1=d1+48;
	a2=d2+48;
	a3=d3+48;
	lcddata(a3);
	delay(20);
	lcddata(a2);
	delay(20);
	lcddata(a1);
	delay(20);
}
void init_counter1(void)
{
	T0=1;
	T1=1;
	TMOD=0x66;
	TH0=0;
	TL0=0;
	TH1=0;
	TL1=0;
}
