
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------------
#include "ascii_chars.h"
#include "max7219.h"
#include "Soft_SPI.h"
void SPI_init(void);
//------------------------------------------------------------------------------
//void Write_OneDisp(uint8_t Dat);
int main(int argc, char** argv) 
{
    MAX7219_init(6);        //Pass number of Chips as argument
    //SPI_init();
    //MAX7219_config(1);
    //MAX7219_displayText("    ");
    MAX7219_displayText("99.23");
    __delay_ms(20);
    
//    MAX7219_displayText("EFGH");
//    __delay_ms(20);
    
//    MAX7219_displayText("IJKL");
//    __delay_ms(20);
//    
//    MAX7219_displayText("MNOP");
//    __delay_ms(20);
    
    
    //Write_OneDisp('A');
    while(1)
    {
      //MAX7219_displayText("ABCD");
    }
  
  return (EXIT_SUCCESS);
}


