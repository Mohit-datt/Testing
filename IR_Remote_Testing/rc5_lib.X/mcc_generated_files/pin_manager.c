/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F15344
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB             :  MPLAB X 5.45

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "pin_manager.h"




void (*IOCBF7_InterruptHandler)(void);


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0x3F;
    TRISB = 0xF0;
    TRISC = 0xFF;

    /**
    ANSELx registers
    */
    ANSELC = 0x7F;
    ANSELB = 0x70;
    ANSELA = 0x37;

    /**
    WPUx registers
    */
    WPUB = 0x80;
    WPUA = 0x00;
    WPUC = 0x88;

    /**
    ODx registers
    */
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0x3F;
    SLRCONB = 0x00;
    SLRCONC = 0x3F;

    /**
    INLVLx registers
    */
    INLVLA = 0x3F;
    INLVLB = 0x00;
    INLVLC = 0x3F;


    /**
    IOCx registers 
    */
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF7 = 0;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN7 = 1;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP7 = 0;
    


    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCBF7_SetInterruptHandler(IOCBF7_DefaultInterruptHandler);
   
    // Enable IOCI interrupt 
    PIE0bits.IOCIE = 1; 
    
	
    INTPPS = 0x17;   //RC7->EXT_INT:INT;    
    CCP2PPS = 0x0F;   //RB7->CCP2:CCP2;    
}
  
void PIN_MANAGER_IOC(void)
{   
	// interrupt on change for pin IOCBF7
    if(IOCBFbits.IOCBF7 == 1)
    {
        IOCBF7_ISR();  
    }	
}

/**
   IOCBF7 Interrupt Service Routine
*/

//extern int rc5_ok;
//extern uint8_t  rc5_state, bit_n;   // bit_n: bit number used for variable rc5_code bits
//extern uint16_t rc5_code, timer_value;  // rc5_code: whole RC5 code message
//#define short_time    700   // used as a minimum time for short pulse or short space
//#define   med_time   1200   // used as a maximum time for short pulse or short space
//#define  long_time   2000   // used as a maximum time for long pulse or long space
void IOCBF7_ISR(void) {

    // Add custom IOCBF7 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF7_InterruptHandler)
    {
        IOCBF7_InterruptHandler();
    }
    IOCBFbits.IOCBF7 = 0;
    
    
    /*************** start external interrupt ISR ***************/
//  if (RBIF && (RB0 || !RB0))   // PORTB change ISR (& clear mismatch condition)
//  if (IOCBFbits.IOCBF7 && (PORTBbits.RB7 || !PORTBbits.RB7))   // PORTB change ISR (& clear mismatch condition)
//    {
//    RBIF = 0;   // clear PORTB interrupt flag bit
//    IOCBFbits.IOCBF7 = 0;
//    if(rc5_state != 0)
//    {
////      timer_value = (TMR1H << 8) | TMR1L;  // store Timer1 value
//        timer_value =TMR1;
////        TMR1H = TMR1L = 0;     // reset Timer1
//        TMR1=0;
//    }
//    TMR1=0;
//    switch(rc5_state)
//    {
//     case 0 :  // start receiving IR data (initially we're at the beginning of mid1)
//       TMR1H = TMR1L = 0;  // reset Timer1
////       TMR1ON    = 1;   // enable Timer1
//       T1CONbits.ON=1;
//       rc5_state = 1;   // next state: end of mid1
//       bit_n     = 0;   // reset bit number
//       break;
// 
//     case 1 :   // end of mid1 ==> check if we're at the beginning of start1 or mid0
//       if((timer_value > long_time) || (timer_value < short_time))
//       {  // invalid interval ==> stop decoding and reset
//         rc5_state = 0;  // reset decoding process
////       TMR1ON    = 0;  // disable Timer1
//         T1CONbits.ON=0;
//       }
// 
//       else
//       {
//         rc5_code |= 1 << (13 - bit_n);   // set bit (13 - bit_n)
//         bit_n++;
//         if (bit_n > 13)  // if all bits have been received
//         {
//           rc5_ok = 1;    // decoding process is OK
////           RBIE   = 0;    // disable PORTB change interrupt
//           PIE0bits.IOCIE=0;
//         }
//         else
//         {
//           if(timer_value > med_time)   // we're at the beginning of mid0
//           {
//             rc5_state = 2;     // next state: end of mid0
//             if(bit_n == 13)    // if we're at the LSB bit
//             {
//               rc5_ok = 1;      // decoding process is OK
//               rc5_code &= ~1;  // clear the LSB bit
////               RBIE   = 0;      // disable PORTB change interrupt
//                PIE0bits.IOCIE=0;
//             }
//           }  // end  " if(timer_value > med_time) "
//           else               // we're at the beginning of start1
//             rc5_state = 3;   // next state: end of start1
//         }  // end  " else "
//         
//       }  // end  " else "
//       break;
// 
//     case 2 :   // end of mid0 ==> check if we're at the beginning of start0 or mid1
//       if((timer_value > long_time) || (timer_value < short_time))
//       {  // time interval invalid ==> stop decoding
//         rc5_state = 0;    // reset decoding process
////         TMR1ON    = 0;    // disable Timer1
//         T1CONbits.ON=0;
//       }
//       else
//       {
//         rc5_code &= ~(1 << (13 - bit_n));  // clear (13 - bit_n)
//         bit_n++;
//         if(timer_value > med_time)  // we're at the beginning of mid1
//           rc5_state = 1;            // next state: end of mid1
//         else              // we're at the beginning of start0
//           rc5_state = 4;  // next state: end of start0
//       }
//       break;
// 
//     case 3 :   // end of start1 ==> check if we're at the beginning of mid1
//       if((timer_value > med_time) || (timer_value < short_time))
//       {   // time interval invalid ==> stop decoding
////         TMR1ON    = 0;  // disable Timer1
//           T1CONbits.ON=0;
//         rc5_state = 0;  // reset decoding process
//       }
//       else              // we're at the beginning of mid1
//         rc5_state = 1;  // next state: end of mid1
//       break;
// 
//     case 4 :  // end of start0 ==> check if we're at the beginning of mid0
//       if((timer_value > med_time) || (timer_value < short_time))
//       {   // time interval invalid ==> stop decoding
////         TMR1ON    = 0;  // disable Timer1
//           T1CONbits.ON=0;
//         rc5_state = 0;  // reset decoding process
//       }
//       else   // we're at the beginning of mid0
//       {
//         rc5_state = 2;    // next state: end of mid0
//         if(bit_n == 13)   // if we're at the LSB bit
//         {
//           rc5_ok = 1;      // decoding process is OK
//           rc5_code &= ~1;  // clear the LSB bit
////           RBIE   = 0;      // disable PORTB change interrupt
//            PIE0bits.IOCIE=0;
//         }
//       }  // end  " else "
//       
//    }  // end  " switch(rc5_state) "
// 
//  //}  // end  " if (RBIF && (RB0 || !RB0)) "
///*************** end external interrupt ISR ***************/
// 
///*************** start Timer1 ISR ***************/
////  if (TMR1IF)         // Timer1 ISR
//  if ( PIR4bits.TMR1IF)         // Timer1 ISR
//  {
////    TMR1IF    = 0;   // clear Timer1 interrupt flag bit
//     PIR4bits.TMR1IF = 0;
//    rc5_state = 0;   // reset decoding process
////    TMR1ON    = 0;   // disable Timer1
//    T1CONbits.ON=0;
//  }
/*************** end Timer1 ISR ***************/
    
}

/**
  Allows selecting an interrupt handler for IOCBF7 at application runtime
*/
void IOCBF7_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF7_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF7
*/
void IOCBF7_DefaultInterruptHandler(void){
    // add your IOCBF7 interrupt custom code
    // or set custom function using IOCBF7_SetInterruptHandler()
}

/**
 End of File
*/