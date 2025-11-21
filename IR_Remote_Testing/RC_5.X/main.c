
#include "mcc_generated_files/mcc.h"
#include "stdlib.h"
#include"string.h"
#include"stdio.h"

extern uint16_t GotData;
extern uint8_t Buff[];
unsigned char sendbuff[20];

void Sendto_Uart(uint8_t* st_pt) 
{
    while (*st_pt) //if there is a char
        EUSART1_Write(*st_pt++); //process it as a byte data
}

void main(void)
{
    SYSTEM_Initialize();
    TMR1_StopTimer();

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    while (1)
    {
        if(GotData==1)
        {
            EUSART1_Write('1');   
//            for(int i=0;i<13;i++)
//            {
//            
//            }
//            sprintf(sendbuff,"IR= %d",Buff);
//            Sendto_Uart(sendbuff); 
            EUSART1_Write('\n');
            GotData=0;
        }
       //EUSART1_Write('0');
        __delay_ms(100);
    }
}
