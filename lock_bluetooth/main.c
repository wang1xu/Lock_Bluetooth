#include "reg52.h"	
#include "lcd.h"
#include "string.h"
#include "i2c.h"
#define GPIO_KEY P1
sbit dianji=P2^3;
typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;
u8 KeyValue;
u8 counter=0;
u8 answer[32];
u8 find;
u8 lanya=0;//������־λ
u8 code smgduan[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};

void delay1(u16 i)
{
	while(i--);	
}
void init()
{
	TMOD=0x20;
	TH1=0xF3;
	TL1=0xF3;
	TR1=1;
	SCON=0x50;
	PCON=0x80;
	IE=0x90;
}

u8 KeyDown()
{
	char a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//��ȡ�����Ƿ���
	{
		delay1(1000);//��ʱ10ms��������
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
				delay1(1000);
				a++;
			}
			return 	smgduan[KeyValue];
		}
	}
	return '%';
}
void zhengwu(u8 panduan)
{
	LcdInit();
   if(panduan)
	{
		dianji=0;
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
	delay1(100000);delay1(100000);delay1(100000);
	delay1(100000);delay1(100000);delay1(100000);
	dianji=1;
	LcdInit();
}
void mimachushizhishezhi()//�����ʼֵ����
{
	write(1,'0');
	delay1(100);
	write(2,'1');
	delay1(100);
	write(3,'2');
	delay1(100);
	write(4,'3');
	delay1(100);
	write(5,'4');
	delay1(100);
	write(6,'5');
	delay1(100);
}

void main()
{
	u8 reanswer[32];
	u8 code1[6];
	u8 code2[32];
	u8 counter=0;
	u8 panduan=1;
	u8 review=0;//�������ñ�־λ
	u8 repoint=0;//��������У��λ
	u8 result=1;//�������ý��λ
	u8 i;
	LcdInit();
	init();
	//mimachushizhishezhi();//�����ʼֵ����
	for(i=0;i<=5;i++)//�����ȡ
	{
		 code1[i]=read(i+1);
		 delay1(100);
	}
	while(1)
	{
	while(1)
	{	
		if(lanya==0)
			find=KeyDown();
		else
			LcdWriteData(find);
		delay1(100);	
		if(find!='%')
		{
			lanya=0;
			if(find=='A')
			{
				LcdWriteCom(0x04);
				LcdWriteData(' ');
				LcdWriteCom(0x06);
				LcdWriteData(' ');
				LcdWriteCom(0x04);
				LcdWriteData(' ');
				LcdWriteCom(0x06);
				counter--;
				if(strlen(answer)>6)//ȥ�����ȳ���6���Ӱ��
				{
					for(i=0;i<=strlen(answer)-1;i++)
						reanswer[i]=answer[i];
					memset(answer, 0 , sizeof(answer));
					for(i=0;i<=counter-1;i++)
				    	answer[i]=reanswer[i];
				}
			}
			else if(find=='B')
			{
				LcdInit();
				memset(answer, 0 , sizeof(answer));//���answer
				counter=0;
			}
			else if(find=='C')//��������
			{
				if(answer[0]=='*'&&answer[1]=='#'&&answer[2]=='7'&&answer[3]=='9'&&answer[4]=='#'&&answer[5]=='*')
				{
				if(review==0)
				{
					LcdInit();
					counter=0;
					memset(answer, 0 , sizeof(answer));//���answer
					answer[0]='\0';
				}
				review=1;
				}
				else
				{
					LcdInit();
					counter=0;
					memset(answer, 0 , sizeof(answer));//���answer
					answer[0]='\0';
					LcdInit();
					LcdWriteData('N');
					LcdWriteData('O');
					LcdWriteData('T');
					delay1(100000);delay1(100000);delay1(100000);
					delay1(100000);delay1(100000);delay1(100000);
					LcdInit();
				}
			}
			else if(find=='D')
				break;	
			else
		    {
				answer[counter]=find;
				LcdWriteData(answer[counter]);
				counter++;
			}
		}			
	}//�������
	if(review==0)
	{
		if(strlen(answer)!=6)//����6λ���뵫��Ҫ��һ����D��ȷ�ϼ�������λ
			panduan=0;
		for(i=0;i<=5;i++)
		{
			if(answer[i]!=code1[i])
				panduan=0;
		}
		zhengwu(panduan);
		panduan=1;

	}
	else//��������
	{
		if(repoint==0)
		{
			for(i=0;i<=strlen(answer)-1;i++)
				code2[i]=answer[i];
		   repoint=1;
		}
		else
		{
			 for(i=0;i<=strlen(answer)-1;i++)
				{
					if(code2[i]!=answer[i]||strlen(answer)!=6||strlen(code2)!=6)
					{
						result=0;
						break;	
					}	
				}
			 if(result)//���óɹ�
			 {
			 	LcdWriteData('Y');
				LcdWriteData('E');
				LcdWriteData('S');
				for(i=0;i<=5;i++)
				{
					write(i+1,code2[i]);
					delay1(100);
				}
				for(i=0;i<=5;i++)//�����ȡ
				{
		 			code1[i]=read(i+1);
		 			delay1(100);
				}
			 }
			 else//����ʧ��
			 {
			 	 LcdWriteData('N');
				 LcdWriteData('O');
			 }
			 repoint=0;
			 result=1;
			 review=0;
			 memset(code2, 0 , sizeof(code2));//���code2
			 code2[0]='\0';
			 delay1(100000);delay1(100000);delay1(100000);
			 delay1(100000);delay1(100000);delay1(100000);
			 LcdInit();
		}
	
	}//�������ý���
	counter=0;
	memset(answer, 0 , sizeof(answer));//���answer
	answer[0]='\0';
	}
}
void initT() interrupt 4
{
	find=SBUF;
	RI=0;
	SBUF=find;
	while(!TI);
	TI=0;
	lanya=1;	
}