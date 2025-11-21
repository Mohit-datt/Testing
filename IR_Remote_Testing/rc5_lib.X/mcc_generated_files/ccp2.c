/**
  CCP2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp2.c

  @Summary
    This is the generated driver implementation file for the CCP2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for CCP2.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F15344
        Driver Version    :  2.1.3
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
         MPLAB 	          :  MPLAB X 5.45
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "ccp2.h"
//#include "../rc5.h" 
#include "../rc5_decoder.h"
static void (*CCP2_CallBack)(uint16_t);

/**
  Section: Capture Module APIs:
*/

static void CCP2_DefaultCallBack(uint16_t capturedValue)
{
    // Add your code here
}

void CCP2_Initialize(void)
{
    // Set the CCP2 to the options selected in the User Interface
	
	// MODE Falling edge; EN enabled; CCP2FMT right_aligned; 
	CCP2CON = 0x84;    
	
	// CCP2CTS CCP2 pin; 
	CCP2CAP = 0x00;    
	
	// RH 0; 
	CCPR2H = 0x00;    
	
	// RL 0; 
	CCPR2L = 0x00;    
    
    // Set the default call back function for CCP2
    CCP2_SetCallBack(CCP2_DefaultCallBack);

    
    // Clear the CCP2 interrupt flag
    PIR6bits.CCP2IF = 0;

    // Enable the CCP2 interrupt
    PIE6bits.CCP2IE = 1;
    
     //RC5_Reset();
}

 unsigned char get_pulse_length(void);
 void save_data(unsigned char data);
 void (*INT_InterruptHandler)(void);
 
void CCP2_CaptureISR(void)
{
    CCP2_PERIOD_REG_T module;

    // Clear the CCP2 interrupt flag
    PIR6bits.CCP2IF = 0;
    
    // Copy captured value.
    module.ccpr2l = CCPR2L;
    module.ccpr2h = CCPR2H;
    
      if(PIR6bits.CCP2IF)
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
                            Decoder.State = CALIBRATE_S;
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
        PIR6bits.CCP2IF=0;    //INTF = 0;
    }

//  if(T0IF)
    if(PIE0bits.TMR0IE)
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
    
    
//    uint16_t delay = module.ccpr2_16Bit;
//
//    /* TSOP2236 pulls the data line up, giving active low,
//     * so the output is inverted. If data pin is high then the edge
//     * was falling and vice versa.
//     * 
//     *  Event numbers:
//     *  0 - short space
//     *  2 - short pulse
//     *  4 - long space
//     *  6 - long pulse
//     */
////    uint8_t event = (PIND & _BV(PIND2)) ? 2 : 0;
//    uint8_t event = (PORTB & PORTBbits.RB7) ? 2 : 0;
//    
//    if(delay > LONG_MIN && delay < LONG_MAX)
//    {
//        event += 4;
//    }
//    else if(delay < SHORT_MIN || delay > SHORT_MAX)
//    {
//        /* If delay wasn't long and isn't short then
//         * it is erroneous so we need to reset but
//         * we don't return from interrupt so we don't
//         * loose the edge currently detected. */
//        RC5_Reset();
//    }
//
//    if(state == STATE_BEGIN)
//    {
//        ccounter--;
//        command |= 1 << ccounter;
//        state = STATE_MID1;
////        TCNT1 = 0;
//        TMR1=0;
////        return;
//    }
//    
//    State newstate = (trans[state] >> event) & 0x03;
//
//    if(newstate == state || state > STATE_START0)
//    {
//        /* No state change or wrong state means
//         * error so reset. */
//        RC5_Reset();
////        return;
//    }
//    
//    state = newstate;
//    
//    /* Emit 0 - jest decrement bit position counter
//     * cause data is already zeroed by default. */
//    if(state == STATE_MID0)
//    {
//        ccounter--;
//    }
//    else if(state == STATE_MID1)
//    {
//        /* Emit 1 */
//        ccounter--;
//        command |= 1 << ccounter;
//    }
//    
//    /* The only valid end states are MID0 and START1.
//     * Mid0 is ok, but if we finish in MID1 we need to wait
//     * for START1 so the last edge is consumed. */
//    if(ccounter == 0 && (state == STATE_START1 || state == STATE_MID0))
//    {
//        state = STATE_END;
//        has_new = 1;
//        
//        /* Disable INT0 */
////        EIMSK &= ~_BV(INT0);
//         PIE0bits.INTE = 0; // ex int enable
//    }
//    
////    TCNT1 = 0;
//    TMR1=0;    
//    
     //Return 16bit captured value
    CCP2_CallBack(module.ccpr2_16Bit);
}

void CCP2_SetCallBack(void (*customCallBack)(uint16_t)){
    CCP2_CallBack = customCallBack;
}
/**
 End of File
*/