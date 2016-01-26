#include "STC12C5A60S2.h"
#include "60S2UART.h"
#include <intrins.h>


extern char RecieveCharInUart1; //Uart1���յ��ֽڴ�������
bit RecieveCharFlag1;//�������ģ�
static bit busy;
/**************************************************************
InitUart1()����ʼ�����ڣ��ں�����ʼʱ��ʼ��һ�¾��У�
��ĵط�����Ҫ���κζ�������ʼ���󴮿�û�д򿪣�
�򿪴��ڹ���������д��һ������
**************************************************************/
void InitUart1(unsigned int baud)
{
#if(PARITYBIT == NONE_PARITY)
    SCON = 0x50;    //8-bit variable UAET
#elif(PARITY == 0DD_PARITY)||(PARITYBIT == EVEN_PARITY)||(PARITYBIT == MARK_PARITY)
    SCON = 0xda;    //9-bit variable UART, parity bit initial to 1
#elif(PARITYBIT == SPACE_PARITY)
    SCON == 0xd5;   //9-bit variable UART, parity bit initial to 0
#endif
    
    TMOD = 0x20;    //Set Timer1 as 8-bit auto reload mode
    //TH1 = -(FOSC/12/32/BAUD);   //Set auto-reload vaule
    TH1 = -(FOSC/12/32/baud);   //Set auto-reload value
    TL1 = TH1;
    TR1 = 1;
}

/*********************************************************
�򿪴���
���������OpenUart2( ) ��������"����"������ͬʱֻ�ܴ�һ�����ڡ���Ϊ�������Ŀ����Ҫͬʱ���������ڣ������Ҿ���ôд��
OpenUart1();
OpenUart2();
��ʱ�򲢲���ͬʱ����2�����ڣ���Ϊ�������������ڲ�����һ�����ڹر��ˡ�������ʱ���������Uart2
*********************************************************/
void OpenUart1()
{
    ES = 1;     //�򿪴���1�ж�
    IE2 = 0x00; //�رմ���2�ж�
}

/*----------------------
 * UART interrupt service routine
 * ----------------------*/
void Uart_Isr() interrupt 4 using 1
{
    if(RI)
    {
        RI = 0;
        RecieveCharInUart1 = SBUF;
        RecieveCharFlag1 = 1;
    }
    if(TI)
    {
        TI = 0;     //Clear transmit interrupt flag
        busy = 0;   //Clear transmit busy flag
    }
}

/*---------------------
 ��Uart1���ڷ���һ���ֽڵ�����
 * Send a byte data to UART
 * Input: dat(data to be sent)
 * Output:-
 ---------------------*/
void SendDataFromUart1(BYTE dat)
{
    while(busy);
    busy = 1;
    SBUF = dat;
}

/*-------------------
 ��Uart1���ַ����ˣ�������ȱ��ã����ã�������Ϊ�Ҽ����������û�ɹ�
 * Send a string to UART
 * Input: s(address of string)
 * Output:-
 -------------------*/
void SendStringFromUart1(char *s)
{
    while((*s)!=0x0a)   //Check the end of the string
    {
        SendDataFromUart1(*s); //Send current char and increment string ptr 
        s++;
    }
	SendDataFromUart1(0x0a);
}
