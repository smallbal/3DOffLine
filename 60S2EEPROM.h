#ifndef _60S2EEPROM_H_
#define _60S2EEPROM_H_

typedef unsigned char BYTE;
typedef unsigned int WORD;


/*Define ISP/AIP/EEPROM command*/
#define CMD_IDLE    0   //Stand-By
#define CMD_READ    1   //Byte-Read
#define CMD_PROGRAM 2   //Byte-Program
#define CMD_ERASE   3   //Sector-Erase

/*Define ISP/IAP/EEPROM operation const for IAP_CONTR*/
//#define ENABLE_IAP 0x80   //if SYSCLK<30MHz
//#define ENABLE_IAP 0x81   //if SYSCLK<24MHz
//#define ENABLE_IAP 0x82   //if SYSCLK<20MHz
#define ENABLE_IAP 0x83   //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84   //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85   //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86   //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87   //if SYSCLK<1MHz

//Start address for STC12C5A60S2 series EEPROM
#define IAP_ADDRESS 0x0000

void Delay(BYTE n);
void IapIdle();
BYTE IapReadByte(WORD addr);
void IapProgramByte(WORD addr, BYTE dat);
void IapEraseSector(WORD addr);

#endif
