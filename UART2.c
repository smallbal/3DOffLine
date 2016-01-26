#include "STC12C5A60S2.h"
#include "60S2UART.h"

#define S2RI  0x01
#define S2TI  0x02
#define S2RB8 0x04
#define S2TB8 0x08


char RecieveCharInUart2; //Uart2接收的字节存在这里
static bit busy;
bit RecieveCharFlag2;

void InitUart2()
{
#if (PARITYBIT == NONE_PARITY)
	S2CON = 0x5a;               //8位可变波特率 (无校验位)
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
	S2CON = 0xda;               //9位可变波特率,校验位初始为1
#elif (PARITYBIT == SPACE_PARITY)
	S2CON = 0xd5;               //9位可变波特率,校验位初始为0
#endif
	BRT = -(FOSC/32/BAUD);      //设置独立波特率发生器的重载初值
	AUXR = 0x14;                //独立波特率发生器工作在1T模式
	//IE2 = 0x01;                 //使能串口2中断
	//EA = 1;                     //开总中断
}

void OpenUart2()
{
    IE2 = 0x01; //是能串口2中断
    ES = 0;     //这里保证两个串口同一时间只有一个开启
}

void Uart2() interrupt 8 using 1
{
	if (S2CON & S2RI)
	{
		S2CON &= ~S2RI;         //清除接收完成标志
		RecieveCharInUart2 = S2BUF;             //P0显示串口数据
        RecieveCharFlag2 = 1;
	}
	if (S2CON & S2TI)
	{
		S2CON &= ~S2TI;         //清除发送完成标志
		busy = 0;
	}
}

void SendDataFromUart2(char dat)
{
	while (busy); 
	busy = 1;
	S2BUF = dat;                //发送数据
}

void SendStringFromUart2(char *s)
{
	while (*s)                  //判断字符串结束标志
	{
		SendDataFromUart2(*s++);         //发送字符
	}
}
