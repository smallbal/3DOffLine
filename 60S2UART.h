#ifndef _60S2UART_H_
#define _60S2UART_H_

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 11059200L  //System frequency
#define BAUD 9600       //UART baudrate

/*Define UART parity mode*/
#define NONE_PARITY  0  //None parity
#define ODD_PARITY   1  //Odd parity
#define EVEN_PARITY  2  //Even parity
#define MARK_PARITY  3  //Mark parity
#define SPACE_PARITY 4  //Space parity

#define PARITYBIT NONE_PARITY    //设置为无校验位


/*Uart1's functions*/
void InitUart1();
void OpenUart1();
void SendDataFromUart1(BYTE dat);
void SendStringFromUart1(char *s);

/*Uart2's functions*/
void InitUart2();
void OpenUart2();
void SendDataFromUart2(BYTE dat);
void SendStringFromUart2(char *s);

#endif
