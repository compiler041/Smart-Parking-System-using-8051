#include <reg51.h>

/* LCD on PORT 2 */
#define lcdport P2

/* Buttons (active LOW) */
sbit senin = P1^0;
sbit senout = P1^1;

/* Motor control (L293D) */
sbit door1_a = P3^4;
sbit door1_b = P3^5;
sbit door2_a = P3^6;
sbit door2_b = P3^7;

/* LCD control */
sbit rs = P3^0;
sbit en = P3^2;

/* LED */
sbit led = P1^7;

unsigned int count = 8;

/* Delay */
void delay(unsigned int x)
{
unsigned int i,j;
for(i=0;i<x;i++)
for(j=0;j<1275;j++);
}

/* LCD COMMAND */
void lcdcmd(unsigned char value)
{
lcdport = value;
rs = 0;
en = 1;
delay(2);
en = 0;
}

/* LCD DATA */
void lcddata(unsigned char value)
{
lcdport = value;
rs = 1;
en = 1;
delay(2);
en = 0;
}

/* LCD STRING */
void lcdstring(char *str)
{
while(*str)
{
lcddata(*str++);
}
}

/* LCD INIT */
void lcdinit()
{
lcdcmd(0x38);
lcdcmd(0x0C);
lcdcmd(0x06);
lcdcmd(0x01);
}

/* DISPLAY COUNT */
void display()
{
lcdcmd(0x8D);
lcddata((count/10)+'0');
lcddata((count%10)+'0');
}

/* ENTRY */
void entry()
{
if(count > 0)
{
count--;
display();

    lcdcmd(0xC0);
    lcdstring("ENTRY OPEN   ");

    door1_a = 1;
    door1_b = 0;
    delay(300);

    door1_a = 0;
    door1_b = 0;
}
}

/* EXIT */
void exitcar()
{
if(count < 8)
{
count++;
display();

    lcdcmd(0xC0);
    lcdstring("EXIT OPEN    ");

    door2_a = 1;
    door2_b = 0;
    delay(300);

    door2_a = 0;
    door2_b = 0;
}
}

/* MAIN */
void main()
{
P1 = 0xFF; // buttons input
led = 1; // LED ON

lcdinit();

lcdcmd(0x80);
lcdstring("CAR PARKING");

lcdcmd(0xC0);
lcdstring("LEFT: ");
display();

while(1)
{
    if(senin == 0)   // ENTRY pressed
    {
        delay(10);
        if(senin == 0)
        {
            entry();
            while(senin == 0);
			delay(10);
        }
    }

    if(senout == 0)  // EXIT pressed
    {
        delay(10);
        if(senout == 0)
        {
            exitcar();
            while(senout == 0);
			delay(10);
        }
    }
}
}




