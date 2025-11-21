/* 
 * File:   IRLIB.h
 * Author: mohit
 *
 * Created on April 6, 2022, 12:22 PM
 */

#ifndef IRLIB_H
#define	IRLIB_H


//#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif
  
uint8_t IRDecode();
//#define DET_ONOFF   1   
//#define DET_COOLING 2
//#define DET_SPEED   3
//#define DET_SWING   4
#define DET_TIMER   5

union BufRotate
{
    unsigned char FullByte;
    struct
    {
        unsigned char Buff:5;
        unsigned char Reserved:3;
    }This;
};

extern union BufRotate Rotate;

extern unsigned char MyBuf[32];
extern unsigned char kk;

extern unsigned int TimerValue;
extern unsigned char NewIRDat;
extern unsigned char DecodedIRKey;

void DecodeIR();



#ifdef	__cplusplus
}
#endif

#endif	/* IRLIB_H */

