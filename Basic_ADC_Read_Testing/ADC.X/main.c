

#include "mcc_generated_files/mcc.h"
#include <xc.h>
#include "mcc_generated_files/pin_manager.h"
#include <stdio.h>

// CONFIG
#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINT1  // Power-up default value for COSC bits->HFINTOSC (1MHz)
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit->CLKOUT function is disabled; i/o or oscillator function on OSC2
#pragma config CSWEN = ON       // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit->FSCM timer enabled

// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit->MCLR pin is Master Clear function
#pragma config PWRTE = OFF      // Power-up Timer Enable bit->PWRT disabled
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit->ULPBOR disabled
#pragma config BOREN = ON       // Brown-out reset enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = LO        // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices
#pragma config ZCD = OFF        // Zero-cross detect disable->Zero-cross detect circuit is disabled at POR.
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control->The PPSLOCK bit can be cleared and set only once in software
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG3
#pragma config WDTCPS = WDTCPS_31   // WDT Period Select bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF           // WDT operating mode->WDT Disabled, SWDTEN is ignored
#pragma config WDTCWS = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC          // WDT input clock selector->Software Control

// CONFIG4
#pragma config BBSIZE = BB512  // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF      // Boot Block Enable bit->Boot Block disabled
#pragma config SAFEN = OFF     // SAF Enable bit->SAF disabled
#pragma config WRTAPP = OFF    // Application Block Write Protection bit->Application Block not write protected
#pragma config WRTB = OFF      // Boot Block Write Protection bit->Boot Block not write protected
#pragma config WRTC = OFF      // Configuration Register Write Protection bit->Configuration Register not write protected
#pragma config WRTSAF = OFF    // Storage Area Flash Write Protection bit->SAF not write protected
#pragma config LVP = ON  
#pragma config CP = OFF        // UserNVM Program memory code protection bit->UserNVM code protection disabled

uint16_t ADC_value=0;
uint8_t tt=0;
char ch;
void ADC_Initialize()
 {
    PMD2bits.ADCMD=0;          // adc module enabled
    ADCON1bits.ADCS=0b000;     //ADC Conversion Clock Select bits
    ADCON1bits.ADPREF=0;       //Positive Voltage Reference Configuration bits
    ADCON1bits.ADFM=1;         //ADC Result Format Select bit
    ADCON0bits.CHS=0b010001;
    ADCON0bits.ADON=1;         //adc on
    ADCON0bits.GOnDONE=0;      //ADC Conversion Status bit
      
    ADRESL = 0x00;    
    ADRESH = 0x00;  
    
    PIE1bits.ADIE = 1;         // Enabling ADC interrupt.
  }

void TMR2_int()
  {
    if(tt>0)    tt--;
    else
    {
        tt=1; 
        IO_RC2_Toggle();              
    }         
  } 

void UART_char(char ch)
{
     while(!PIR3bits.TX2IF);    // Wait till the transmitter register becomes empty
    if(PIE3bits.TX2IE==0)        //EUSART2 Transmit Interrupt Flag
    {
        TX2REG=ch; 
    } 
    PIE3bits.TX2IE = 1;
}

void UART_string(char* st_pt)
    {
        while(*st_pt) //if there is a char
        UART_char(*st_pt++); //process it as a byte data
    }
       
void Osillator_Initialize(void)
  { 
    OSCCON1bits.NOSC = 0b110;       //HFINTOSC selected
    OSCFRQbits.HFFRQ = 0b110;       //32Mhz selected  
    OSCCON1bits.NDIV = 0b111;       // ADCRC  
  }

unsigned int ADC_Read(unsigned char channel)
  {    
    ADCON0bits.CHS=channel;             //Channel Select bits 
    ADCON0bits.ADON = 1;                //ADC Enable bit
    __delay_us(200);                    //Acquisition time to charge hold capacitor
    ADCON0bits.GOnDONE=1;               //Initializes A/D Conversion
    while(ADCON0bits.GOnDONE==1);       //Wait for A/D Conversion to complete
    ADC_value =((ADRESH<<8)+ADRESL);    //Returns Result
     return ADC_value;
  } 

void main()
  { 
    TRISCbits.TRISC2=0;                 //output_LED
    TRISCbits.TRISC1=1;                 //ADC inpiut bit selected
    ANSELCbits.ANSC1=1;                 //ADC analog bit config      
    
    SYSTEM_Initialize();
    Osillator_Initialize();
    ADC_Initialize();
    TMR2_Initialize(); 
    EUSART2_Initialize();
    
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    TMR2_SetInterruptHandler(TMR2_int);
    
        while(1)
        {   
            UART_char('1');
           ADC_Read(0b010001);            
        }        
  }
