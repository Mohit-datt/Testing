
//#include "mcc_generated_files/mcc.h"
#include "IRLIB.h"
#include <stdio.h>
#include <xc.h>


//#include "Includes.h"
//const unsigned int ONOFF_KEY[]   =  {125,45, 125,40, 40,125, 130,45, 120,45, 40,130, 35,130, 125,45, 35,130, 40,125, 40,125, 40};  // UNKNOWN 39D41DC6
//                                     //10       10      01    10       10     01      01       10       01     01       01    0
//
//const unsigned int COOLING_KEY[] =  {125,45, 125,40, 45,125, 125,40, 125,45, 45,120, 45,125, 40,125, 125,45, 40,125, 40,125, 45};  // UNKNOWN E0984BB6
//                                      //10    10      01        10      10     01      01       01     10      01      01     0
//
//const unsigned int SPEED_KEY[]   =  {125,45, 120,45, 40,130, 120,45, 125,40, 45,125, 40,125, 40,130, 40,125, 125,45, 40,125, 40};  // UNKNOWN 371A3C86
//                                      //10    10      01        10      10     01      01       01    01       10     01      0
//
//const unsigned int SWING_KEY[]   =  {125,40, 130,35, 45,125, 130,35, 130,40, 45,125, 40,125, 40,130, 40,125, 40,125, 125,40, 45};  // UNKNOWN 143226DB
//                                      //10    10      01        10      10     01     01       01       01       01    10     0
//
//const unsigned int TIMER_KEY[]   =  {125,45, 125,45, 35,130, 120,50, 120,45, 40,130, 120,45, 40,130, 35,130, 40,125, 40,130, 35};  // UNKNOWN 1D2FEFF6
//                                      // 10    10      01      10       10      01      10     01      01       01     01     0


unsigned char DecodedIRKey=0;

//union
//{
//    unsigned char FullByte;
//    struct
//    {
//        unsigned char Buff:5;
//        unsigned char Reserved:3;
//    }This;
//}Rotate;

unsigned char MyBuf[32];
//unsigned int TimerValue;
unsigned char NewIRDat;

//const unsigned char IRAddress[] = "0x40BF";          //40BF
const unsigned char IRAddress[] ="0100000010111111";              //40BF
//const unsigned char KEYCODE[5][11]={"01100101010","01011001010","01010110010","01010101100","10010101010"};
const unsigned char KEYCODE[2][12]={"001100001100","000110001110"};  //30c,18e
//const unsigned char KEYCODE[2][4]={"0x30C","0x18E"};

unsigned char jj;
extern unsigned char MyBuf[32];
unsigned char kk;

union BufRotate Rotate;

unsigned char IRDecode()
{
    for(jj=0;jj<16;jj++)        //Check for Address
    {
        if(MyBuf[jj]!=IRAddress[jj])
        {
            return 0;           //Address not match
        }
    }
    if(jj==16)      //Address is correct now check for data
    {
        for(kk=0;kk<2;kk++)
        {
            for(jj=0;jj<12;jj++)
            {
                if(MyBuf[16+jj]!=KEYCODE[kk][jj])    break;
            }
            if(jj==12)
            {
                NOP();
                return (kk+1);
            }
        }
        return 0;               //Address matches but no data matches
    }
    return 0;
    
//    MyBuf[]=bin_val;
//    while (bin_val != 0)
//    {
//        reminder = bin_val % 10;
//        hex_val = hex_val + reminder * i;
//        i = i * 2;
//        bin_val = bin_val / 10;
//    }
            
}

