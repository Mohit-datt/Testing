#include "mcc_generated_files/mcc.h"
#include "IR_lib.h"
#include <stdio.h>
#include <xc.h>


//void ir_init() {
//    IR_SENSOR_PORT = INPUT;
//}
uint8_t SendBuf[100];

void SendToUart(const uint8_t* st_pt) //L-98 use to print string on Uart screen 
{
    while (*st_pt) //if there is a char
        EUSART2_Write(*st_pt++); //process it as a byte data
}


int ir_result(char debug_info) 
{
    protocol_check(); // call protocol_check function
    /*inside the protocol check function the timer counter checks the pulse width 
    if it is greater than 141 and less than 145 the statement is true. 
    you can do this calculation by taking the datasheet as reference*/
    if (ir_str_t.first_start_pulse >= 141 && ir_str_t.first_start_pulse <= 145) 
    {
        if (ir_str_t.seccound_verification_puls >= 68 && ir_str_t.seccound_verification_puls <= 73) 
        {
            read_data(); //call the function
            ir_str_t.ir_received_data = read_data();
            if (debug_info) 
            {               
                //SendToUart("Received Data: 0x%x   startPuls %d secoundPuls %d \n", ir_str_t.ir_received_data, ir_str_t.first_start_pulse, ir_str_t.seccound_verification_puls);
                sprintf(SendBuf,"Received Data: 0x%x   startPuls %d secoundPuls %d \n",ir_str_t.ir_received_data, ir_str_t.first_start_pulse, ir_str_t.seccound_verification_puls);
                SendToUart(SendBuf);
            }
            return ir_str_t.ir_received_data;
        }
    }
    return ir_str_t.ir_received_data;
}
//The protocol_check() function.
void protocol_check() 
{
    ir_str_t.first_start_pulse = 0; // remove all data
    ir_str_t.seccound_verification_puls = 0; // remove all data
    while (IR_SENSOR_PIN == 0) 
    {
        if (TIMER0_OVERFLOW_INTERRUPT_FLAG) 
        {
            TIMER0_OVERFLOW_INTERRUPT_FLAG = 0;
            ir_str_t.first_start_pulse++;
            if (ir_str_t.first_start_pulse >= 200) 
            {
                break;
            }
        }
    }
    while (IR_SENSOR_PIN == 1) 
    {
        if (TIMER0_OVERFLOW_INTERRUPT_FLAG) 
        {
            TIMER0_OVERFLOW_INTERRUPT_FLAG = 0;
            ir_str_t.seccound_verification_puls++;
            if (ir_str_t.seccound_verification_puls >= 150) 
            {
                break;
            }
        }
    }
}

//The read_data() function

int read_data() 
{
    ir_str_t.ir_raw_data = 0;    
    for (char j = 0; j < 32; j++) 
    {   
        // the data coming from the sensor is 16 bit long so we need a for loop
        while (!IR_SENSOR_PIN); //Wait until PORT goes HIGH
        __delay_us(700);
        if (IR_SENSOR_PIN == 0) 
        {
            ir_str_t.ir_raw_data &= ~(1 << (31 - j)); //Clear bit (7-b)
        } 
        else 
        {
            ir_str_t.ir_raw_data |= (1 << (31 - j)); //Set bit (7-b)
            while (IR_SENSOR_PIN);//Wait until PORT goes LOW
        } 
    }
    return ir_str_t.ir_raw_data;
}