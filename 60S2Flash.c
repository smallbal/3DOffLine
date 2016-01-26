//#include <reg52.h>
#include "STC12C5A60S2.h"
#include "60S2EEPROM.h"
#include <intrins.h>




void Delay(BYTE n)
{
    WORD x;
    while(n--)
    {
        x = 0;
        while(++x);
    }
}

/*-------------------------
 * Disable ISP/IAP/EEPROM function
 * Make MCU in a safe state
 ------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;  //Close IAP function
}


/*------------------------
 * Read one byte ISP/IAP/EEPROM area
 * input:addr(ISP/IAP/EEPROM address)
 * output: Flash data
 -----------------------*/
BYTE IapReadByte(WORD addr)
{
    BYTE dat;   //Data buffer
    IAP_CONTR = ENABLE_IAP;  //Open IAP function, and set wait time
    IAP_CMD = CMD_READ;     //Set ISP/IAP/EEPROM READ command
    IAP_ADDRL = addr;       //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr>>8;    //Set ISP/IAP/EEPROM address high
    IAP_TRIG = 0x5a;        //Send triger command1(0x51)
    IAP_TRIG = 0xa5;        //Send triger command2(0xa5)
    _nop_();                //MCU will hold here until IAP/IAP/EEPROM operation complete
    dat = IAP_DATA;         //Read ISP/IAP/EEPROM data
    IapIdle();              //Close ISP/IAP/EEPROM function

    return dat;             //Return Flash data
}


/*---------------------
 * Program one byte to ISP/IAP/EEPROM area
 * Input: addr(ISP/IAP/EEPROM address)
 *        dat(ISP/IAP/EEPROM data)
 * output:-
 --------------------*/
void IapProgramByte(WORD addr, BYTE dat)
{
    IAP_CONTR = ENABLE_IAP;     //Open IAP function, and set wait time
    IAP_CMD = CMD_PROGRAM;      //Set ISP/IAP/EEPROM PROGRAM command
    IAP_ADDRL = addr;           //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr>>8;     	//Set ISP/IAP/EEPROM address high
	IAP_DATA = dat;				//Write ISP/IAP/EEPROM data
    IAP_TRIG = 0x5a;            //Send triger command1(0x5a)
    IAP_TRIG = 0xa5;            //Send triger command2(0xa5)
    _nop_();                    //MCU will hold here until ISP/IAP/EEPROM operation complete

    IapIdle();
}

/*------------------
 * Erase one sector area
 * Input: addr(ISP/IAP/EEPROM address)
 * Output:-
 ------------------*/
void IapEraseSector(WORD addr)
{
    IAP_CONTR = ENABLE_IAP;     //Open IAP function, and set wait time
    IAP_CMD = CMD_ERASE;      //Set ISP/IAP/EEPROM ERASE command
    IAP_ADDRL = addr;           //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr>>8;        //Set ISP/IAP/EEPROM address high
    IAP_TRIG = 0x5a;            //Send triger command1(0x5a)
    IAP_TRIG = 0xa5;            //Send triger command2(0xa5)
    _nop_();                    //MCU will hold here until ISP/IAP/EEPROM operation complete

    IapIdle();
}
