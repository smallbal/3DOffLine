#include "STC12C5A60S2.h"
#include "60S2UART.h"

#define S2RI  0x01
#define S2TI  0x02
#define S2RB8 0x04
#define S2TB8 0x08


char RecieveCharInUart2; //Uart2���յ��ֽڴ�������
static bit busy;
bit RecieveCharFlag2;

void InitUart2()
{
#if (PARITYBIT == NONE_PARITY)
	S2CON = 0x5a;               //8λ�ɱ䲨���� (��У��λ)
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
	S2CON = 0xda;               //9λ�ɱ䲨����,У��λ��ʼΪ1
#elif (PARITYBIT == SPACE_PARITY)
	S2CON = 0xd5;               //9λ�ɱ䲨����,У��λ��ʼΪ0
#endif
	BRT = -(FOSC/32/BAUD);      //���ö��������ʷ����������س�ֵ
	AUXR = 0x14;                //���������ʷ�����������1Tģʽ
	//IE2 = 0x01;                 //ʹ�ܴ���2�ж�
	//EA = 1;                     //�����ж�
}

void OpenUart2()
{
    IE2 = 0x01; //���ܴ���2�ж�
    ES = 0;     //���ﱣ֤��������ͬһʱ��ֻ��һ������
}

void Uart2() interrupt 8 using 1
{
	if (S2CON & S2RI)
	{
		S2CON &= ~S2RI;         //���������ɱ�־
		RecieveCharInUart2 = S2BUF;             //P0��ʾ��������
        RecieveCharFlag2 = 1;
	}
	if (S2CON & S2TI)
	{
		S2CON &= ~S2TI;         //���������ɱ�־
		busy = 0;
	}
}

void SendDataFromUart2(char dat)
{
	while (busy); 
	busy = 1;
	S2BUF = dat;                //��������
}

void SendStringFromUart2(char *s)
{
	while (*s)                  //�ж��ַ���������־
	{
		SendDataFromUart2(*s++);         //�����ַ�
	}
}
