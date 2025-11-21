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
        Device            :  PIC18F27K40
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

// get/set led_1 aliases
#define led_1_TRIS                 TRISAbits.TRISA0
#define led_1_LAT                  LATAbits.LATA0
#define led_1_PORT                 PORTAbits.RA0
#define led_1_WPU                  WPUAbits.WPUA0
#define led_1_OD                   ODCONAbits.ODCA0
#define led_1_ANS                  ANSELAbits.ANSELA0
#define led_1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define led_1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define led_1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define led_1_GetValue()           PORTAbits.RA0
#define led_1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define led_1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define led_1_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define led_1_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define led_1_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define led_1_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define led_1_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define led_1_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set led_2 aliases
#define led_2_TRIS                 TRISAbits.TRISA1
#define led_2_LAT                  LATAbits.LATA1
#define led_2_PORT                 PORTAbits.RA1
#define led_2_WPU                  WPUAbits.WPUA1
#define led_2_OD                   ODCONAbits.ODCA1
#define led_2_ANS                  ANSELAbits.ANSELA1
#define led_2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define led_2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define led_2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define led_2_GetValue()           PORTAbits.RA1
#define led_2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define led_2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define led_2_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define led_2_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define led_2_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define led_2_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define led_2_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define led_2_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()              PORTBbits.RB0
#define RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()             do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()           do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode()         do { ANSELBbits.ANSELB0 = 1; } while(0)
#define RB0_SetDigitalMode()        do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set pot aliases
#define pot_TRIS                 TRISCbits.TRISC4
#define pot_LAT                  LATCbits.LATC4
#define pot_PORT                 PORTCbits.RC4
#define pot_WPU                  WPUCbits.WPUC4
#define pot_OD                   ODCONCbits.ODCC4
#define pot_ANS                  ANSELCbits.ANSELC4
#define pot_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define pot_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define pot_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define pot_GetValue()           PORTCbits.RC4
#define pot_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define pot_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define pot_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define pot_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define pot_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define pot_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define pot_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define pot_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSELC7 = 0; } while(0)

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