#ifndef _I2C_H
#define _I2C_H

#include<reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

sbit SDA=P2^0;
sbit SCL=P2^1;

void start();
void stop();
void write_8bit(unsigned char dat);
unsigned char read_8bit();
void write(unsigned char add,unsigned char dat);
unsigned char read(unsigned char add);

#endif