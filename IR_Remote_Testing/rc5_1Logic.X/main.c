
#include "mcc_generated_files/mcc.h"

extern uint16_t data;

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    while (1)
    {
        if(data==1)
        {
            NOP();
            data=0;
        }
    }
}
