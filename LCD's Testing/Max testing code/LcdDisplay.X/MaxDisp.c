#include "Soft_SPI.h"
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <stdlib.h>
#include "ascii_chars.h"
#include "max7219.h"

void SPI_init(void)
{
  SCLK_dir = 0;
  SDOUT_dir = 0;
//  SDIN_dir = 1;
  CS0_dir  = 0;
  //CS1_dir  = 0;
}
//--------------------------TX: transmit data-----------------------------------
void SPI_write(char send)
{
  for(int Tx = 0 ; Tx < 8 ; Tx++ )
  {
    SCLK = 0;
    NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
    NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
    NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
    SDOUT = ( (send << Tx) & 0x80 ) ? 1 : 0; //MSB first.
    
    SCLK = 1;                  
    NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
    NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
    NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
    NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();    
  }
}
//--------------------------RX: recieve data------------------------------------
/*char SPI_read(void)
{
  char data = 0;

  for(int Rx = 0 ; Rx < 8 ; Rx++ )
  {
    SCLK = 0;
    data += (SDIN << (7-Rx));  //MSB first.
    SCLK = 1;
  }

  return data;
  
  
}*/


void MAX7219_init(char noChips)
{
  SPI_init();
  while(noChips)
        MAX7219_config(--noChips);
}


void MAX7219_config(char chip)
{
  MAX7219_write(DECODE_MODE_REG,DISABLE_DECODE,chip);    
  MAX7219_write(INTESITY_REG,BRIGHTNESS,chip);     
  MAX7219_write(SCAN_LIMIT_REG,SCAN_ALL_DIGITS,chip);     
  MAX7219_write(SHUTDOWN_REG,NORMAL_OPERATION,chip);
  MAX7219_write(DISPLAY_TEST_REG,DISABLE_TEST,chip);   
}

void MAX7219_write(char regName,char data,char chip)
{
  CS0 = 0;
   
  SPI_write(regName); 
  
  SPI_write(data); 
  while(chip--)
     
       MAX7219_NoOperation();        //Used for daisy chained (Cascaded) arrangements
  
  CS0 = 1;
}

union
{
    uint8_t Data;
    struct
    {
        uint8_t b0:1;
        uint8_t b1:1;
        uint8_t b2:1;
        uint8_t b3:1;
        uint8_t b4:1;
        uint8_t b5:1;
        uint8_t b6:1;
        uint8_t b7:1;
    }aa;
}bb,cc;

//uint8_t Flip(uint8_t dat)
//{
//    uint8_t retval;
//    
//    bb.Data=dat;
//    cc.aa.b0=bb.aa.b7;
//    cc.aa.b1=bb.aa.b6;
//    cc.aa.b2=bb.aa.b5;
//    cc.aa.b3=bb.aa.b4;
//    cc.aa.b4=bb.aa.b3;
//    cc.aa.b5=bb.aa.b2;
//    cc.aa.b6=bb.aa.b1;
//    cc.aa.b7=bb.aa.b0;
//
//    retval = cc.Data;
//    return retval;
//}

void MAX7219_displayText(char* text)
{ 
  char chip = 0;
  char col,row;
  while(*text)
  { 
    row = (*text++);
    
    for(col = 0; col <8 ; col++)
    {
      MAX7219_write(7-col+1, symbol[row][col], chip );
    }
    
    chip++;
  }
}



void Write_OneDisp(uint8_t Dat)
{
    uint8_t Col,NedDat;

    NedDat = Dat - 32;
    CS0 = 0;   
    for(Col=0;Col<8;Col++)
    {
        SPI_write(Col); 
        SPI_write(symbol[NedDat][Col]); 
    }
    CS0 = 1;
    
}
void MAX7219_NoOperation()
{
  SPI_write(NO_OP_REG);           
  SPI_write(0x00);                //Don't care (Can be any arbitrary value)
}
//------------------------------------------------------------------------------
