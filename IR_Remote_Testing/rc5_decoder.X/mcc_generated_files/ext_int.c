/**
   EXT_INT Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     ext_int.c
 
   @Summary
     This is the generated driver implementation file for the EXT_INT driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for EXT_INT.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
         Device            :  PIC16F15344
         Driver Version    :  1.11
     The generated drivers are tested against the following:
         Compiler          :  XC8 2.31 and above
         MPLAB             :  MPLAB X 5.45
 */ 

 /**
   Section: Includes
 */
#include <xc.h>
#include "ext_int.h"
#include"../rc5_decoder.h"



void (*INT_InterruptHandler)(void);

void INT_ISR(void)
{
    //EXT_INT_InterruptFlagClear();

      if(PIR0bits.INTF)
    {
        switch(Decoder.State)
        {
          case START_S:      TMR0 =0;
    //                        TMR0H = 0;
    //                        TMR0L = 0;
    //                        T0IF = 0;
    //                        T0IE = 1; 
                            PIE0bits.TMR0IE=1;
                            PIR0bits.TMR0IF=0;

                            Decoder.bit_counter = 0;
                            Decoder.rc_data = 0;
                            Decoder.State =CALIBRATE_S;
                            break;

          case CALIBRATE_S: Decoder.pulse_t1 = TMR0;  /* Calibrate bit time */
                            TMR0 = 0;
    //                        TMR0H = 0;
    //                        TMR0L = 0;
                            Decoder.pulse_t2 = Decoder.pulse_t1 + (Decoder.pulse_t1 / 2);
                            Decoder.pulse_t3 = Decoder.pulse_t1 * 2; 
                            Decoder.tolerance = Decoder.pulse_t1 / 8; 
                            Decoder.last_bit = 1;  
                            Decoder.State = DATA_S;
                            break;

          case DATA_S:      if(get_pulse_length() == PULSE_OK){
                              Decoder.State = DATA_S;
                              }
                            else{
    //                          T0IF = 1;
                                PIR0bits.TMR0IF=1;
                              }
                            break;

          default:          PIR0bits.TMR0IF=1;     //    T0IF = 1;
                            break;
        }
        PIR0bits.INTF=0;    //INTF = 0;
    }

//  if(T0IF)
    if(PIR0bits.TMR0IF)
    { 
        if(Decoder.bit_counter == 0x0b)
        {
            save_data(0);
        }

        if(Decoder.bit_counter == 0x0c)
        {
            RC5_Code.address = (Decoder.rc_data >> 6) & 0x001f;
            RC5_Code.command = Decoder.rc_data & 0x003f;
            RC5_Code.toggle = (Decoder.rc_data >> 11) & 0x0001; 
            RC5_Code.valid = 1;
        }
    
//        T0IF = 0;
//        T0IE = 0;
        PIE0bits.TMR0IE=0;
        PIR0bits.TMR0IF=0;
        Decoder.State = START_S; 
    }
    
    // Callback function gets called everytime this ISR executes
//    INT_CallBack();    
}


void INT_CallBack(void)
{
    // Add your custom callback code here
    if(INT_InterruptHandler)
    {
        INT_InterruptHandler();
    }
}

void INT_SetInterruptHandler(void (* InterruptHandler)(void)){
    INT_InterruptHandler = InterruptHandler;
}

void INT_DefaultInterruptHandler(void){
    // add your INT interrupt custom code
    // or set custom function using INT_SetInterruptHandler()
}

void EXT_INT_Initialize(void)
{
    
    // Clear the interrupt flag
    // Set the external interrupt edge detect
    EXT_INT_InterruptFlagClear();   
    EXT_INT_fallingEdgeSet();    
    // Set Default Interrupt Handler
    INT_SetInterruptHandler(INT_DefaultInterruptHandler);
    EXT_INT_InterruptEnable();      

}

