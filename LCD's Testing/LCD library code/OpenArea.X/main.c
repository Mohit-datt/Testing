
#include "mcc_generated_files/mcc.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define RS LATCbits.LATC3 
#define EN LATCbits.LATC1
#define RW LATCbits.LATC2
#define D4 LATAbits.LATA4
#define D5 LATAbits.LATA5
#define D6 LATAbits.LATA6
#define D7 LATAbits.LATA7

uint16_t PotRead=0;
unsigned char I2a_Pot[5];

void SendToUart( uint8_t *st_pt)                                                 //L-98 use to print string on Uart screen 
{
    while (*st_pt) //if there is a char
    EUSART2_Write(*st_pt++); //process it as a byte data                    //use to print single character on Uart screen
}

const unsigned short Custom_Char5x8[] = 
{
    
  0b00000,0b01010,0b11010,0b01010,0b01010,0b01011,0b01010,0b00000,    //Data transfer Symbol
  0b00000,0b00100,0b10110,0b01101,0b00110,0b01101,0b10110,0b00100,    //Bluetooth Symbol
  0b11100,0b01000,0b01000,0b01001,0b00011,0b00111,0b01111,0b11111,    //Network Symbol
  0b00000,0b00000,0b01110,0b10001,0b00100,0b01010,0b00000,0b00100     //Wifi Symbol
  
};

void Lcd_SetBit(char data_bit) //Based on the Hex value Set the Bits of the Data Lines
{
    if(data_bit& 1) 
        D4 = 1;
    else
        D4 = 0;

    if(data_bit& 2)
        D5 = 1;
    else
        D5 = 0;

    if(data_bit& 4)
        D6 = 1;
    else
        D6 = 0;

    if(data_bit& 8) 
        D7 = 1;
    else
        D7 = 0;
}

void Lcd_Cmd(char a)
{
    RS = 0;           
    Lcd_SetBit(a); //Incoming Hex value
    EN  = 1;         
        __delay_ms(4);
        EN  = 0;         
}

void Lcd_Clear()
{
    Lcd_Cmd(0); //Clear the LCD
    Lcd_Cmd(1); //Move the curser to first position
}

void Lcd_Set_Cursor(char a, char b)
{
    char temp,z,y;
    if(a== 1)
    {
      temp = 0x80 + b - 1; //80H is used to move the curser
        z = temp>>4; //Lower 8-bits
        y = temp & 0x0F; //Upper 8-bits
        Lcd_Cmd(z); //Set Row
        Lcd_Cmd(y); //Set Column
    }
    else if(a== 2)
    {
        temp = 0xC0 + b - 1;
        z = temp>>4; //Lower 8-bits
        y = temp & 0x0F; //Upper 8-bits
        Lcd_Cmd(z); //Set Row
        Lcd_Cmd(y); //Set Column
    }
}

void Lcd_Start()
{
  Lcd_SetBit(0x00);
  //for(int i=1065244; i<=0; i--)  NOP();  
  __delay_ms(500);//for(int i=1065244; i<=0; i--)  NOP();  
  Lcd_Cmd(0x03);
    __delay_ms(5);
  Lcd_Cmd(0x03);
    __delay_ms(11);
  Lcd_Cmd(0x03); 
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x08); //Select Row 1
  Lcd_Cmd(0x00); //Clear Row 1 Display
  Lcd_Cmd(0x0C); //Select Row 2
  Lcd_Cmd(0x00); //Clear Row 2 Display
  Lcd_Cmd(0x06);
}

void Lcd_Print_Char(char data)  //Send 8-bits through 4-bit mode
{
   char Lower_Nibble,Upper_Nibble;
   Lower_Nibble = data&0x0F;
   Upper_Nibble = data&0xF0;
   RS = 1;             // => RS = 1
   Lcd_SetBit(Upper_Nibble>>4);             //Send upper half by shifting by 4
   EN = 1;
   for(int i=2130483; i<=0; i--)  NOP(); 
   EN = 0;
   Lcd_SetBit(Lower_Nibble); //Send Lower half
   EN = 1;
   for(int i=2130483; i<=0; i--)  NOP();
   EN = 0;
}

void Lcd_Print_String(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
       Lcd_Print_Char(a[i]);  //Split the string using pointers and call the Char function 
}

void LcdPrint(void)
{
    itoa(I2a_Pot,PotRead, 10);                                               //pot value convert into ascii to print on uart
    SendToUart("POT:");                                                  //print string on uart on uart
    SendToUart( I2a_Pot );                                                      //print ascii value of pot value on uart 
    SendToUart("ms");                                                  //print string on uart on uart
    EUSART2_Write('\n');      
}

void main(void)
{
    SYSTEM_Initialize();
    
    Lcd_Start();
    
    while (1)
    {
        PotRead= ADCC_GetSingleConversion(Pot);
        LcdPrint();
        __delay_ms(200);
        //SendToUart(":");
        //EUSART2_Write('m');
    }
}
