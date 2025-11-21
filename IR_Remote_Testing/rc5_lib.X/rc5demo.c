//#include <p18cxxx.h>
//#include <usart.h>
#include <stdio.h>
//#include <timers.h>

//#include "../rc5demo.h"
#include "rc5demo.h"

#pragma config OSC = HSPLL
#pragma config WDT = OFF
#pragma config LVP = ON
#pragma config PBADEN = OFF


#define LED_On()		TRISAbits.TRISA0 = 0; LATAbits.LATA0 = 1
#define LED_Off()		TRISAbits.TRISA0 = 0; LATAbits.LATA0 = 0


/** I N T E R R U P T S  *******************************************/

#pragma interruptlow InterruptHandler
void InterruptHandler (void)
{
    if( INTCONbits.RBIF )    // PORTB Change Interrupt
    {
		LED_On();
		RC5_InterruptHandler();
		LED_Off();
		INTCONbits.RBIF = 0;  // Wenn ja Interruptflag löschen
    }
}

#pragma code _HIGH_INTERRUPT_VECTOR = 0x000008
void _high_ISR (void)
{
    _asm
        goto InterruptHandler       // Sprung zur Interruptroutine
    _endasm
}

#pragma code _LOW_INTERRUPT_VECTOR = 0x000018
void _low_ISR (void)
{
    _asm
        goto InterruptHandler       // Sprung zur Interruptroutine
    _endasm
}


#pragma code
