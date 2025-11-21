#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char MyBuf[6];
uint8_t rx_data=0,RX_index=0,kk=0,jj=0,Press=0,result=0,tt=0;
const unsigned char BUtton[6][4]={"33DE","3BDE","33E9","3BE9","33CF","3BCF"};
const unsigned char BUtton01[]={"3BDE"},BUtton11[]={"33DE"},BUtton02[]={"3BE9"},BUtton22[]={"33E9"},BUtton03[]={"3BCF"},BUtton33[]={"33CF"};
const unsigned char addr[]={"3B"};
void received_data(void)
{
    while(!PIR1bits.RCIF);
    rx_data=RC1REG;

    if(RX_index<6)
    {
        MyBuf[RX_index++]=rx_data;
    }
    
//    for(kk=0;kk<6;kk++)
//    {
//        for(jj=0;jj<4;jj++)
//        {
//            if(MyBuf[jj]!=BUtton[kk][jj])    break;
//        }
//        if(jj==4)
//        {
//            NOP();
//            Press=kk;
//        }
//    }    

    
//        for(jj=0;jj<2;jj++)
//        {
//            if(MyBuf[jj]==addr[jj])
//            {
//                for(kk=0;kk<6;kk++)
//                {
//                    if(MyBuf=="DE\r\n")
//                    {
//                        Press=1;
//                    }
//                }
//            }
//        }
    
    if(MyBuf[5]=='\n');
    {
        if(MyBuf[0]=='3' )
        {
           if(MyBuf[2]=='D' && MyBuf[3]=='E' )
           {
            IO_RA0_Toggle();// Press=1;   
           }
           else if(MyBuf[2]=='E' && MyBuf[3]=='9')
           {
            IO_RA1_Toggle();// Press=2;
           }
           else if(MyBuf[2]=='C' && MyBuf[3]=='F')
           {
            Press=3;
           }
        }
    }

//        if(Press==1)
//        {
//            
//        }
//        if(Press==2)
//        {
//            
//        }
//        if(Press==3)
//        {
//            IO_RA1_Toggle();
//            IO_RA1_Toggle();
//        }
//   
}

//char UART_Read()
//{
//  while(!PIR1bits.RCIF);
//  return RC1REG;
//}


void Tmr1_intt(void)
{
//    if(DecodedIRKey>0) DecodedIRKey--;
//    else DecodedIRKey=0;
        if(tt>0) tt--;
    else
    {
        tt=10;
        Press=0;
        if(MyBuf[5]=='\n')
        {
            for(int i=0;i<6;i++)
            {
                MyBuf[i]=0;
            }
        }
     
    }
}
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    EUSART_SetRxInterruptHandler(received_data);
    TMR1_SetInterruptHandler(Tmr1_intt);
    
    while (1)
    {
    
    }
}
