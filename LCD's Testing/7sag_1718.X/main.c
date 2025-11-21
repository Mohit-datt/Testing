
#include "mcc_generated_files/mcc.h"

//------------------------------------------------------------------------------
#define DECODE_MODE_REG     0x09
#define INTESITY_REG        0x0A
#define SCAN_LIMIT_REG      0x0B
#define SHUTDOWN_REG        0x0C
#define DISPLAY_TEST_REG    0x0F
//------------------------------------------------------------------------------
#define DISABLE_DECODE      0x00
#define DECODE_ALL          0xFF
#define BRIGHTNESS          0x0F
#define SCAN_LOW_NIBBLE     0x03
#define SCAN_ALL_DIGITS     0x07
#define SHUTDOWN_MODE       0x00
#define NORMAL_OPERATION    0x01
#define DISABLE_TEST_MODE   0x00
#define ENABLE_TEST_MODE    0x01
//------------------------------------------------------------------------------
//sbit MAX7219_CS_LOAD at RC0_bit;
//sbit MAX7219_CS_LOAD_DIRECTION at TRISC0_bit;
#define Slave1_SetLow()     LATCbits.LATC6=0
#define Slave1_SetHigh()     LATCbits.LATC6=1

void MAX7219_write(char reg1, char data1)
{
  //MAX7219_CS_LOAD  = 0;
  Slave1_SetLow();
          
  SPI_ExchangeByte(reg1);
  SPI_ExchangeByte(data1);

  //MAX7219_CS_LOAD  = 1;
  Slave1_SetHigh();
}
void MAX7219_init()
{
  //SPI1_init();
    //SPI_Initialize();
    
    MAX7219_write(DECODE_MODE_REG,DECODE_ALL);
    MAX7219_write(INTESITY_REG,BRIGHTNESS);
    MAX7219_write(SCAN_LIMIT_REG,SCAN_ALL_DIGITS);
    MAX7219_write(SHUTDOWN_REG,NORMAL_OPERATION);
    MAX7219_write(DISPLAY_TEST_REG,ENABLE_TEST_MODE);
    MAX7219_write(DISPLAY_TEST_REG,DISABLE_TEST_MODE);
}
void Max7219Print(unsigned long Number, unsigned short NumberOfDigits)
{
  long i;
  for(i=1;Number>0||i-NumberOfDigits<=0;Number/=10,i++)
  {
    //MAX7219_CS_LOAD=0;
    Slave1_SetLow();
    
    SPI_ExchangeByte(i);
    SPI_ExchangeByte(Number%10);
    
    //MAX7219_CS_LOAD=1;
    Slave1_SetHigh();
  }
}

void Max7219DisplayOff()
{
  //MAX7219_CS_LOAD=0;
  Slave1_SetLow();
          
  SPI_ExchangeByte(SHUTDOWN_REG);
  SPI_ExchangeByte(DISABLE_DECODE);
  
  Slave1_SetHigh();
  //MAX7219_CS_LOAD=1;
}

void Max7219DisplayOn()
{
  //MAX7219_CS_LOAD=0;
  Slave1_SetLow();
  SPI_ExchangeByte(SHUTDOWN_REG);
  SPI_ExchangeByte(NORMAL_OPERATION);
  
  Slave1_SetHigh();
  //MAX7219_CS_LOAD=1;
}

void Max7219UpdateIntensity(char OnValue)
{
  if(OnValue>=0&&OnValue<=15)
  {
    //MAX7219_CS_LOAD=0;
    Slave1_SetLow();
    SPI_ExchangeByte(0x0a);
    SPI_ExchangeByte(OnValue);
    
    Slave1_SetHigh();
    //MAX7219_CS_LOAD=1;
  }
}
unsigned long i;
void main(void)
{
    SYSTEM_Initialize();
    SPI_Open(SPI_DEFAULT);
    
    //MAX7219_CS_LOAD = 0;                       // Deselect DAC
    Slave1_SetLow();
    //MAX7219_CS_LOAD_DIRECTION = 0;             // Set CS# pin as Output
    TRISCbits.TRISC6=0;

    MAX7219_init();
    Max7219DisplayOn();
    //__delay_ms(1000);
    while (1)
    {
//        for(i=0;i<99999;i++)//Count From 0 To 99999999 And Display on 8 Seven segemnts
//        {
//            Max7219Print(i+999999,5);
//            __delay_ms(100);
//        }
        Max7219UpdateIntensity(0);
        __delay_ms(100);
        Max7219UpdateIntensity(15);
        __delay_ms(100);
        
    }
    
}
