#ifndef _SYS_1602_
#define _SYS_1602_




void LCDinitial(void);

void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData);

void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData);

void DisplayListCharL(unsigned char X, unsigned char Y, unsigned char *DData, int L) ;

void Display10BitDataL(int value, unsigned char x, unsigned char y, int L); //��1602����ʾ10λ����

extern unsigned char idata dis[];

#endif
