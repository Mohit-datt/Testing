

#include "mcc_generated_files/mcc.h"
#include"rc5_decoder.h"


void main(void)
{
     unsigned char address, command;
    // initialize the device
    SYSTEM_Initialize();
     init_rc5_decoder();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    while (1)
    {
        if(RC5_Code.valid)
        {
          address = RC5_Code.address;
          command = RC5_Code.command;
          PORTC = command;
          RC5_Code.valid = 0;
        }
    }    
}
