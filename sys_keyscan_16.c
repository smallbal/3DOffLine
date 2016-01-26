/*============================================================

//分为键盘扫描函数key_scan（），不用管。与键盘服务函数key_service（）；
//在key_service中填写按键操作后要进行的动作，
// key_service中对应关系：
//case1->S1	 ，case2->S2，以此类推，case16->S16


// ------------------------ 接线情况-------------------------- //
P0

// ------------------ 中断、定时器的使用 -------------------- //

-

// ----------------------- 修改参数 ------------------------- //

矩阵键盘接口，P0
key_service中对应关系

// ----------------------- 重要参数 ------------------------- //

-

// ----------------------- 功能函数 ------------------------- //

//1.键盘扫描
    key_scan();
//2.键盘服务
    key_service()		


=============================================================*/
#include "STC12C5A60S2.h"
#include<sys_keyscan_16.h>
#include "base_delay.h"

unsigned char idata  key_sec;


void key_scan()
{
  unsigned int temp;
  {	
    P0=0xf7;
    temp=P0;
    temp=temp&0x0f;
    if(temp!=0x0f)
    {
      delayus(10);
      if(temp!=0x0f)
      {	
        temp=P0;
        switch(temp)
        {
          case 0xe7:
               key_sec=1;
               break;

          case 0xd7:
               key_sec=5;
			  
               break;

          case 0xb7:
               key_sec=9;
			  
               break;

          case 0x77:
               key_sec=13;
			   
               break;
         }
         while(temp!=0xf0) 
        {
           temp=P0;
           temp=temp&0xf0;
          
         }
        
      }
    }

    P0=0xfb;
    temp=P0;
    temp=temp&0x0f;
    if(temp!=0x0f)
    {
      delayus(10);
      if(temp!=0x0f)
      {
        temp=P0;
        switch(temp)
        {
          case 0xeb:
               key_sec=2; 
			  
               break;

          case 0xdb:
               key_sec=6;
			  
               break;

          case 0xbb:
               key_sec=10;
               break;

          case 0x7b:
               key_sec=14;
			  
               break;
         }
         while(temp!=0xf0)
         {
           temp=P0;
           temp=temp&0xf0;
          
         }
        
      }
      }

    P0=0xfd;
    temp=P0;
    temp=temp&0x0f;
    if(temp!=0x0f)
    {
      delayus(10);
      if(temp!=0x0f)
      {
        temp=P0;
        switch(temp)
        {
          case 0xed:
               key_sec=3;
			   
               break;

          case 0xdd:
               key_sec=7;
			   
               break;
			   
          case 0xbd:
               key_sec=11;
			   
               break;

          case 0x7d:
               key_sec=15;
		
               break;
         }
        while(temp!=0xf0)
         {
           temp=P0;
           temp=temp&0xf0;
          
         }
         
      }
      }
	P0=0xfe;
    temp=P0;
    temp=temp&0x0f;
    if(temp!=0x0f)
    {
      delayus(10);
      if(temp!=0x0f)
      {
        temp=P0;
        switch(temp)
        {
          case 0xee:
               key_sec=4;
			   
               break;

          case 0xde:
               key_sec=8;
			   
               break;

          case 0xbe:
               key_sec=12;
			   
               break;

          case 0x7e:
               key_sec=16;
			  
               break;
         }
         while(temp!=0xf0)
         {
           temp=P0;
           temp=temp&0xf0;
          
         }
        
      }
    } 
 }
}

void key_service()
{
	switch(key_sec)
	{
		case 1:
			
			break;

		case 2:
			 
			break;
		case 3:
			    
			break;
		case 4:
			   
			break;
		case 5:
			    
			break;
		case 6:
			   
			break;
			
		case 7:
			  
			break;
		case 8:
			   
			break;
		case 9:
			   
			break;
		case 10:
				
			break;
		case 11:
			  
			break;
		case 12:
			
			break;
		case 13:
				
			break;
		case 14:
				
			break;
		case 15:
				 
			break;
		case 16:
				 
			break;
	}
}


		

