/*--------------------------------------------------------------------

  Title       : Header file rc5_decoder.c 
  Filename    : rc5_decoder.h 
   
  Copyright @ BobTheBass 2011

----------------------------------------------------------------------*/

#ifndef RC5_DECODER_H
#define RC5_DECODER_H

/*--- Pulse types ---*/

#define PULSE_OK    0
#define PULSE_ERROR 1

/*--- RC code structure ---*/

typedef struct
  {
  unsigned char toggle;
  unsigned char address;
  unsigned char command;
  unsigned char valid;
  }RC5_CODE;

//extern volatile RC5_CODE RC5_Code;

/*--- RC5 Decoder state machine ---*/

enum RC5_STATE{START_S, CALIBRATE_S, DATA_S};

/*--- RC5 code structure ---*/

volatile RC5_CODE RC5_Code;

/*--- RC5 decoder structure ---*/

typedef struct
  {
  enum RC5_STATE State; 
  unsigned char bit_time;
  unsigned char pulse_t1;
  unsigned char pulse_t2;
  unsigned char pulse_t3;
  unsigned char tolerance;

  unsigned char last_bit;
  unsigned char bit_counter;
  unsigned int rc_data;
  }DECODER;

volatile DECODER Decoder;


 unsigned char get_pulse_length(void);
 void save_data(unsigned char data);


/*--- Function prototypes ---*/

void init_rc5_decoder(void);
//void interrupt isr_vector(void);

#endif

/*--- End of File --*/
