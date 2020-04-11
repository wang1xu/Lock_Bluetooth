#include "i2c.h"
void delay()
{
	uchar a,b;
	for(b=1;b>0;b--)
		for(a=2;a>0;a--);
}
void start()
{
	SDA=1;
	delay();
	SCL=1;
	delay();
	SDA=0;
	delay();
}
void stop()
{
	SDA=0;
	delay();
	SCL=1;
	delay();
	SDA=1;
	delay();
}
void write_8bit(uchar dat)
{
	uchar i,j;
	SCL=0;
	delay();
	for(i=0;i<=7;i++)
	{
		if(dat&0x80)
			SDA=1;
		else
			SDA=0;
		delay();
		dat<<=1;
		SCL=1;
		delay();
		SCL=0;
		delay();
	}
	SDA=1;
	delay();
	SCL=1;
	while(SDA)
	{
		j++;
		if(j>200)
		{
			SCL=0;
			delay();
			return ;
		}	
	}
	SCL=0;
	delay();
}
uchar read_8bit()
{
	uchar dat=0,i;
	SCL=0;
	delay();
	SDA=1;
	delay();
	for(i=0;i<=7;i++)//ÒÆ7Î»£¬´«8Î»
	{
		SCL=1;
		delay();
		dat<<=1;
		dat=SDA|dat;
		delay();
		SCL=0;
		delay();
	}
	return dat;
}
void write(uchar add,uchar dat)
{
	start();
	write_8bit(0xa0);
	write_8bit(add);
	write_8bit(dat);
	stop();
}
uchar read(uchar add)
{
	uchar dat;
	start();
	write_8bit(0xa0);
	write_8bit(add);
	start();
	write_8bit(0xa1);
	dat=read_8bit();
	stop();
	return dat;
}