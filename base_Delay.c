
/*
1/n指令周期=机器周期=6状态周期=12时钟周期

时钟周期即晶振的单位时间发出的脉冲数，12MHz=12×10的6次方，即每秒发出12000000个脉冲信号，
那么发出一个脉冲的时间就是时钟周期，即1/12微秒。

单周期指令
双周期指令
四周期指令

 */

/*void delay(unsigned int k) //ms倍数
{
  unsigned int i, j;
  for (i = 0; i < k; i++)
  {
    for (j = 0; j < 121; j++)
      ;
  }
}
  */
void delayms(unsigned char ms) //ms倍数
{
  unsigned char i;
  while (ms--)
  {
    for (i = 0; i < 120; i++)
      ;
  }
}

void delayus(unsigned char i) //us倍数
{
  for (i; i > 0; i--)
    ;
}





