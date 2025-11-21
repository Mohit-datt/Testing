
#include "mcc_generated_files/mcc.h"

uint16_t output[50],kl=0;
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    while (1)
    {
        if(kl<50)
        {
        output[kl++]=CLC2_OutputStatusGet();
        }
    }
}
/**
 End of File
*/