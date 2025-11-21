/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F15344
        Driver Version    :  2.11
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set sens_led aliases
#define sens_led_TRIS                 TRISBbits.TRISB4
#define sens_led_LAT                  LATBbits.LATB4
#define sens_led_PORT                 PORTBbits.RB4
#define sens_led_WPU                  WPUBbits.WPUB4
#define sens_led_OD                   ODCONBbits.ODCB4
#define sens_led_ANS                  ANSELBbits.ANSB4
#define sens_led_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define sens_led_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define sens_led_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define sens_led_GetValue()           PORTBbits.RB4
#define sens_led_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define sens_led_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define sens_led_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define sens_led_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define sens_led_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define sens_led_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define sens_led_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define sens_led_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set pot aliases
#define pot_TRIS                 TRISCbits.TRISC1
#define pot_LAT                  LATCbits.LATC1
#define pot_PORT                 PORTCbits.RC1
#define pot_WPU                  WPUCbits.WPUC1
#define pot_OD                   ODCONCbits.ODCC1
#define pot_ANS                  ANSELCbits.ANSC1
#define pot_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define pot_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define pot_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define pot_GetValue()           PORTCbits.RC1
#define pot_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define pot_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define pot_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define pot_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define pot_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define pot_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define pot_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define pot_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set out_led aliases
#define out_led_TRIS                 TRISCbits.TRISC2
#define out_led_LAT                  LATCbits.LATC2
#define out_led_PORT                 PORTCbits.RC2
#define out_led_WPU                  WPUCbits.WPUC2
#define out_led_OD                   ODCONCbits.ODCC2
#define out_led_ANS                  ANSELCbits.ANSC2
#define out_led_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define out_led_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define out_led_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define out_led_GetValue()           PORTCbits.RC2
#define out_led_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define out_led_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define out_led_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define out_led_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define out_led_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define out_led_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define out_led_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define out_led_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/