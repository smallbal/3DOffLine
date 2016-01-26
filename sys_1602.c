/*============================================================

// ------------------------ �������-------------------------- //
���������
---------------------------------------------------
|LCD-----51   |	LCD-----51   |	LCD------51      |
--------------------------------------------------|
|DB0-----P2.0 |	DB4-----P2.4 |	RW-------P1.1    |
|DB1-----P2.1 |	DB5-----P2.5 |	RS-------P1.2    |
|DB2-----P2.2 |	DB6-----P2.6 |	E--------P1.0    |
|DB3-----P2.3 |	DB7-----P2.7 |	VLCD��1K���赽GND|
---------------------------------------------------

// ------------------ �жϡ���ʱ����ʹ�� -------------------- //
-

// ----------------------- �޸Ĳ��� ------------------------- //

��Ҫ��statement.h�������Ҫ������

// ----------------------- ��Ҫ���� ------------------------- //

-

// ----------------------- ���ܺ��� ------------------------- //

//1.ָ��λ��------һ���ַ�
//X�У�0-15��Y�У�0��1��DData��һλ�ַ���ASCII��
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)

//2.ָ��λ��------һ���ַ�����Ҫ��statement.h��������飩
//X�У�0-15��Y�У�0��1��DData��С��16���ַ���ASCII��
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code

//3.ָ��λ��-------һ���������ַ�����Ҫ��statement.h��������飩
//���룺X�У�0-15��Y�У�0��1��DData��С��16���ַ���ASCII��L��󳤶�
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
#define LCDDataPort  P2   //LCD ���ݶ˿ڡ�ע�������#define
#define Busy    0x80 //���ڼ��LCD״̬���е�Busy��ʶ

/* ----------------------- declaration ------------------------- */
void WriteDataLCD(unsigned char WDLCD); //LCD����
void WriteCommandLCD(unsigned char WCLCD, BuysC); //LCDָ��
unsigned char ReadDataLCD(void);
unsigned char ReadStatusLCD(void);
unsigned char idata dis[6];							//��ʾ����(-511��512)���ַ�����


void LCDinitial(void) ////LCD��ʼ��������һ��
{
  LCDDataPort = 0;
  WriteCommandLCD(0x38, 0); //������ʾģʽ���ã������æ�ź�
  delayms(5);
  WriteCommandLCD(0x38, 0);
  delayms(5);
  WriteCommandLCD(0x38, 0);
  delayms(5);
  WriteCommandLCD(0x38, 1); //��ʾģʽ����,��ʼҪ��ÿ�μ��æ�ź�
  WriteCommandLCD(0x08, 1); //�ر���ʾ
  WriteCommandLCD(0x01, 1); //��ʾ����
  WriteCommandLCD(0x06, 1); // ��ʾ����ƶ�����
  // WriteCommandLCD(0x0F,1); // ��ʾ�����������; ��
  WriteCommandLCD(0x0C, 1); // ��ʾ�����������[; _
  delayms(100);
}

void WriteDataLCD(unsigned char WDLCD) //���ùܣ�LCDд����
{
  ReadStatusLCD(); //���æ
  LCDDataPort = WDLCD;
  LCD_RS = 1;
  LCD_RW = 0;
  LCD_E = 0; //�������ٶ�̫�߿���������С����ʱ
  LCD_E = 0; //��ʱ
  LCD_E = 1;
}

void WriteCommandLCD(unsigned char WCLCD, BuysC) //���ùܣ�LCDдָ��
{
  if (BuysC)
    ReadStatusLCD();
  //������Ҫ���æ��BuysCΪ0ʱ����æ���
  LCDDataPort = WCLCD;
  LCD_RS = 0;
  LCD_RW = 0;
  LCD_E = 0;
  LCD_E = 0;
  LCD_E = 1;
}

unsigned char ReadDataLCD(void) //���ùܣ�LCD������
{
  LCD_RS = 1;
  LCD_RW = 1;
  LCD_E = 0;
  LCD_E = 0;
  LCD_E = 1;
  return (LCDDataPort);
}  

unsigned char ReadStatusLCD(void) //���ùܣ�LCD��״̬
{
  LCDDataPort = 0xFF;
  LCD_RS = 0;
  LCD_RW = 1;
  LCD_E = 0;
  LCD_E = 0;
  LCD_E = 1;
  while (LCDDataPort &Busy)
    ;
  //���æ�ź�
  return (LCDDataPort);
}

void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
  //��ָ��λ����ʾһ���ַ������룺X�У�0-15��Y�У�0��1��DData��һλ�ַ���ASCII��
{
  Y &= 0x1;
  X &= 0xF; //����X���ܴ���15��Y���ܴ���1
  if (Y)
    X |= 0x40;
  //��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
  X |= 0x80; //���ָ����
  WriteCommandLCD(X, 1); //��������
  WriteDataLCD(DData); //������
}

void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData) //��ָ��λ����ʾ����,���룺X�У�0-15��Y�У�0��1��DData��С��16���ַ���ASCII��
{
  unsigned char ListLength;

  ListLength = 0;
  Y &= 0x1;
  X &= 0xF; //����X���ܴ���15��Y���ܴ���1
  while (DData[ListLength] > 0x19)
  //�������ִ�β���˳�
  {
    if (X <= 0xF)
    //X����ӦС��0xF
    {
      DisplayOneChar(X, Y, DData[ListLength]); //��ʾ�����ַ�
      ListLength++;
      X++;
    }
  }
}


//****************************************
//����ת�ַ���
//****************************************
void lcd_printf(unsigned char *s,int temp_data)
{
	if(temp_data<0)
	{
		temp_data=-temp_data;
		*s='-';
	}
	else *s=' ';

  //��λ��
  *++s = temp_data / 100+0x30;
  temp_data = temp_data % 100; //ȡ������
  *++s = temp_data / 10+0x30;
  temp_data = temp_data % 10; //ȡ������
  *++s = temp_data + 0x30;

  /*
  //��λ��
   *++s = temp_data / 10000+0x30;
  temp_data = temp_data % 10000; //ȡ������
   *++s = temp_data / 1000+0x30;
  temp_data = temp_data % 1000; //ȡ������
   *++s = temp_data / 100+0x30;
  temp_data = temp_data % 100; //ȡ������
   *++s = temp_data / 10+0x30;
  temp_data = temp_data % 10; //ȡ������
   *++s = temp_data + 0x30;
   */
}








void DisplayListCharL(unsigned char X, unsigned char Y, unsigned char *DData, int L) //LCD1602��ʾ��������ȣ����룺X�У�0-15��Y�У�0��1��DData��С��16���ַ���ASCII��L��󳤶�
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


void Display10BitDataL(int value, unsigned char x, unsigned char y, int L) //��1602����ʾ10λ����
{
  value /= 64; //ԭ16λת��Ϊ10λ����
  lcd_printf(dis, value); //ת��������ʾ
  DisplayListCharL(x, y, dis, L); //��ʼ�У��У���ʾ���飬��ʾ����
}




