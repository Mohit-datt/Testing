
#include "mcc_generated_files/mcc.h"
#include <stdio.h>         // for sprintf
#include <stdint.h> 
#include <stdint.h>
#include <stdlib.h>
//#include "rc5.h"  //avr
//#include "rc5_decoder.h"
#include "rc5demo.h"


//#define short_time    700   // used as a minimum time for short pulse or short space
//#define   med_time   1200   // used as a maximum time for short pulse or short space
//#define  long_time   2000   // used as a maximum time for long pulse or long space
 
//char text[3];
////__bit rc5_ok;
//int rc5_ok;
//uint8_t  rc5_state, bit_n;   // bit_n: bit number used for variable rc5_code bits
//uint16_t rc5_code, timer_value;  // rc5_code: whole RC5 code message
 
// interrupt ISRs
//void __interrupt() MyISRs(void)
//{
///*************** start external interrupt ISR ***************/
////  if (RBIF && (RB0 || !RB0))   // PORTB change ISR (& clear mismatch condition)
//  if (IOCBFbits.IOCBF7 && (PORTBbits.RB7 || !PORTBbits.RB7))   // PORTB change ISR (& clear mismatch condition)
//  {
////    RBIF = 0;   // clear PORTB interrupt flag bit
//    IOCBFbits.IOCBF7 = 0;
//    if(rc5_state != 0)
//    {
////      timer_value = (TMR1H << 8) | TMR1L;  // store Timer1 value
//        timer_value =TMR1;
////        TMR1H = TMR1L = 0;     // reset Timer1
//        TMR1=0;
//    }
// 
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
//  }  // end  " if (RBIF && (RB0 || !RB0)) "
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
///*************** end Timer1 ISR ***************/
// 
//}


void main(void)
{  
    unsigned char address, command;
    // initialize the device
    SYSTEM_Initialize();
//    init_rc5_decoder();
//    
//     for(;;)
//    {
//        if(RC5_Code.valid)
//          {
//            address = RC5_Code.address;
//            command = RC5_Code.command;
//            PORTC = command;
//            RC5_Code.valid = 0;
//          }
//    }
    
    
        //RC5_Init();
    
    /* Set PB5 to output */
    //DDRB |= _BV(PB5);
    
    /* Enable interrupts */
//    sei();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
//    for(;;)
//    {
//      
//    }    
    
//    uint16 rc5code;
//	uint8 dummy;
//
//	TRISC = 0xBF;
// 	TRISBbits.RB4=1;
//    
//	// configure timer 0
//	OpenTimer0(TIMER_INT_OFF & T0_8BIT & T0_SOURCE_INT & T0_PS_1_256);
//
//    /* baud rate formula for BRGH = 0: */
//    /* BaudRate = FOSC/(16 (X + 1)) */
//    /* => BaudRate (64 (X + 1)) = FOSC */
//    /* => 16 (X + 1) = FOSC / BaudRate */
//    /* => X = (FOSC / BaudRate) / 16 - 1 */
//    /* => X = SPBRG = 40000000 / 19200) / 16 - 1 = 25.04166 => 25 */
//    OpenUSART(USART_TX_INT_OFF &    /* disables TX interrupt */
//              USART_RX_INT_OFF &    /* disables RX interrupt */
//              USART_ASYNCH_MODE &   /* sets it in asynchronous mode */
//              USART_EIGHT_BIT &     /* sets to use 8-bit data mode */
//              USART_CONT_RX &       /* sets the port in continues receive mode */
//              USART_BRGH_LOW,      /* uses the high speed Baud rate formula */
//              31);
//
//	INTCONbits.RBIE = 1;     // Enable Port-b change interrupt
//	dummy = RC5_GetPin();		// clear mismatch
//	INTCONbits.RBIF = 0;  // Wenn ja Interruptflag löschen
//	INTCONbits.GIE = 1;
//
//	LED_On();
//
//
//	printf("*** C18 RC5 Demo! ***\n\r");
//	LED_Off();

    
    // Enable the Global Interrupts
 

    // Enable the Peripheral Interrupts
   

    while (1)
    {     
        
         /* check if new data is available */
        if (RC5_CodeReady())
        {
            /* get code */
            rc5code = RC5_GetCode();
            
            printf("RC5 Code=0x%04X DevAddr=0x%02X Toggle=%d Cmd=0x%02X\n\r",
                   rc5code,
                   RC5_GetDeviceAddr(rc5code),
                   RC5_GetToggleBit(rc5code),
                   RC5_GetCmd(rc5code));
        }
        
        /* this function increments the RC5 timeout timer */
        /* NOTE: Decoding will also work without calling this function, but */
        /*       it could happen that RC5 codes are sometimes not getting */
        /*       recognized because of decoding state machine stucks due */
        /*       to erroneous RC5 signal. */
        RC5_TimeoutIncrement();
        
        
//          uint16_t command;
//                
//        /* Poll for new RC5 command */
//        if(RC5_NewCommandReceived(&command))
//        {
//            /* Reset RC5 lib so the next command
//             * can be decoded. This is a must! */
//            RC5_Reset();
            
            /* Toggle the LED on PB5 */
//            PORTB ^= _BV(PB5);
            
            /* Do something with the command 
             * Perhaps validate the start bits and output
             * it via UART... */
//            if(RC5_GetStartBits(command) != 3)
//            {
//                /* ERROR */
//            }
//            
//            uint8_t toggle = RC5_GetToggleBit(command);
//            uint8_t address = RC5_GetAddressBits(command);
//            uint8_t cmdnum = RC5_GetCommandBits(command);
//        }
    }
}
