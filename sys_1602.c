/*============================================================

// ------------------------ 接线情况-------------------------- //
接线情况：
---------------------------------------------------
|LCD-----51   |	LCD-----51   |	LCD------51      |
--------------------------------------------------|
|DB0-----P2.0 |	DB4-----P2.4 |	RW-------P1.1    |
|DB1-----P2.1 |	DB5-----P2.5 |	RS-------P1.2    |
|DB2-----P2.2 |	DB6-----P2.6 |	E--------P1.0    |
|DB3-----P2.3 |	DB7-----P2.7 |	VLCD接1K电阻到GND|
---------------------------------------------------

// ------------------ 中断、定时器的使用 -------------------- //
-

// ----------------------- 修改参数 ------------------------- //

需要在statement.h里添加需要的数组

// ----------------------- 重要参数 ------------------------- //

-

// ----------------------- 功能函数 ------------------------- //

//1.指定位置------一个字符
//X列（0-15）Y行（0、1）DData（一位字符或ASCII）
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)

//2.指定位置------一串字符（需要在statement.h里添加数组）
//X列（0-15）Y行（0、1）DData（小于16个字符或ASCII）
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code

//3.指定位置-------一串带长度字符（需要在statement.h里添加数组）
//输入：X列（0-15）Y行（0、1）DData（小于16个字符或ASCII）L最大长度
DisplayListCharL(unsigned char X, unsigned char Y, unsigned char *DData,int L)


=============================================================*/

#include "STC12C5A60S2.h"
#include"base_delay.h"
#include"sys_1602.h"

/* --------------------bit sbit int char ------------------------- */
sbit LCD_RW = P1 ^ 1; //LCD RW
sbit LCD_RS = P1 ^ 2; //LCD RS
sbit LCD_E = P1 ^ 0; //LCD EN


/* ----------------------- Definition ------------------------- */
#define LCDDataPort  P2   //LCD 数据端口。注意必须是#define
#define Busy    0x80 //用于检测LCD状态字中的Busy标识

/* ----------------------- declaration ------------------------- */
void WriteDataLCD(unsigned char WDLCD); //LCD数据
void WriteCommandLCD(unsigned char WCLCD, BuysC); //LCD指令
unsigned char ReadDataLCD(void);
unsigned char ReadStatusLCD(void);
unsigned char idata dis[6];							//显示数字(-511至512)的字符数组


void LCDinitial(void) ////LCD初始化，运行一次
{
  LCDDataPort = 0;
  WriteCommandLCD(0x38, 0); //三次显示模式设置，不检测忙信号
  delayms(5);
  WriteCommandLCD(0x38, 0);
  delayms(5);
  WriteCommandLCD(0x38, 0);
  delayms(5);
  WriteCommandLCD(0x38, 1); //显示模式设置,开始要求每次检测忙信号
  WriteCommandLCD(0x08, 1); //关闭显示
  WriteCommandLCD(0x01, 1); //显示清屏
  WriteCommandLCD(0x06, 1); // 显示光标移动设置
  // WriteCommandLCD(0x0F,1); // 显示开及光标设置; 无
  WriteCommandLCD(0x0C, 1); // 显示开及光标设置[; _
  delayms(100);
}

void WriteDataLCD(unsigned char WDLCD) //不用管，LCD写数据
{
  ReadStatusLCD(); //检测忙
  LCDDataPort = WDLCD;
  LCD_RS = 1;
  LCD_RW = 0;
  LCD_E = 0; //若晶振速度太高可以在这后加小的延时
  LCD_E = 0; //延时
  LCD_E = 1;
}

void WriteCommandLCD(unsigned char WCLCD, BuysC) //不用管，LCD写指令
{
  if (BuysC)
    ReadStatusLCD();
  //根据需要检测忙，BuysC为0时忽略忙检测
  LCDDataPort = WCLCD;
  LCD_RS = 0;
  LCD_RW = 0;
  LCD_E = 0;
  LCD_E = 0;
  LCD_E = 1;
}

unsigned char ReadDataLCD(void) //不用管，LCD读数据
{
  LCD_RS = 1;
  LCD_RW = 1;
  LCD_E = 0;
  LCD_E = 0;
  LCD_E = 1;
  return (LCDDataPort);
}  

unsigned char ReadStatusLCD(void) //不用管，LCD读状态
{
  LCDDataPort = 0xFF;
  LCD_RS = 0;
  LCD_RW = 1;
  LCD_E = 0;
  LCD_E = 0;
  LCD_E = 1;
  while (LCDDataPort &Busy)
    ;
  //检测忙信号
  return (LCDDataPort);
}

void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
  //按指定位置显示一个字符，输入：X列（0-15）Y行（0、1）DData（一位字符或ASCII）
{
  Y &= 0x1;
  X &= 0xF; //限制X不能大于15，Y不能大于1
  if (Y)
    X |= 0x40;
  //当要显示第二行时地址码+0x40;
  X |= 0x80; //算出指令码
  WriteCommandLCD(X, 1); //发命令字
  WriteDataLCD(DData); //发数据
}

void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData) //按指定位置显示数组,输入：X列（0-15）Y行（0、1）DData（小于16个字符或ASCII）
{
  unsigned char ListLength;

  ListLength = 0;
  Y &= 0x1;
  X &= 0xF; //限制X不能大于15，Y不能大于1
  while (DData[ListLength] > 0x19)
  //若到达字串尾则退出
  {
    if (X <= 0xF)
    //X坐标应小于0xF
    {
      DisplayOneChar(X, Y, DData[ListLength]); //显示单个字符
      ListLength++;
      X++;
    }
  }
}


//****************************************
//整数转字符串
//****************************************
void lcd_printf(unsigned char *s,int temp_data)
{
	if(temp_data<0)
	{
		temp_data=-temp_data;
		*s='-';
	}
	else *s=' ';

  //三位数
  *++s = temp_data / 100+0x30;
  temp_data = temp_data % 100; //取余运算
  *++s = temp_data / 10+0x30;
  temp_data = temp_data % 10; //取余运算
  *++s = temp_data + 0x30;

  /*
  //六位数
   *++s = temp_data / 10000+0x30;
  temp_data = temp_data % 10000; //取余运算
   *++s = temp_data / 1000+0x30;
  temp_data = temp_data % 1000; //取余运算
   *++s = temp_data / 100+0x30;
  temp_data = temp_data % 100; //取余运算
   *++s = temp_data / 10+0x30;
  temp_data = temp_data % 10; //取余运算
   *++s = temp_data + 0x30;
   */
}








void DisplayListCharL(unsigned char X, unsigned char Y, unsigned char *DData, int L) //LCD1602显示数组带长度，输入：X列（0-15）Y行（0、1）DData（小于16个字符或ASCII）L最大长度
{
  unsigned char ListLength = 0;
  Y &= 0x1;
  X &= 0xF;
  while (L--)
  {
    DisplayOneChar(X, Y, DData[ListLength]);
    ListLength++;
    X++;
  }
}


void Display10BitDataL(int value, unsigned char x, unsigned char y, int L) //在1602上显示10位数据
{
  value /= 64; //原16位转换为10位数据
  lcd_printf(dis, value); //转换数据显示
  DisplayListCharL(x, y, dis, L); //启始列，行，显示数组，显示长度
}




