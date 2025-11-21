//#ifndef SPI_PINS_H
#define	SPI_PINS_H
//------------------------------------------------------------------------------
#include <xc.h>
//------------------------------------------------------------------------------
#define SCLK       LATCbits.LATC3         //Serial Clock
#define SDOUT      LATCbits.LATC5         //Serial Data Out
//#define SDIN       LATCbits.LATC4         //Serial Data In
#define CS0        LATCbits.LATC6         //Chip 1 Select
//#define CS1        RC3         //Chip 2 Select
//---------------------------DIRECTION------------------------------------------
#define SCLK_dir   TRISCbits.TRISC3
#define SDOUT_dir  TRISCbits.TRISC5
//#define SDIN_dir   TRISCbits.TRISC4
#define CS0_dir    TRISCbits.TRISC6
//#define CS1_dir    TRISC3
//------------------------------------------------------------------------------
//#endif