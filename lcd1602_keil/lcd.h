#ifndef _LCD_H
#define _LCD_H

#include<reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

void Lcd1602_Delay1ms(uint c);   //��� 0us
/*LCD1602д��8λ�����Ӻ���*/
void LcdWriteCom(uchar com);
/*LCD1602д��8λ�����Ӻ���*/	
void LcdWriteData(uchar dat)	;
/*LCD1602��ʼ���ӳ���*/		
void LcdInit();
#endif