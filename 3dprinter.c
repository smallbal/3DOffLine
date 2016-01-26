/****************************************
外设配置
按钮1：P00   			作用：手动清除已保存的打印状态（清除EEPROM）
按钮2：P01	 			作用：保留


蜂鸣器：P02			 	作用：提示

LED:P03					作用：丢弃保存的打印状态


1602接线
---------------------------------------------------
|LCD-----51   |	LCD-----51   |	LCD------51      |
--------------------------------------------------|
|DB0-----P2.0 |	DB4-----P2.4 |	RW-------P1.1    |
|DB1-----P2.1 |	DB5-----P2.5 |	RS-------P1.2    |
|DB2-----P2.2 |	DB6-----P2.6 |	E--------P1.0    |
|DB3-----P2.3 |	DB7-----P2.7 |	VLCD接1K电阻到GND|
---------------------------------------------------

****************************************/

#include "base_Delay.H"				   //延时
#include "sys_1602.H"					//1602
//#include "sys_keyscan_16.H"			 //矩阵键盘
#include "UART1.h"						 //串口1
#include "UART2.h"						 //串口2
#include "STC12C5A60S2.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h> /* for printf */



sbit plus = P3 ^ 4;	//按键
sbit tab = P3 ^ 5;	//按键
int tab_sec = 1;	//按键切换
unsigned char time_sec2;//串口接收
char RecieveCharInUart1_old;//Uart1上一次接收的字节
char Uart1_CmdBuffer[] ;//Uart1上一次接收的字节，将赋值给这个数组
void get_command(serial_char);	//字符解析

void main()
{
  
  LCDinitial();
  InitUart1();	 //！！！经经，帮我做成可调整串口速率的，eg: InitUart1(115200);
  InitUart2();
  RecieveCharInUart1 = 0;  RecieveCharInUart1_old  = 0;//串口清零
  

  /*开机5s内，清除按钮检测，还没写*/ 
  while (1)
  {
     OpenUart1();
	 if(RecieveCharInUart1 != RecieveCharInUart1_old) //串口有数据更新
	 {
		  get_command(RecieveCharInUart1_old);
		  //process_commands();

		  RecieveCharInUart1_old  = RecieveCharInUart1;//更新
	 }
  }
}

/*需要将串口收到的数据分离成数组，每行元素暂定这种格式
数组位置  0       1    |    2      3    |   4      5    |   6      7   |   8      9       
储存元素  G       1    |    X    92.47  |   Y   143.23  |   Z      2   |   E   3.01373    
意义	  GCode指令集  |	  X坐标		|	 Y坐标  	|     Z坐标    |     挤出长度        


数组位置  10   11      |    12    13     |    14     15   |   16	 17	   |  18  19         |  20   21
储存元素  F   1800.000 |    S     220    |    P      1    |   R     1      |  M   109        |  N	10010
意义      进料速度	   |	马达电压	 |    马达频率 	  |   温度相关	   |  打印机指令集   |  行号

数组位置  22       |      23        |     24        |     25  
储存元素  T        |      I			|     J			|     Q
意义      系统保留 |	  系统保留	|    系统保留 	|   系统保留	    
*/

void get_command(serial_char)	//数据分离，我已疯，你来吧
{
  if(serial_char == '\n'||serial_char == '\r')
  {
   
  }
}




//在数组中搜索特征式诸如X, Y, Z, E, etc特征
char *Code_Value_Position;	//特征式的位置的指针
int code_seen (char code_value)//
{
  Code_Value_Position = strchr(Uart1_CmdBuffer, code_value);
  return (Code_Value_Position != NULL);//特征式位置被找到的话，返回1；没找到，返回0
}



//计算特征式后面跟的那个数值，返回双精度
double code_value()
{
  return (strtod(&Uart1_CmdBuffer[*Code_Value_Position + 1], NULL));
}



void process_commands()
{
  if(code_seen('T'))//指定挤出机，最多可能有4个挤出机，所以如下要根据T值保存成4组，若无T则T=0
  {
	  
  }
  else if(code_seen('G'))
  {
    switch((int)code_value())
    {
    /*case 0: // G0 -> G1
    case 1: //  打印位置，重点
	case 20: // 英寸作为单位，若出现记录1次 
    case 21: // 毫米作为单位，若出现记录1次
    case 29: // G29 Detailed Z-Probe, probes the bed at 3 or more points.
    case 90: // 绝对坐标模式，若出现记录1次
    case 91: // 相对坐标模式，若出现记录1次，这样的话似乎打印不了。。。   */
	}
  }
  else if(code_seen('M'))
  {
    switch( (int)code_value() )
    {
	/*case 82: // 挤出机绝对坐标模式
	case 83: // 挤出机相对坐标模式
    case 104: // 挤出机温度     //case 190: // 挤出机温度 wait for
	case 106: // 风扇转速
    case 140: // 热床温度  */
	}
   }
   else
   {
      	//丢弃
   }
  

}

/*指针的使用
*ai_buf  //ai_buf指向的地址内的值
ai_buf  //ai_buf指向的地址
&ai_buf  //ai_buf本身的地址
ai_buf[100]; //从ai_buf指向的地址开始偏移100个单位的地址内的值	 */ 
