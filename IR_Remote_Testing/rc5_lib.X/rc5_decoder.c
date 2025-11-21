/*--------------------------------------------------------------------

  Title       : RC5 Interrupt driven Decoder
  Filename    : rc_decoder.c 
   
  Copyright @ BobTheBass 2011
    
--------------------------------------------------------------------*/

#include <htc.h>
#include "rc5_decoder.h"
#include "mcc_generated_files/interrupt_manager.h"

/*--- Local function prototypes ---*/

//unsigned char get_pulse_length(void);
void one_type_pulse(void);
void two_type_pulse(void);
void three_type_pulse(void);
//void save_data(unsigned char data);

/*--- Initialise rc5 decoder interrupt ---*/


void init_rc5_decoder(void)
  {
  RC5_Code.valid = 0;
  Decoder.State = START_S;

//  ANSEL &= 0xfb;  /* RA2 as digital I/O */
//  TRISA2 = 1;     /* RA2 as input */
//
///* Timer should have an overflow period of greater than 5mS and less than 15mS */
///* Overflow period = (1 / (oscfreq / 4)) * 256 * prescaler */ 
//
//  //OPTION = 0x04;  /* Pull ups on, Timer 1:32 prescaler for 4MHz oscillator */
//
//  OPTION = 0x05;  /* Pull ups on, Timer 1:64 prescaler for 8MHz oscillator */
//
//  INTF = 0;   /* Clear interrupt flag */
//  INTE = 1;   /* Enable External interrupt pin (RA2 on 690) */
  PIR0bits.INTF=0;
  PIE0bits.INTE=1;
  
//  T0IF = 0;   /* Clear interrupt flag */
//  T0IE = 0;   /* Timer_0 overflow interrupt disable */
  PIE0bits.TMR0IE=0;
  PIR0bits.TMR0IF=0;   //TMR0 Overflow Interrupt Flag bit
 
  //INTERRUPT_GlobalInterruptEnable();
//  GIE = 1;    /* Global Interrupt Enable */ 
  } 

  
/*--- Rc5 interrupt ---*/

//void interrupt isr_vector(void)
//{
////  if(INTF)
//    if(PIR0bits.INTF)
//    {
//        switch(Decoder.State)
//        {
//          case START_S:      TMR0 =0;
//    //                        TMR0H = 0;
//    //                        TMR0L = 0;
//    //                        T0IF = 0;
//    //                        T0IE = 1; 
//                            PIE0bits.TMR0IE=1;
//                            PIR0bits.TMR0IF=0;
//
//                            Decoder.bit_counter = 0;
//                            Decoder.rc_data = 0;
//                            Decoder.State = CALIBRATE_S;
//                            break;
//
//          case CALIBRATE_S: Decoder.pulse_t1 = TMR0;  /* Calibrate bit time */
//                            TMR0 = 0;
//    //                        TMR0H = 0;
//    //                        TMR0L = 0;
//                            Decoder.pulse_t2 = Decoder.pulse_t1 + (Decoder.pulse_t1 / 2);
//                            Decoder.pulse_t3 = Decoder.pulse_t1 * 2; 
//                            Decoder.tolerance = Decoder.pulse_t1 / 8; 
//                            Decoder.last_bit = 1;  
//                            Decoder.State = DATA_S;
//                            break;
//
//          case DATA_S:      if(get_pulse_length() == PULSE_OK){
//                              Decoder.State = DATA_S;
//                              }
//                            else{
//    //                          T0IF = 1;
//                                PIR0bits.TMR0IF=1;
//                              }
//                            break;
//
//          default:          PIR0bits.TMR0IF=1;     //    T0IF = 1;
//                            break;
//        }
//        PIR0bits.INTF=0;    //INTF = 0;
//    }
//
////  if(T0IF)
//    if(PIE0bits.TMR0IE)
//    { 
//        if(Decoder.bit_counter == 0x0b)
//        {
//            save_data(0);
//        }
//
//        if(Decoder.bit_counter == 0x0c)
//        {
//            RC5_Code.address = (Decoder.rc_data >> 6) & 0x001f;
//            RC5_Code.command = Decoder.rc_data & 0x003f;
//            RC5_Code.toggle = (Decoder.rc_data >> 11) & 0x0001; 
//            RC5_Code.valid = 1;
//        }
//    
////        T0IF = 0;
////        T0IE = 0;
//        PIE0bits.TMR0IE=0;
//        PIR0bits.TMR0IF=0;
//        Decoder.State = START_S; 
//    }
//}

/*--- Get pulse length ---*/

unsigned char get_pulse_length(void)
  {
  unsigned char max, min;

  Decoder.bit_time = TMR0;
  TMR0 = 0;

  max = Decoder.bit_time + Decoder.tolerance;
  min = Decoder.bit_time - Decoder.tolerance;
   
  if((Decoder.pulse_t1 >= min) && (Decoder.pulse_t1 <= max)){
    one_type_pulse();
    return PULSE_OK;
    }
  else if((Decoder.pulse_t2 >= min) && (Decoder.pulse_t2 <= max)){
    two_type_pulse();
    return PULSE_OK;
    }
  else if((Decoder.pulse_t3 >= min) && (Decoder.pulse_t3 <= max)){
    three_type_pulse();
    return PULSE_OK;
    }
  else{
    return PULSE_ERROR;
    }
  }

/*--- A one type pulse ---*/

 void one_type_pulse(void)
  {
  if(Decoder.last_bit == 1){
    save_data(1);
    }
  else{
    save_data(0);
    }
  }

/*--- A two type pulse ---*/

 void two_type_pulse(void)
  {
  if(Decoder.last_bit == 1){
    save_data(0);
    Decoder.last_bit = 0;
    }
  else{
    save_data(0);
    save_data(1);
    Decoder.last_bit = 1;
    }
  }

/*--- A three type pulse ---*/

 void three_type_pulse(void)
  {
  save_data(0);
  save_data(1);
  Decoder.last_bit = 1;
  }

/*--- Save data ---*/

 void save_data(unsigned char data)
  {
  Decoder.rc_data <<= 1;

  if(data == 1){
    Decoder.rc_data |= 1;
    }
  else{
    Decoder.rc_data &= 0xffe;
    }

  Decoder.bit_counter++;
  }

/*--- End of File ---*/
