
/*
1/nָ������=��������=6״̬����=12ʱ������

ʱ�����ڼ�����ĵ�λʱ�䷢������������12MHz=12��10��6�η�����ÿ�뷢��12000000�������źţ�
��ô����һ�������ʱ�����ʱ�����ڣ���1/12΢�롣

������ָ��
˫����ָ��
������ָ��

 */

/*void delay(unsigned int k) //ms����
{
  unsigned int i, j;
  for (i = 0; i < k; i++)
  {
    for (j = 0; j < 121; j++)
      ;
  }
}
  */
void delayms(unsigned char ms) //ms����
{
  unsigned char i;
  while (ms--)
  {
    for (i = 0; i < 120; i++)
      ;
  }
}

void delayus(unsigned char i) //us����
{
  for (i; i > 0; i--)
    ;
}





