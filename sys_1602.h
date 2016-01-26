#ifndef _SYS_1602_
#define _SYS_1602_




void LCDinitial(void);

void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData);

void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData);

void DisplayListCharL(unsigned char X, unsigned char Y, unsigned char *DData, int L) ;

void Display10BitDataL(int value, unsigned char x, unsigned char y, int L); //在1602上显示10位数据

extern unsigned char idata dis[];

#endif
