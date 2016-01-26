#include "STC12C5A60S2.h"
#include "60S2UART.h"
#include <intrins.h>


extern char RecieveCharInUart1; //Uart1接收的字节存在这里
bit RecieveCharFlag1;//这个干嘛的？
static bit busy;
/**************************************************************
InitUart1()：初始化串口，在函数开始时初始化一下就行，
别的地方不需要加任何东西，初始化后串口没有打开，
打开串口功能我另外写了一个函数
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
打开串口
这个函数和OpenUart2( ) 的作用是"互锁"，就是同时只能打开一个串口。因为咱这个项目不需要同时打开两个串口，所以我就这么写了
OpenUart1();
OpenUart2();
这时候并不是同时打开了2个串口，因为这俩函数都在内部把另一个串口关闭了。所以这时候仅仅打开了Uart2
*********************************************************/
void OpenUart1()
{
    ES = 1;     //打开串口1中断
    IE2 = 0x00; //关闭串口2中断
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
 从Uart1串口发出一个字节的数据
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
 从Uart1发字符串了，这个你先别用！别用！！！因为我记着这个函数没成功
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
