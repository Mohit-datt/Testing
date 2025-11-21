
#include "mcc_generated_files/mcc.h"
#include "IRLIB.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

uint16_t dummy,adc=0,tt=0;
unsigned char SendBuf[100];
void SendToUart(uint8_t* st_pt)                                                 //L-98 use to print string on Uart screen 
{
    while (*st_pt) //if there is a char
        EUSART2_Write(*st_pt++); //process it as a byte data                    //use to print single character on Uart screen
}
void Tmr1_intt(void)
{
//    if(DecodedIRKey>0) DecodedIRKey--;
//    else DecodedIRKey=0;
        if(tt>0) tt--;
    else
    {
        tt=10;
        DecodedIRKey=0;
    }
}
void main(void)
{
    SYSTEM_Initialize();

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    TMR1_SetInterruptHandler(Tmr1_intt);
    
    while (1)
    {
        dummy=ADCC_GetSingleConversion(pot);
        adc=ADCC_GetSingleConversion(pot);

        sprintf(SendBuf,"%d",adc);
        SendToUart(SendBuf);
        EUSART2_Write('\n');
        __delay_ms(100);   
    }
}
