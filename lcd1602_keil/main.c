#include "reg52.h"	
#include "lcd.h"
#include "string.h"
#define GPIO_KEY P1
typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;
u8 KeyValue;
u8 counter=0;
u8 code smgduan[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};//��ʾ0~F��ֵ
void delay(u16 i)
{
	while(i--);	
}

u8 KeyDown()
{
	char a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//��ȡ�����Ƿ���
	{
		delay(1000);//��ʱ10ms��������
		if(GPIO_KEY!=0x0f)//�ٴμ������Ƿ���
		{	
			//������
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			//������
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 //��ⰴ�����ּ��
			{
				delay(1000);
				a++;
			}
		}
		return 1;
	}
	else
		return 0;
}
u8 zhengwu(u8 panduan)
{
   if(panduan)
	{
		LcdWriteData('O');
		LcdWriteData('K');
	}
	else
	{
		LcdWriteData('E');
		LcdWriteData('R');
		LcdWriteData('R');
		LcdWriteData('0');
		LcdWriteData('R');
	}
	delay(100000);delay(100000);delay(100000);
	delay(100000);delay(100000);delay(100000);
	delay(100000);delay(100000);delay(100000);
	LcdInit();
	return 1;
}
void main(void)
{
    u8 find;
	u8 answer[32];
	u8 reanswer[32];
	u8 j;//answer�ļ���
	u8 code1[6]={'0','1','2','3','4','5'};
	u8 panduan=1;
	LcdInit();
	while(1)
	{
	while(1)//���빦��
	{
	    find=KeyDown();
		if(find)
			{	
			if(counter==17)
				LcdWriteCom(0x40+0x80);
			if(counter==33)
				{
				LcdInit();
				counter=1;
				}
			if(smgduan[KeyValue]!='B'&&smgduan[KeyValue]!='A')
			{
			LcdWriteData(smgduan[KeyValue]);
			answer[counter]=smgduan[KeyValue];
			counter++;
			}


		    if(smgduan[KeyValue]=='A')//��λ
			{
			u8 i;
			LcdWriteCom(0x04);//ʵ�ʲ��
			LcdWriteData(' ');
			LcdWriteCom(0x06);
			LcdWriteData(' ');
			LcdWriteCom(0x04);
			LcdWriteData(' ');
			LcdWriteCom(0x06);
			counter--;
			if(strlen(answer)>6)
			{
				for(i=0;i<=strlen(answer)-1;i++)
					reanswer[i]=answer[i];
				memset(answer, 0 , sizeof(answer));
				for(i=0;i<=counter-1;i++)
				    answer[i]=reanswer[i];
			}
			}


			if(smgduan[KeyValue]=='B')//���
			{
				LcdInit();
				memset(answer, 0 , sizeof(answer));//���answer
				counter=0;
			}
			if(smgduan[KeyValue]=='D')
			{
				//LcdWriteData(smgduan[strlen(answer)]);
		        //while(1);���
				break;
			}
			}
	}
	//for(j=0;j<=7;j++) LcdWriteData(answer[j]);
	//while(1);

	//�ж�����ֵ���������ù�ϵ
	if(strlen(answer)!=7)//����6λ���뵫��Ҫ��һ����D��ȷ�ϼ�������λ
		panduan=0;
	for(j=0;j<=5;j++)
	{
		if(answer[j]!=code1[j])
		{
		panduan=0;
		}
	}
	LcdInit();
	panduan=zhengwu(panduan);
	counter=0;


	memset(answer, 0 , sizeof(answer));//���answer
	answer[0]='\0';
	}	
				
}
