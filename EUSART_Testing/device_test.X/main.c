#include "mcc_generated_files/mcc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

uint16_t adc_value=0;
unsigned char I2a_Pot[5];

void SendToUart(const uint8_t* st_pt)                                           //L-98 use to print string on Uart screen 
{
    while (*st_pt)               //if there is a char
        EUSART2_Write(*st_pt++);     //process it as a byte data                        //use to print single character on Uart screen
    
}
void main(void)
{
    SYSTEM_Initialize();

    while (1)
    { 
        adc_value= ADC_GetConversion(pot);
        itoa(I2a_Pot, adc_value, 10);                                               //pot value convert into ascii to print on uart
        SendToUart("Pot:");                                                         //print string on uart on uart
        SendToUart( I2a_Pot ); 
        EUSART2_Write('\n');
        __delay_ms(100);
    }
}
