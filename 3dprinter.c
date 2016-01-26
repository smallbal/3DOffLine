/****************************************
��������
��ť1��P00   			���ã��ֶ�����ѱ���Ĵ�ӡ״̬�����EEPROM��
��ť2��P01	 			���ã�����


��������P02			 	���ã���ʾ

LED:P03					���ã���������Ĵ�ӡ״̬


1602����
---------------------------------------------------
|LCD-----51   |	LCD-----51   |	LCD------51      |
--------------------------------------------------|
|DB0-----P2.0 |	DB4-----P2.4 |	RW-------P1.1    |
|DB1-----P2.1 |	DB5-----P2.5 |	RS-------P1.2    |
|DB2-----P2.2 |	DB6-----P2.6 |	E--------P1.0    |
|DB3-----P2.3 |	DB7-----P2.7 |	VLCD��1K���赽GND|
---------------------------------------------------

****************************************/

#include "base_Delay.H"				   //��ʱ
#include "sys_1602.H"					//1602
//#include "sys_keyscan_16.H"			 //�������
#include "UART1.h"						 //����1
#include "UART2.h"						 //����2
#include "STC12C5A60S2.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h> /* for printf */



sbit plus = P3 ^ 4;	//����
sbit tab = P3 ^ 5;	//����
int tab_sec = 1;	//�����л�
unsigned char time_sec2;//���ڽ���
char RecieveCharInUart1_old;//Uart1��һ�ν��յ��ֽ�
char Uart1_CmdBuffer[] ;//Uart1��һ�ν��յ��ֽڣ�����ֵ���������
void get_command(serial_char);	//�ַ�����

void main()
{
  
  LCDinitial();
  InitUart1();	 //�������������������ɿɵ����������ʵģ�eg: InitUart1(115200);
  InitUart2();
  RecieveCharInUart1 = 0;  RecieveCharInUart1_old  = 0;//��������
  

  /*����5s�ڣ������ť��⣬��ûд*/ 
  while (1)
  {
     OpenUart1();
	 if(RecieveCharInUart1 != RecieveCharInUart1_old) //���������ݸ���
	 {
		  get_command(RecieveCharInUart1_old);
		  //process_commands();

		  RecieveCharInUart1_old  = RecieveCharInUart1;//����
	 }
  }
}

/*��Ҫ�������յ������ݷ�������飬ÿ��Ԫ���ݶ����ָ�ʽ
����λ��  0       1    |    2      3    |   4      5    |   6      7   |   8      9       
����Ԫ��  G       1    |    X    92.47  |   Y   143.23  |   Z      2   |   E   3.01373    
����	  GCodeָ�  |	  X����		|	 Y����  	|     Z����    |     ��������        


����λ��  10   11      |    12    13     |    14     15   |   16	 17	   |  18  19         |  20   21
����Ԫ��  F   1800.000 |    S     220    |    P      1    |   R     1      |  M   109        |  N	10010
����      �����ٶ�	   |	����ѹ	 |    ���Ƶ�� 	  |   �¶����	   |  ��ӡ��ָ�   |  �к�

����λ��  22       |      23        |     24        |     25  
����Ԫ��  T        |      I			|     J			|     Q
����      ϵͳ���� |	  ϵͳ����	|    ϵͳ���� 	|   ϵͳ����	    
*/

void get_command(serial_char)	//���ݷ��룬���ѷ裬������
{
  if(serial_char == '\n'||serial_char == '\r')
  {
   
  }
}




//����������������ʽ����X, Y, Z, E, etc����
char *Code_Value_Position;	//����ʽ��λ�õ�ָ��
int code_seen (char code_value)//
{
  Code_Value_Position = strchr(Uart1_CmdBuffer, code_value);
  return (Code_Value_Position != NULL);//����ʽλ�ñ��ҵ��Ļ�������1��û�ҵ�������0
}



//��������ʽ��������Ǹ���ֵ������˫����
double code_value()
{
  return (strtod(&Uart1_CmdBuffer[*Code_Value_Position + 1], NULL));
}



void process_commands()
{
  if(code_seen('T'))//ָ������������������4������������������Ҫ����Tֵ�����4�飬����T��T=0
  {
	  
  }
  else if(code_seen('G'))
  {
    switch((int)code_value())
    {
    /*case 0: // G0 -> G1
    case 1: //  ��ӡλ�ã��ص�
	case 20: // Ӣ����Ϊ��λ�������ּ�¼1�� 
    case 21: // ������Ϊ��λ�������ּ�¼1��
    case 29: // G29 Detailed Z-Probe, probes the bed at 3 or more points.
    case 90: // ��������ģʽ�������ּ�¼1��
    case 91: // �������ģʽ�������ּ�¼1�Σ������Ļ��ƺ���ӡ���ˡ�����   */
	}
  }
  else if(code_seen('M'))
  {
    switch( (int)code_value() )
    {
	/*case 82: // ��������������ģʽ
	case 83: // �������������ģʽ
    case 104: // �������¶�     //case 190: // �������¶� wait for
	case 106: // ����ת��
    case 140: // �ȴ��¶�  */
	}
   }
   else
   {
      	//����
   }
  

}

/*ָ���ʹ��
*ai_buf  //ai_bufָ��ĵ�ַ�ڵ�ֵ
ai_buf  //ai_bufָ��ĵ�ַ
&ai_buf  //ai_buf����ĵ�ַ
ai_buf[100]; //��ai_bufָ��ĵ�ַ��ʼƫ��100����λ�ĵ�ַ�ڵ�ֵ	 */ 
